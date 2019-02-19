#include "RBTree.h"
#include "Output.h"

namespace rb_tree {
	RBTree::RBTree() : nil(std::make_shared<SentinelRBNode>()), root(nil) {	}

	void RBTree::insert(const std::shared_ptr<RBNode> z) {
		PRINT("Inserting %d", z->getValue());
		std::shared_ptr<RBNode> y;
		auto x = root;
		while (x != nil) {
			y = x;
			if (z->getValue() < x->getValue()) {
				x = x->left;
			} else {
				x = x->right;
			}
		}
		z->parent = y;
		if (y.get() == nullptr) {
			root = z;
			root->parent = nil;
		} else if (z->getValue() < y->getValue()) {
			y->left = z;
		} else {
			y->right = z;
		}
		z->left = nil;
		z->right = nil;
		z->color = Color::Red;
		insertFixup(z);
	}

	std::shared_ptr<RBNode> RBTree::remove(std::shared_ptr<RBNode> z) {
		std::shared_ptr<RBNode> y;
		std::shared_ptr<RBNode> x;
		if (z->left == nil || z->right == nil) {
			y = z;
		} else {
			y = successor(z);
		}
		if (y->left != nil) {
			x = y->left;
		} else {
			x = y->right;
		}
		x->parent = y->parent;
		if (y->parent == nil) {
			root = x;
		} else if (y == y->parent->left) {
			y->parent->left = x;
		} else {
			y->parent->right = x;
		}
		if (y != z) {
			z->copyData(y);
		}
		if (y->color == Color::Black) {
			removeFixup(x);
		}
		return y;
	}

	void RBTree::printInorder() const {
		PRINT("Inorder:");
		printInorder(root);
	}

	void RBTree::printPreorder() const {
		PRINT("Preorder:");
		printPreorder(root);
	}
	
	std::shared_ptr<RBNode> RBTree::search(int value) const {
		auto x = root;
		while (x != nil && value != x->getValue()) {
			if (value < x->getValue()) {
				x = x->left;
			} else {
				x = x->right;
			}
		}
		return x == nil ? nullptr : x;
	}

	std::shared_ptr<RBNode> RBTree::successor(const std::shared_ptr<RBNode> x) const {
		if (x->right != nil) {
			return treeMinimum(x->right);
		}
		auto y = x->parent;
		auto w = x;
		while (y != nil && w == y->right) {
			w = y;
			y = y->parent;
		}
		return y;
	}

	std::shared_ptr<RBNode> RBTree::treeMinimum(const std::shared_ptr<RBNode> x) const {
		auto w = x;
		while (w->left != nil) {
			w = w->left;
		}
		return w;
	}

	void RBTree::rotateLeft(const std::shared_ptr<RBNode> x) {
		auto y = x->right;
		x->right = y->left;
		if (y->left != nil) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nil) {
			root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void RBTree::rotateRight(const std::shared_ptr<RBNode> x) {
		auto y = x->left;
		x->left = y->right;
		if (y->right != nil) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nil) {
			root = y;
		} else if (x == x->parent->right) {
			x->parent->right = y;
		} else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	void RBTree::insertFixup(std::shared_ptr<RBNode> z) {
		while (z->parent != nil && z->parent->color == Color::Red) {
			if (z->parent->parent != nil && z->parent == z->parent->parent->left) {
				auto y = z->parent->parent->right;
				if (y != nil && y->color == Color::Red) {
					z->parent->color = Color::Black;
					y->color = Color::Black;
					z->parent->parent->color = Color::Red;
					z = z->parent->parent;
				} else {
					if (z == z->parent->right) {
						z = z->parent;
						rotateLeft(z);
					}
					z->parent->color = Color::Black;
					z->parent->parent->color = Color::Red;
					rotateRight(z->parent->parent);
				}
			} else if (z->parent->parent != nil && z->parent == z->parent->parent->right) {
				auto y = z->parent->parent->left;
				if (y != nil && y->color == Color::Red) {
					z->parent->color = Color::Black;
					y->color = Color::Black;
					z->parent->parent->color = Color::Red;
					z = z->parent->parent;
				} else {
					if (z == z->parent->left) {
						z = z->parent;
						rotateRight(z);
					}
					z->parent->color = Color::Black;
					z->parent->parent->color = Color::Red;
					rotateLeft(z->parent->parent);
				}
			}
		}

		root->color = Color::Black;
	}

	void RBTree::removeFixup(std::shared_ptr<RBNode> x) {
		while (x != root && x->color == Color::Black) {
			std::shared_ptr<RBNode> w;
			if (x == x->parent->left) {
				w = x->parent->right;
				if (w->color == Color::Red) {
					w->color = Color::Black;
					x->parent->color = Color::Red;
					rotateLeft(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == Color::Black && w->right->color == Color::Black) {
					w->color = Color::Red;
					x = x->parent;
				} else { 
					if (w->right->color == Color::Black) {
						w->left->color = Color::Black;
						w->color = Color::Red;
						rotateRight(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = Color::Black;
					w->right->color = Color::Black;
					rotateLeft(x->parent);
					x = root;
				}
			} else if (x == x->parent->right) {
				w = x->parent->left;
				if (w->color == Color::Red) {
					w->color = Color::Black;
					x->parent->color = Color::Red;
					rotateRight(x->parent);
					w = x->parent->left;
				}
				if (w->right->color == Color::Black && w->left->color == Color::Black) {
					w->color = Color::Red;
					x = x->parent;
				} else {
					if (w->left->color == Color::Black) {
						w->right->color = Color::Black;
						w->color = Color::Red;
						rotateLeft(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = Color::Black;
					w->right->color = Color::Black;
					rotateRight(x->parent);
					x = root;
				}
			}
		}
	}

	void RBTree::printInorder(const std::shared_ptr<RBNode> x) const {
		if (x != nil) {
			printInorder(x->left);
			PRINT("%d", x->getValue());
			printInorder(x->right);
		}
	}

	void RBTree::printPreorder(const std::shared_ptr<RBNode> x) const {
		if (x != nil) {
			PRINT("%d (Color: %d)", x->getValue(), x->color);
			printPreorder(x->left);
			printPreorder(x->right);
		}
	}

}


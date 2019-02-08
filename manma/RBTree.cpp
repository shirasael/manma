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

	void RBTree::remove(const std::shared_ptr<RBNode> z) {
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
		return std::shared_ptr<RBNode>();
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
						rotateLeft(z);
					}
					z->parent->color = Color::Black;
					z->parent->parent->color = Color::Red;
					rotateRight(z->parent->parent);
				}
			}
		}

		root->color = Color::Black;
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


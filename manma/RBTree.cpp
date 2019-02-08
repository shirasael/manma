#include "RBTree.h"

namespace rb_tree {

	void RBTree::insert(const std::shared_ptr<RBNode> z) {
		std::shared_ptr<RBNode> y;
		auto x = root;
		while (x != nullptr) {
			y = x;
			if (z->getValue() < x->getValue()) {
				x = x->left;
			} else {
				x = x->right;
			}
		}
		auto y = z->parent;
		if (y == nullptr) {
			root = z;
		} else if (z->getValue() < y->getValue()) {
			y->left = z;
		} else {
			y->right = z;
		}
		z->left = nullptr;
		z->right = nullptr;
		z->color = Color::Red;
		insertFixup(z);
	}

	void RBTree::remove(const std::shared_ptr<RBNode> z) {
	}

	std::shared_ptr<RBNode> RBTree::search(int value) {
		return std::shared_ptr<RBNode>();
	}

	void RBTree::rotateLeft(const std::shared_ptr<RBNode> x) {
		auto y = x->right;
		x->right = y->left;
		if (y->left != nullptr) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
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
		if (y->right != nullptr) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
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
		while (z->parent != nullptr && z->parent->color == Color::Red) {
			if (z->parent->parent != nullptr && z->parent == z->parent->parent->left) {
				auto y = z->parent->parent->right;
				if (y != nullptr && y->color == Color::Red) {
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
			} else if (z->parent->parent != nullptr && z->parent == z->parent->parent->right) {
				auto y = z->parent->parent->left;
				if (y != nullptr && y->color == Color::Red) {
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

}


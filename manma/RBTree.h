#pragma once
#include "RBNode.h"
#include "Output.h"
#include <functional>

namespace rb_tree {

	/**
	 * A class that represents a RB tree. The class is templated to the type of element
	 * being held by the tree.
	 * 
	 * The tree is organized according to the values of the function `getValue()` of the elements in it.
	 */
	template<typename T>
	class RBTree {
	public:

		/**
		 * Construct an empty tree. 
		 */
		RBTree();
		virtual ~RBTree() = default;

		/**
		 * Insert a new element into the tree. 
		 * As explaing the the teaching book, running time is O(logn).
		 */
		void insert(std::shared_ptr<RBNode<T>> z);

		/**
		 * Insert an existing element from the tree. 
		 * As explaing the the teaching book, running time is O(logn).
		 */
		std::shared_ptr<RBNode<T>> remove(std::shared_ptr<RBNode<T>> z);

		/**
		 * Search an element in the tree with the given value.
		 * As explaing the the teaching book, running time is O(logn).
		 */
		std::shared_ptr<RBNode<T>> search(double value) const;

		/**
		 * Given an element in the tree, find its successor in the tree.
		 * As explaing the the teaching book, running time is O(logn).
		 */
		std::shared_ptr<RBNode<T>> successor(std::shared_ptr<RBNode<T>> x) const;
		
		/**
		 * Find the minimal / maximal element in the tree.
		 * As explaing the the teaching book, in both cases running time is O(logn).
		 */
		std::shared_ptr<RBNode<T>> minimum() const;
		std::shared_ptr<RBNode<T>> maximum() const;

		/**
		 * Find the element with the value higher-or-equals to the given value, which is also the element 
		 * with the closest value to the given one.
		 * For instance, if the tree contains elements with the values {1, 4.9, 6.5, 8, 3.4} and we call this 
		 * function with the imput 5, the result would be 6.5.
		 * 
		 * The function runs recursivly from the top of the tree to its buttom, therefor the running time
		 * of this procedure is also O(logn).
		 */
		std::shared_ptr<RBNode<T>> closestTo(double value) const;

		/**
		 * Print the tree using in-order strategy.
		 * Running time: O(n).
		 */
		void printInorder() const;

		/**
		 * Print the tree using pre-order strategy.
		 * Running time: O(n).
		 */
		void printPreorder() const;

		/**
		 * Run the given function in an in-order strategy, meaning iterate through the elements in the 
		 * tree FROM SMALLSET TO LARGEST, and for each element run the given function.
		 * 
		 * Running time: O(n).
		 */
		void runInorder(std::function<void(const T&)> f) const;

		/**
		 * Check if the tree contains only one element (i.e, only the root element).
		 * Running time: O(1).
		 */
		bool isOnlyRoot() const;

	private:
		// Helper function to get the maximum / minimum of a subtree in the tree rooting at x.
		std::shared_ptr<RBNode<T>> treeMinimum(std::shared_ptr<RBNode<T>> x) const;
		std::shared_ptr<RBNode<T>> treeMaximum(std::shared_ptr<RBNode<T>> x) const;

		// Rotate the tree left or right at the given node, as explained in the teaching book.
		void rotateLeft(std::shared_ptr<RBNode<T>> x);
		void rotateRight(std::shared_ptr<RBNode<T>> x);

		// Perform fixup after insert / remove, as explained in the teaching book.
		void insertFixup(std::shared_ptr<RBNode<T>> z);
		void removeFixup(std::shared_ptr<RBNode<T>> z);

		// Helper recursive function for `closetTo(double)`.
		std::shared_ptr<RBNode<T>> closestTo(std::shared_ptr<RBNode<T>> x, double value) const;

		// Helper recursive function for `printPreorder()`
		void printPreorder(std::shared_ptr<RBNode<T>> x) const;

		// Helper recursive function for `runInorder(std::function<void(const T&)>)`
		void runInorder(std::shared_ptr<RBNode<T>> x, std::function<void(const T&)> f) const;

	public:
		// Nil sentinel of the tree. Contains no data.
		std::shared_ptr<RBNode<T>> nil;

		// Root element od the tree.
		std::shared_ptr<RBNode<T>> root;
	};

	template<typename T>
	RBTree<T>::RBTree() : nil(std::make_shared<RBNode<T>>(T())), root(nil) {}

	template<typename T>
	void RBTree<T>::insert(std::shared_ptr<RBNode<T>> z) {
		PRINT("Inserting %f", z->getValue());
		std::shared_ptr<RBNode<T>> y;
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

	template<typename T>
	std::shared_ptr<RBNode<T>> RBTree<T>::remove(std::shared_ptr<RBNode<T>> z) {
		std::shared_ptr<RBNode<T>> y;
		std::shared_ptr<RBNode<T>> x;
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

	template<typename T>
	void RBTree<T>::printInorder() const {
		PRINT("Inorder:");
		runInorder(root, [](const T& v) { PRINT("%f", v.value); });
	}

	template<typename T>
	void RBTree<T>::printPreorder() const {
		PRINT("Preorder:");
		printPreorder(root);
	}

	template <typename T>
	void RBTree<T>::runInorder(std::function<void(const T&)> f) const {
		runInorder(root, f);
	}

	template <typename T>
	bool RBTree<T>::isOnlyRoot() const {
		return root != nil && root->right == nil && root->left == nil;
	}

	template<typename T>
	std::shared_ptr<RBNode<T>> RBTree<T>::search(double value) const {
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

	template<typename T>
	std::shared_ptr<RBNode<T>> RBTree<T>::successor(const std::shared_ptr<RBNode<T>> x) const {
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

	template <typename T>
	std::shared_ptr<RBNode<T>> RBTree<T>::minimum() const {
		return treeMinimum(root);
	}

	template <typename T>
	std::shared_ptr<RBNode<T>> RBTree<T>::maximum() const {
		return treeMaximum(root);
	}

	template <typename T>
	std::shared_ptr<RBNode<T>> RBTree<T>::closestTo(double value) const {
		return closestTo(root, value);
	}

	template<typename T>
	std::shared_ptr<RBNode<T>> RBTree<T>::treeMinimum(const std::shared_ptr<RBNode<T>> x) const {
		auto w = x;
		while (w->left != nil) {
			w = w->left;
		}
		return w;
	}

	template<typename T>
	std::shared_ptr<RBNode<T>> RBTree<T>::treeMaximum(const std::shared_ptr<RBNode<T>> x) const {
		auto w = x;
		while (w->left != nil) {
			w = w->left;
		}
		return w;
	}

	template<typename T>
	void RBTree<T>::rotateLeft(const std::shared_ptr<RBNode<T>> x) {
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

	template<typename T>
	void RBTree<T>::rotateRight(const std::shared_ptr<RBNode<T>> x) {
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

	template<typename T>
	void RBTree<T>::insertFixup(std::shared_ptr<RBNode<T>> z) {
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

	template<typename T>
	void RBTree<T>::removeFixup(std::shared_ptr<RBNode<T>> z) {
		while (z != root && z->color == Color::Black) {
			std::shared_ptr<RBNode<T>> w;
			if (z == z->parent->left) {
				w = z->parent->right;
				if (w->color == Color::Red) {
					w->color = Color::Black;
					z->parent->color = Color::Red;
					rotateLeft(z->parent);
					w = z->parent->right;
				}
				if (w->left->color == Color::Black && w->right->color == Color::Black) {
					w->color = Color::Red;
					z = z->parent;
				} else {
					if (w->right->color == Color::Black) {
						w->left->color = Color::Black;
						w->color = Color::Red;
						rotateRight(w);
						w = z->parent->right;
					}
					w->color = z->parent->color;
					z->parent->color = Color::Black;
					w->right->color = Color::Black;
					rotateLeft(z->parent);
					z = root;
				}
			} else if (z == z->parent->right) {
				w = z->parent->left;
				if (w->color == Color::Red) {
					w->color = Color::Black;
					z->parent->color = Color::Red;
					rotateRight(z->parent);
					w = z->parent->left;
				}
				if (w->right->color == Color::Black && w->left->color == Color::Black) {
					w->color = Color::Red;
					z = z->parent;
				} else {
					if (w->left->color == Color::Black) {
						w->right->color = Color::Black;
						w->color = Color::Red;
						rotateLeft(w);
						w = z->parent->left;
					}
					w->color = z->parent->color;
					z->parent->color = Color::Black;
					w->right->color = Color::Black;
					rotateRight(z->parent);
					z = root;
				}
			}
		}
	}

	template <typename T>
	std::shared_ptr<RBNode<T>> RBTree<T>::closestTo(std::shared_ptr<RBNode<T>> x, double value) const {
		if (x == nil || x == nullptr) {
			return nullptr;
		}
		if (x->getValue() == value) {
			return x;
		}
		if (x->getValue() > value) {
			auto k = closestTo(x->left, value);
			if (k == nil || k == nullptr) {
				return x;
			}
			return k;
		}
		if (x->getValue() < value) {
			return closestTo(x->right, value);
		}
		return nullptr;
	}

	template<typename T>
	void RBTree<T>::printPreorder(const std::shared_ptr<RBNode<T>> x) const {
		if (x != nil) {
			PRINT("%f (Color: %d)", x->getValue(), x->color);
			printPreorder(x->left);
			printPreorder(x->right);
		}
	}

	template <typename T>
	void RBTree<T>::runInorder(const std::shared_ptr<RBNode<T>> x, std::function<void(const T&)> f) const {
		if (x != nil) {
			runInorder(x->left, f);
			f(*x->data);
			runInorder(x->right, f);
		}
	}
}

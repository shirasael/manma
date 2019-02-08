#pragma once
#include "RBNode.h"

namespace rb_tree {

	class RBTree {
	public:
		RBTree();
		virtual ~RBTree() = default;

		void insert(const std::shared_ptr<RBNode> z);
		void remove(const std::shared_ptr<RBNode> z);
		std::shared_ptr<RBNode> search(int value) const;

		void printInorder() const;
		void printPreorder() const;

	private:

		void rotateLeft(const std::shared_ptr<RBNode> x);
		void rotateRight(const std::shared_ptr<RBNode> x);

		void insertFixup(std::shared_ptr<RBNode> z);

		void printInorder(const std::shared_ptr<RBNode> x) const;
		void printPreorder(const std::shared_ptr<RBNode> x) const;

		std::shared_ptr<RBNode> nil;

	public:
		std::shared_ptr<RBNode> root;

	};

}
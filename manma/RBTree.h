#pragma once
#include "RBNode.h"

namespace rb_tree {

	class RBTree {
	public:
		RBTree() = default;
		virtual ~RBTree() = default;

		void insert(const std::shared_ptr<RBNode> z);
		void remove(const std::shared_ptr<RBNode> z);
		std::shared_ptr<RBNode> search(int value);

	private:

		void rotateLeft(const std::shared_ptr<RBNode> x);
		void rotateRight(const std::shared_ptr<RBNode> x);

		void insertFixup(std::shared_ptr<RBNode> z);

	public:
		std::shared_ptr<RBNode> root;
	};

}
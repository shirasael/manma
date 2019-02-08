#pragma once
#include <memory>

namespace rb_tree {
	enum Color {
		Black,
		Red
	};

	class RBNode {
	public:
		RBNode(Color color);
		RBNode(Color color, const std::shared_ptr<RBNode> parent);
		virtual ~RBNode() = default;

		virtual int getValue() const = 0;

		Color color;
		std::shared_ptr<RBNode> parent;
		std::shared_ptr<RBNode> left;
		std::shared_ptr<RBNode> right;
	};

}


#pragma once
#include <memory>

namespace rb_tree {
	enum class Color : int{
		Black,
		Red
	};

	class RBNode {
	public:
		RBNode();
		explicit RBNode(Color color);
		virtual ~RBNode() = default;

		virtual int getValue() const = 0;
		virtual void copyData(const std::shared_ptr<RBNode>& other) {};

		Color color;
		std::shared_ptr<RBNode> parent;
		std::shared_ptr<RBNode> left;
		std::shared_ptr<RBNode> right;
	};


	class SimpleRBNode final : public RBNode {
	public:
		explicit SimpleRBNode(int value);
		int getValue() const override;
		void copyData(const std::shared_ptr<RBNode>& other) override;
		int value;
	};


	class SentinelRBNode final : public RBNode {
	public:
		const int SENTINEL = 0xFFFFFFFF;

		SentinelRBNode();
		int getValue() const override { return SENTINEL; };
	};

}


#include "RBNode.h"

namespace rb_tree {
	RBNode::RBNode() : color(Color::Red) {}

	RBNode::RBNode(Color color) : color(color) {}

	SimpleRBNode::SimpleRBNode(int value) : RBNode(), value(value) {}
	int SimpleRBNode::getValue() const {
		return value;
	}
	SentinelRBNode::SentinelRBNode() : RBNode(Color::Black) {}
}
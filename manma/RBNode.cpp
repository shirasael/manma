#include "RBNode.h"

namespace rb_tree {
	RBNode::RBNode() : color(Color::Red) {}

	RBNode::RBNode(Color color) : color(color) {}

	SimpleRBNode::SimpleRBNode(int value) : RBNode(), value(value) {}
	
	int SimpleRBNode::getValue() const {
		return value;
	}
	
	void SimpleRBNode::copyData(const std::shared_ptr<RBNode>& other) {
		auto o = static_cast<SimpleRBNode*>(other.get());
		value = o->value;
	}
	
	SentinelRBNode::SentinelRBNode() : RBNode(Color::Black) {}
}
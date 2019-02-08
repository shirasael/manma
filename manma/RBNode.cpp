#include "RBNode.h"

namespace rb_tree {
	RBNode::RBNode(Color color) : color(color) {}
	RBNode::RBNode(Color color, const std::shared_ptr<RBNode> parent) : color(color), parent(parent) {}
}
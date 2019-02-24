#include "BoxerNodes.h"

namespace boxer {
//
//	BoxNode::BoxNode(const std::shared_ptr<Box>& box) : box(box) {}
//	
//	BoxNode::BoxNode(const Dimensions& d) : box(std::make_shared<Box>(d)) {}
//	
//	void BoxNode::copyData(const std::shared_ptr<RBNode>& other) {
//		const auto o = dynamic_cast<BoxNode*>(other.get());
//		box = o->box;
//	}
//
//	BoxSideNode::BoxSideNode(const std::shared_ptr<Box>& box) : BoxNode(box){}
//	
//	BoxSideNode::BoxSideNode(const Dimensions& d) : BoxNode(d) {}
//	
//	double BoxSideNode::getValue() const {
//		return box->dimensions.side;
//	}
//
//	void BoxSideNode::copyData(const std::shared_ptr<RBNode>& other) {
//		BoxNode::copyData(other);
//		const auto o = dynamic_cast<BoxSideNode*>(other.get());
//		rootHeightNode = o->rootHeightNode;
//	}
//
//	BoxHeightNode::BoxHeightNode(const std::shared_ptr<Box>& box) : BoxNode(box) {}
//
//	BoxHeightNode::BoxHeightNode(const Dimensions& d) : BoxNode(d) {}
//	
//	double BoxHeightNode::getValue() const {
//		return box->dimensions.height;
//	}
//
//	void BoxHeightNode::copyData(const std::shared_ptr<RBNode>& other) {
//		BoxNode::copyData(other);
//		const auto o = dynamic_cast<BoxHeightNode*>(other.get());
//		rootSideNode = o->rootSideNode;
//	}
//
//	BoxVolumNode::BoxVolumNode(const std::shared_ptr<Box>& box) : BoxNode(box) {}
//
//	BoxVolumNode::BoxVolumNode(const Dimensions& d) : BoxNode(d) {}
//
//	double BoxVolumNode::getValue() const {
//		return box->dimensions.side * box->dimensions.side * box->dimensions.height;
//	}
//
}

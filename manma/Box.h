#pragma once
#include "RBTree.h"

namespace boxer {

	class Box final {
	public:
		explicit Box(double side, double height) : side(side), height(height) {};
		~Box() = default;

		double volum() const {
			return side * side * height;
		}

		double side;
		double height;
	};

	struct SimpleValue {
		SimpleValue() = default;
		explicit SimpleValue(const std::shared_ptr<Box>& box, double value) : box(box), value(value) {};
		
		std::shared_ptr<Box> box;
		double value;
	};

	class SideBox final {
	public:
		explicit SideBox(const std::shared_ptr<Box>& box) : value(box->side) {};
		SideBox() : value(-1) {};

		double value;
		rb_tree::RBTree<SimpleValue> heights;
	};

	class HeightBox final {
	public:
		explicit HeightBox(const std::shared_ptr<Box>& box) : value(box->height) {};
		HeightBox() : value(-1) {};

		double value;
		rb_tree::RBTree<SimpleValue> sides;
	};

	class HeapVolumBox final {
	public:
		explicit HeapVolumBox(const std::shared_ptr<Box>& box) : 
			box(box), value(box->volum()) {};
		HeapVolumBox() : value(-1) {};

		std::shared_ptr<Box> box;
		double value;
	};

	class TreeVolumBox final {
	public:
		explicit TreeVolumBox(const std::shared_ptr<HeapVolumBox>& vbox) :
			vbox(vbox), value(vbox->box->volum()) {};
		TreeVolumBox() : value(-1) {};

		std::shared_ptr<HeapVolumBox> vbox;
		double value;
	};
}


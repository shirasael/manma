#pragma once
#include "RBTree.h"

namespace boxer {

	// A class of an object Box which has a side and height and the ability to calculate its volume
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

	// A class of object box that has a specific side value and a tree to represent all the heights possible for this side in the box storage
	class SideBox final {
	public:
		explicit SideBox(const std::shared_ptr<Box>& box) : value(box->side) {};
		SideBox() : value(-1) {};

		double value;
		rb_tree::RBTree<SimpleValue> heights;
	};

	// A class of object box that has a specific height value and a tree to represent all the sides possible for this side in the box storage
	class HeightBox final {
	public:
		explicit HeightBox(const std::shared_ptr<Box>& box) : value(box->height) {};
		HeightBox() : value(-1) {};

		double value;
		rb_tree::RBTree<SimpleValue> sides;
	};

	// A class of object box that represents the volume of the box - will be used in the heap - heap of volume boxes
	class HeapVolumBox final {
	public:
		explicit HeapVolumBox(const std::shared_ptr<Box>& box) : 
			box(box), value(box->volum()) {};
		HeapVolumBox() : value(-1) {};

		std::shared_ptr<Box> box;
		double value;
	};

	// A class of object box that represents the volume of the box will be used in a tree - tree of volume boxes
	class TreeVolumBox final {
	public:
		explicit TreeVolumBox(const std::shared_ptr<HeapVolumBox>& vbox) :
			vbox(vbox), value(vbox->box->volum()) {};
		TreeVolumBox() : value(-1) {};

		std::shared_ptr<HeapVolumBox> vbox;
		double value;
	};
}


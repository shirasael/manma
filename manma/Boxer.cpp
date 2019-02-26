#include "Boxer.h"

namespace boxer {

	using namespace heap;
	using namespace rb_tree;

	Boxer::Boxer(): highVolums(Minimum), lowVolums(Maximum) {}

	void Boxer::insertBox(const std::shared_ptr<Box>& box) {
		auto vbox = std::make_shared<HeapVolumBox>(box);
		if (lowVolums.heapSize() == 0 || box->volum() > lowVolums.top()->box->volum()) {
			highVolums.insert(vbox);
		} else {
			lowVolums.insert(vbox);
		}
		if (abs(lowVolums.heapSize() - highVolums.heapSize()) > 1) {
			fixHeaps();
		} 

		auto side = sides.search(box->side);
		if (side == nullptr) {
			side = std::make_shared<RBNode<SideBox>>(SideBox{ box });
			sides.insert(side);
		}
		side->data->heights.insert(std::make_shared<RBNode<SimpleValue>>(SimpleValue{ box, box->height }));

		auto height = heights.search(box->height);
		if (height == nullptr) {
			height = std::make_shared<RBNode<HeightBox>>(HeightBox{ box });
			heights.insert(height);
		}
		height->data->sides.insert(std::make_shared<RBNode<SimpleValue>>(SimpleValue{ box, box->side }));
	}

	void Boxer::removeBox(const Box& box) {
		// search in tree for box with given volume 
		auto vbox = volums.search(box.volum());
		if (vbox == nullptr) {
			PRINT("Could not remove box - no such box in storage.")
			return;
		}

		// find if vbox is the low heap or the high heap and remove it
		if (lowVolums.indexOf(*vbox->data->vbox) >= 0) {
			lowVolums.remove(vbox->data->vbox);
		} else {
			highVolums.remove(vbox->data->vbox);
		}
		
		fixHeaps();

		// remove box from tree of volumes
		volums.remove(vbox);

		// Remove data from sides rbtree
		auto side = sides.search(box.side);
		if (side != nullptr) {
			if (side->data->heights.isOnlyRoot()) {
				sides.remove(side);
			} else {
				auto height = side->data->heights.search(box.height);
				side->data->heights.remove(height);
			}
		}

		// Remove data from heights rbtree
		auto height = heights.search(box.height);
		if (height != nullptr) {
			if (height->data->sides.isOnlyRoot()) {
				heights.remove(height);
			} else {
				auto side = height->data->sides.search(box.side);
				height->data->sides.remove(side);
			}
		}
	}

	std::shared_ptr<Box> Boxer::getBox(const Box& box) const {
		
		// check if the box exists 
		if (!checkBox(box)) {
			return nullptr;
		}

		auto min = std::make_shared<Box>(DBL_MAX, DBL_MAX);
		sides.runInorder([&](const SideBox& side) {
			const auto closest = side.heights.closestTo(box.height);
			if (side.value >= box.side && closest != nullptr && min->volum() > closest->data->box->volum()) {
				min = closest->data->box;
			}
		});
		return min;
	}

	bool Boxer::checkBox(const Box& box) const {
		bool found = false;
		sides.runInorder([&](const SideBox& side) {
			if (side.value >= box.side && side.heights.maximum()->getValue() >= box.height) {
				found = true;
			}
		});
		return found;
	}

	std::shared_ptr<Box> Boxer::getMedianBox() const {
		return lowVolums.top()->box;
	}

	void Boxer::display() const {
		PRINT("~~~ BOXER ~~~");
		highVolums.displayHeap();
		lowVolums.displayHeap();

		sides.printPreorder();
		heights.printPreorder();
		volums.printPreorder();
	}

	void Boxer::fixHeaps() {
		if (lowVolums.heapSize() > highVolums.heapSize()) {
			highVolums.insert(lowVolums.top());
			lowVolums.pop();
		} else {
			lowVolums.insert(highVolums.top());
			highVolums.pop();
		}
	}
}

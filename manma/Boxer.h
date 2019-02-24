#pragma once
#include "Box.h"
#include <memory>
#include "RBTree.h"
#include "Heap.h"

namespace boxer {

	class Boxer final {
	public:
		Boxer();
		~Boxer() = default;

		/**
		 * @brief Inerts...
		 * 
		 * Complexity:
		 * We call 3 times to rbtree.insert - hich runs in O(logn)....
		 */
		void insertBox(const std::shared_ptr<Box>& box);
		void removeBox(const Box& box);
		std::shared_ptr<Box> getBox(const Box& box) const;
		bool checkBox(const Box& box) const;
		std::shared_ptr<Box> getMeianBox() const;

		void display() const;

	private:

		void fixHeaps();

		rb_tree::RBTree<SideBox> sides;
		rb_tree::RBTree<HeightBox> heights;
		rb_tree::RBTree<TreeVolumBox> volums;

		heap::Heap<HeapVolumBox> highVolums;
		heap::Heap<HeapVolumBox> lowVolums;
	};

}

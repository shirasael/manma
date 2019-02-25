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
		 * @brief Insert...
		 * 
		 * Complexity:
		 * We call 3 times to rbtree.insert - which runs in O(logn)
		 * We call 1 time to heap.insert - which runs in O(logm)
		 * In total the Insert complexity is O(logmn)
		 */
		void insertBox(const std::shared_ptr<Box>& box);
		/**
		* @brief Remove...
		*
		* Complexity:
		* We call 3 times to rbtree.remove - which runs in O(logn)
		* We call 1 time to heap.remove - which runs in O(m)
		* In total the Remove complexity is O()
		*/
		void removeBox(const Box& box);
		/**
		* @brief Get...
		*
		* Complexity:
		* The complexity of removing box from tree is 
		* The complexity of removiing box from heap is 
		*/
		std::shared_ptr<Box> getBox(const Box& box) const;
		/**
		* @brief Check...
		*
		* Complexity:
		* In total the Check complexity is O(logn)
		*/
		bool checkBox(const Box& box) const;
		/**
		* @brief GetMedian...
		*
		* Complexity:
		* In total the GetMedian complexity is O(1) using the top function
		*/
		std::shared_ptr<Box> getMedianBox() const;

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

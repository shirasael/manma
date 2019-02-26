#pragma once
#include "Box.h"
#include <memory>
#include "RBTree.h"
#include "Heap.h"

namespace boxer {

	/**
	 * A class that holds the needed data structure.
	 * Throughout this file, let n be the number of boxes inserted, s the number of different sides 
	 * inserted and h the number of different hights inserted.
	 * 
	 * Every boxer is composed from 3 RBTs and 2 heaps:
	 *		1.	One RB tree that holds all the volums of the inserted boxes (size: n)
	 *		2.	Two RB trees that hold th different sides and the different hights of the inserted boxes.
	 *			Every node in the sides tree holds an RB tree of its own, referring to the matching heights
	 *			of the boxes inserted with that side. Same thing applies to the hights tree.
	 *			The size of the sides-tree is s, and the size of the hieghts-tree is h.
	 *			The size of each inner tree in the sides-tree is O(h), and as for the inner trees of the 
	 *			heigts-tree - O(s).
	 *		3.	One MAXIMUM heap that holds the boxes with the LOWEST volums and one MINIMUM heap 
	 *			that holds the boxes with the HIGHEST volums. Each heap contains half of the boxes (i.e, the
	 *			size of each heap is n/2).
	 */
	class Boxer final {
	public:
		Boxer();
		~Boxer() = default;

		/**
		 * @brief Insert a new box into the storage.
		 * 
		 * Complexity:
		 * 
		 * We call 5 times to rbtree.insert: 
		 *		1. Once for the volums - O(logn)
		 *		2. Once for the sides-tree - O(logs), and then in the inner heights-tree - O(logh)
		 *		2. Once for the heights-tree - O(logh), and then in the inner sides-tree - O(logs)
		 * We call 1 time to heap.insert - which runs in O(logn/2)=O(logn)
		 * In total, since s <n and h < n, we get that insertion is done in time O(logn).
		 * 
		 */
		void insertBox(const std::shared_ptr<Box>& box);

		/**
		 * @brief Remove a box with the given properties from the storage.
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

		/**
		 * @brief:	If the heaps are not balanced, meaning the boxes are not split equally between them: remove the
		 *			top box from the too-large heap, and place it in the other heap.
		 *			
		 * Complexity:
		 * The size of each heap is O(n/2). Hence, extracting the top element from a heap is done in time of O(logn).
		 * By similar manner, Placing the element in the other heap takes O(logn) time.
		 * Therefor the running time of the function is O(logn).
		 * 
		 */
		void fixHeaps();

		rb_tree::RBTree<SideBox> sides;
		rb_tree::RBTree<HeightBox> heights;
		rb_tree::RBTree<TreeVolumBox> volums;

		heap::Heap<HeapVolumBox> highVolums;
		heap::Heap<HeapVolumBox> lowVolums;
	};

}

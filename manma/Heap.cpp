#include "Heap.h"

namespace heap {
	Heap::Heap()
	{
	}
	
	// Insert element into heap
	void Heap::Insert(int element)
	{
		// insert the new element to the end of the vector
		heap.push_back(element);

		// call heapify up on element index
		heapifyUp(heap.size() - 1);
	}

	// Remove element at root
	void Heap::Pop()
	{
		// if heap has no elemennts
		if (heap.size() == 0)
			cout << "heap is empty - no element to pop";
		else {
			// replace the root of the heap with the last element of the vector
			heap[0] = heap.back();
			heap.pop_back();

			// call heapify down on root node
			heapifyDown(0);
		}
	}
	
	// Return element at root
	int Heap::top()
	{
		// if heap has no elemennts
		if (heap.size() == 0)
		{
			cout << "heap is empty - no element to return";
			return NULL;
		}
		else
		{
			return heap[0];
		}
	}

	// Display Heap
	void Heap::DisplayHeap()
	{
		vector <int>::iterator pos = heap.begin();
		cout << "Heap: ";
		while (pos != heap.end())
		{
			cout << *pos << " ";
			pos++;
		}
		cout << endl;
	}

	//  Check if heap is empty
	bool Heap::Empty()
	{
		return heap.size() == 0;
	}

	// Return size of heap
	int Heap::heapSize()
	{
		return heap.size();
	}

	// Return parent location
	int Heap::parent(int child)
	{
		int p = (child - 1) / 2;
		if (child == 0)
			return -1;
		else
			return p;
	}

	// Return parents' left child location
	int Heap::leftChild(int idxParent)
	{
		return (idxParent + 1) * 2 - 1;
	}

	// Return parents' right child location
	int Heap::rightChild(int idxParent)
	{
		return (idxParent + 1) * 2;
	}

	// Recursive heapify up algorithm - maintain heap structure from bottom to top
	void Heap::heapifyUp(int idx)
	{
		// check if node at idx and its parent violets the heap properties
		if (idx >= 0 && parent(idx) >= 0 && heap[parent(idx)] < heap[idx])
		{
			// swap them if heap property is violated
			swap(heap[idx], heap[parent(idx)]);

			// call heapify up on parent
			heapifyUp(parent(idx));
		}
	}

	//  Recursive heapify down algorithm - maintain heap structure from top to bottom 
	void Heap::heapifyDown(int idx)
	{
		// get left and right childs locations of node at index idx
		int lchild = leftChild(idx);
		int rchild = rightChild(idx);

		int max = idx;

		// compare node at heap[idx] with its left and right childs and fint max value
		if (lchild < heap.size() && heap[lchild] > heap[idx])
			max = lchild;

		if (rchild < heap.size() && heap[rchild] > heap[idx])
			max = rchild;

		// swap with the child that has the bigger value and call heapify down on child
		if (max != idx)
		{
			swap(heap[idx], heap[max]);
			heapifyDown(max);
		}
	}
}


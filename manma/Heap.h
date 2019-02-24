#pragma once
#include <vector>
#include "Output.h"
#include <memory>
#include <iostream>

using namespace std;

namespace heap {

	template<typename T>
	class Heap {

	public:
		Heap();
		virtual ~Heap() = default;

		void insert(T element);
		void pop();
		void displayHeap() const;

		bool empty() const;

		int heapSize() const;
		T top() const;

	private:
		int parentIdx(int idxChild) const;
		int leftChildIdx(int idxParent) const;
		int rightChildIdx(int idxParent) const;

		void heapifyUp(int idx);
		void heapifyDown(int idx);

		vector<T> _heap;
	};

	template<typename T>
	Heap<T>::Heap() {}

	// Insert element into heap
	template<typename T>
	void Heap<T>::insert(T element) {
		// insert the new element to the end of the vector
		_heap.push_back(element);

		// call heapify up on element index
		heapifyUp(_heap.size() - 1);
	}

	// Remove element at root
	template<typename T>
	void Heap<T>::pop() {
		// if heap has no elemennts
		if (_heap.size() == 0) {			
			PRINT("heap is empty - no element to pop");
		} else {
			// replace the root of the heap with the last element of the vector
			_heap[0] = _heap.back();
			_heap.pop_back();

			// call heapify down on root node
			heapifyDown(0);
		}
	}

	// Return element at root
	template<typename T>
	T Heap<T>::top() const {
		// if heap has no elemennts
		if (_heap.size() == 0) {
			throw std::exception("heap is empty - no element to return");
		} else {
			return _heap[0];
		}
	}

	// Display Heap
	template<typename T>
	void Heap<T>::displayHeap() const {
		vector<T>::const_iterator pos = _heap.begin();
		PRINT("Heap:");
		while (pos != _heap.end()) {
			cout << (*pos).value << " ";
			pos++;
		}
		cout << endl;
	}

	//  Check if heap is empty
	template<typename T>
	bool Heap<T>::empty() const {
		return _heap.size() == 0;
	}

	// Return size of heap
	template<typename T>
	int Heap<T>::heapSize() const {
		return _heap.size();
	}

	// Return parentIdx location
	template<typename T>
	int Heap<T>::parentIdx(int idxChild) const {
		int p = (idxChild - 1) / 2;
		if (idxChild == 0)
			return -1;
		else
			return p;
	}

	// Return parents' left child location
	template<typename T>
	int Heap<T>::leftChildIdx(int idxParent) const {
		return (idxParent + 1) * 2 - 1;
	}

	// Return parents' right child location
	template<typename T>
	int Heap<T>::rightChildIdx(int idxParent) const {
		return (idxParent + 1) * 2;
	}

	// Recursive heapify up algorithm - maintain heap structure from bottom to top
	template<typename T>
	void Heap<T>::heapifyUp(int idx) {
		// check if node at idx and its parentIdx violets the heap properties
		if (idx >= 0 && parentIdx(idx) >= 0 && _heap[parentIdx(idx)].value < _heap[idx].value) {
			// swap them if heap property is violated
			swap(_heap[idx], _heap[parentIdx(idx)]);

			// call heapify up on parentIdx
			heapifyUp(parentIdx(idx));
		}
	}

	//  Recursive heapify down algorithm - maintain heap structure from top to bottom 
	template<typename T>
	void Heap<T>::heapifyDown(int idx) {
		// get left and right childs locations of node at index idx
		int lchild = leftChildIdx(idx);
		int rchild = rightChildIdx(idx);

		int max = idx;

		// compare node at heap[idx] with its left and right childs and fint max value
		if (lchild < _heap.size() && _heap[lchild].value > _heap[idx].value)
			max = lchild;

		if (rchild < _heap.size() && _heap[rchild].value > _heap[idx].value)
			max = rchild;

		// swap with the child that has the bigger value and call heapify down on child
		if (max != idx) {
			swap(_heap[idx], _heap[max]);
			heapifyDown(max);
		}
	}

}
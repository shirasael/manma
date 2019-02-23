#pragma once
#include <vector>
#include <cstdlib>
#include <iostream>
#include <Bits.h>

using namespace std;

namespace heap {

	class Heap
	{

		public:
			Heap();
			virtual ~Heap() = default;

			void Insert(int element);
			void Pop();
			void DisplayHeap();

			bool Empty();

			int heapSize();
			int top();

		private:

			vector <int> heap;

			int parent(int child);
			int leftChild(int idxParent);
			int rightChild(int idxParent);

			void heapifyUp(int idx);
			void heapifyDown(int idx);
	};
}
#include "Output.h"
#include "Input.h"
#include "RBTree.h"
#include <fstream>
#include <sstream>
#include "Heap.h"

const int ARGS_COUNT = 2;

using namespace rb_tree;

struct SimpleNode {
	SimpleNode() : value(DBL_MAX) {};
	SimpleNode(double value) : value(value) {};
	
	double value;
};

void testHeap() {
	heap::Heap<SimpleNode> heap;
	heap.insert(SimpleNode{ 1.0 });
	heap.insert(SimpleNode{ 2.0 });
	heap.insert(SimpleNode{ 10.0 });
	heap.insert(SimpleNode{ 4.0 });
	heap.insert(SimpleNode{ 5.0 });
	heap.insert(SimpleNode{ 14.0 });
	heap.insert(SimpleNode{ 7.0 });
	heap.insert(SimpleNode{ 8.0 });
	heap.insert(SimpleNode{ 13.0 });

	heap.displayHeap();

	PRINT("Heap size: %d", heap.heapSize());

	PRINT("Top: %f", heap.top().value);
}

void testRBTree() {
	RBTree<SimpleNode> tree;
	auto a = std::make_shared<RBNode<SimpleNode>>(SimpleNode{ 10 });
	auto b = std::make_shared<RBNode<SimpleNode>>(SimpleNode{ 7 });
	tree.insert(std::make_shared<RBNode<SimpleNode>>(SimpleNode{ 12 }));
	tree.insert(std::make_shared<RBNode<SimpleNode>>(SimpleNode{ 11 }));
	tree.insert(a);
	tree.insert(std::make_shared<RBNode<SimpleNode>>(SimpleNode{ 9 }));
	tree.insert(std::make_shared<RBNode<SimpleNode>>(SimpleNode{ 8 }));
	tree.insert(b);
	tree.insert(std::make_shared<RBNode<SimpleNode>>(SimpleNode{ 6 }));
	tree.insert(std::make_shared<RBNode<SimpleNode>>(SimpleNode{ 5 }));
	tree.insert(std::make_shared<RBNode<SimpleNode>>(SimpleNode{ 5 }));
	tree.insert(std::make_shared<RBNode<SimpleNode>>(SimpleNode{ 4 }));
	tree.insert(std::make_shared<RBNode<SimpleNode>>(SimpleNode{ 3 }));
	tree.insert(std::make_shared<RBNode<SimpleNode>>(SimpleNode{ 2 }));
	tree.insert(std::make_shared<RBNode<SimpleNode>>(SimpleNode{ 1 }));
	tree.printInorder();
	tree.printPreorder();
	PRINT("----------------------");
	tree.remove(a);
	tree.remove(b);
	tree.printInorder();
	tree.printPreorder();
	PRINT("Fininding 4...");
	auto x = tree.search(4);
	PRINT("Found: %p", x.get());
	PRINT("Finding 532...");
	x = tree.search(532);
	PRINT("Found: %p", x.get());
}


int main(int argc, char *argv[]) {
	// testRBTree();
	testHeap();

	if (argc != ARGS_COUNT) {
		PRINT("Usage: manma.exe <input_file_path>");
		return 1;
	}

	PRINT("Reading input file %s", argv[1]);

	std::ifstream infile(argv[1]);
	std::string line;
	while (std::getline(infile, line)) {
		PRINT(">>> %s", line.c_str());
		Input input(parse(line));
		switch (input.cmd) {
		case InputCmd::Insert:
			PRINT("Performing insert with side %f, heghit %f", input.args[0], input.args[1]);
			break;
		case InputCmd::Remove:
			PRINT("Performing remove with side %f, heghit %f", input.args[0], input.args[1]);
			break;
		case InputCmd::Get:
			PRINT("Performing get with side %f, heghit %f", input.args[0], input.args[1]);
			break;
		case InputCmd::Check:
			PRINT("Performing check with side %f, heghit %f", input.args[0], input.args[1]);
			break;
		case InputCmd::Median:
			PRINT("Performing get median");
			break;
		default:
			break;
		}
	}

	return 0;
}
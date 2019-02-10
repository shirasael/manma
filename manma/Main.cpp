#include "Output.h"
#include "Input.h"
#include "RBTree.h"
#include <fstream>
#include <sstream>

const int ARGS_COUNT = 2;

using namespace rb_tree;

void testRBTree() {
	RBTree tree;
	auto a = std::make_shared<SimpleRBNode>(10);
	auto b = std::make_shared<SimpleRBNode>(7);
	tree.insert(std::make_shared<SimpleRBNode>(12));
	tree.insert(std::make_shared<SimpleRBNode>(11));
	tree.insert(a);
	tree.insert(std::make_shared<SimpleRBNode>(9));
	tree.insert(std::make_shared<SimpleRBNode>(8));
	tree.insert(b);
	tree.insert(std::make_shared<SimpleRBNode>(6));
	tree.insert(std::make_shared<SimpleRBNode>(5));
	tree.insert(std::make_shared<SimpleRBNode>(5));
	tree.insert(std::make_shared<SimpleRBNode>(4));
	tree.insert(std::make_shared<SimpleRBNode>(3));
	tree.insert(std::make_shared<SimpleRBNode>(2));
	tree.insert(std::make_shared<SimpleRBNode>(1));
	tree.printInorder();
	tree.printPreorder();
	PRINT("----------------------");
	tree.remove(a);
	tree.remove(b);
	tree.printInorder();
	tree.printPreorder();
}


int main(int argc, char *argv[]) {
	testRBTree();

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
			PRINT("Performing insert with side %d, heghit %d", input.args[0], input.args[1]);
			break;
		case InputCmd::Remove:
			PRINT("Performing remove with side %d, heghit %d", input.args[0], input.args[1]);
			break;
		case InputCmd::Get:
			PRINT("Performing get with side %d, heghit %d", input.args[0], input.args[1]);
			break;
		case InputCmd::Check:
			PRINT("Performing check with side %d, heghit %d", input.args[0], input.args[1]);
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
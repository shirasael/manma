#include "Output.h"
#include "Input.h"
#include "RBTree.h"
#include <fstream>
#include <sstream>
#include "Heap.h"
#include "Box.h"
#include "Boxer.h"


const int ARGS_COUNT = 2;

void runGetBox(const boxer::Boxer& boxer, double side, double height) {
	const auto res = boxer.getBox(boxer::Box(side, height));
	if (res == nullptr) {
		PRINT("Box not found");
	} else {
		PRINT("Found box side: %f, height %f", res->side, res->height);
	}
}

void runMedian(boxer::Boxer boxer) {
	const auto median = boxer.getMedianBox();
	PRINT("Median box is box with side %f and height %f (volum: %f)", median->side, median->height, median->volum());
}

int main(int argc, char *argv[]) {
	if (argc != ARGS_COUNT) {
		PRINT("Usage: manma.exe <input_file_path>");
		return 1;
	}

	PRINT("Reading input file %s", argv[1]);

	boxer::Boxer boxer;

	std::ifstream infile(argv[1]);
	std::string line;
	while (std::getline(infile, line)) {
		PRINT(">>> %s", line.c_str());
		Input input(parse(line));
		switch (input.cmd) {
		case InputCmd::Insert:
			PRINT("Performing insert with side %f, heghit %f", input.args[0], input.args[1]);
			boxer.insertBox(std::make_shared<boxer::Box>(input.args[0], input.args[1]));
			boxer.display();
			break;
		case InputCmd::Remove:
			PRINT("Performing remove with side %f, heghit %f", input.args[0], input.args[1]);
			boxer.removeBox(boxer::Box(input.args[0], input.args[1]));
			boxer.display();
			break;
		case InputCmd::Get:
			PRINT("Performing get with side %f, heghit %f", input.args[0], input.args[1]);
			runGetBox(boxer, input.args[0], input.args[1]);
			break;
		case InputCmd::Check:
			PRINT("Performing check with side %f, heghit %f", input.args[0], input.args[1]);
			PRINT("Box exists? %d", boxer.checkBox(boxer::Box(input.args[0], input.args[1])));
			break;
		case InputCmd::Median:
			PRINT("Performing get median");
			runMedian(boxer);
			break;
		default:
			break;
		}
	}
	return 0;
}

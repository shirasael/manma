#include "Output.h"
#include "Input.h"
#include <fstream>
#include <sstream>

const int ARGS_COUNT = 2;


int main(int argc, char *argv[]) {
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
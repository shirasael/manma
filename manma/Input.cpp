#include "Input.h"
#include <sstream>

void upper(std::string& str) {
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
}

std::vector<std::string> split(const std::string& s, char delimiter) {
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

Input parse(const std::string& line) {
	auto brac = line.find("(");
	std::string cmd(line.substr(0, brac));
	upper(cmd);
	std::vector<double> args;
	for (auto& s : split(line.substr(brac + 1, line.size() - 1), ',')) {
		args.push_back(strtod(s.c_str(), nullptr));
	}
	return Input {
		INPUT_CMD.at(cmd),
		args
	};
}

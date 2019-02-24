#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <map>

const std::string INSERT_BOX("INSERTBOX");
const std::string REMOVE_BOX("REMOVEBOX");
const std::string GET_BOX("GETBOX");
const std::string CHECK_BOX("CHECKBOX");
const std::string GET_MEDIAN_BOX("GETMEDIANBOX");

enum class InputCmd {
	Insert,
	Remove,
	Get,
	Check,
	Median
};

const std::map<std::string, InputCmd> INPUT_CMD {
	{ INSERT_BOX, InputCmd::Insert },
	{ REMOVE_BOX, InputCmd::Remove },
	{ GET_BOX, InputCmd::Get },
	{ CHECK_BOX, InputCmd::Check },
	{ GET_MEDIAN_BOX, InputCmd::Median },
};


struct Input {
	const InputCmd cmd;
	const std::vector<double> args;
};

Input parse(const std::string& line);
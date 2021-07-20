#include "../include/Interpreter.hpp"

Statement Interpreter::parse(const std::string& input) const {
	std::string operation;
	std::string value;
	std::stringstream ss(input);
	getline(ss, operation,' ');
	getline(ss,value,' ');

	if(operation.length() > 0) {

	} else {
		throw std::invalid_argument("Invalid operation");
	}

	if(value.length() > 0) {

	} else {
		throw std::invalid_argument("Invalid value");
	}  

	return Statement(Operation::GET,0);
}
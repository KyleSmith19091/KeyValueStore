#include "../include/Statement.hpp"

Statement::Statement(Operation op, int v) {
	this->operation = op;
	this->value = v;
}

std::string Statement::getString() noexcept {
	std::string operationString = "";
	if(this->operation == Operation::GET) {
		operationString = "GET";		
	} else if(this->operation == Operation::SET) {
		operationString = "SET";
	} else if(this->operation == Operation::PUT) {
		operationString = "PUT";
	} else {
		operationString = "UNKNOWN";
	}

	return operationString + " " + std::to_string(this->value);
}
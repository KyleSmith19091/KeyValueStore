#include "../include/Interpreter.hpp"

Statement Interpreter::parse(const std::string& input) {
	std::string operation;
	std::string value;
	std::stringstream ss(input);
	getline(ss, operation,' ');
	getline(ss,value,' ');

	Operation op = getOperation(operation);
	if(op == Operation::UNKNOWN) {
		return Statement(Operation::UNKNOWN,-1);
	}

	Value v = determineValue(value);
	if(v == Value::INVALID) {
		return Statement(Operation::UNKNOWN,-1);
	}

	return Statement(op,stoi(value));
}

Operation Interpreter::getOperation(const std::string& operation) noexcept {
	if(operation == "GET") {
		return Operation::GET;
	} else if(operation == "SET") {
		return Operation::SET;
	} else if(operation == "PUT") {
		return Operation::PUT;
	} else {
		return Operation::UNKNOWN;
	}
}

Value Interpreter::determineValue(const std::string& value) noexcept {
	try
	{
		stoi(value);
	}
	catch(const std::exception& e)
	{
		return Value::INVALID;
	}
	
	return Value::VALID;
}
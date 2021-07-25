#include "../include/Interpreter.hpp"

Statement Interpreter::parse(const std::string& input) {
	std::string temp;
	std::string operation = "";
	std::string value = "";
	std::string key = "";
	std::stringstream ss(input);

	int numArgs = -1;

	while(getline(ss,temp,' ')) {
		if(numArgs == -1) {
			operation = temp;	
			numArgs++;
		} else if(numArgs == 0) {
			key = temp;
			numArgs++;
		} else if(numArgs == 1) {
			value = temp;
			numArgs++;
		} else {
			return Statement(Operation::UNKNOWN); // Too many arguments
		}
	}
	numArgs++;

	Operation op = getOperation(operation);
	if(op == Operation::UNKNOWN) {
		return Statement(Operation::UNKNOWN);
	}else if(op == Operation::EXIT) {
		return Statement(Operation::EXIT);
	} else if(op == Operation::EMPTY) {
		return Statement(Operation::EMPTY);
	}	

	// Key must consist of alphabetic characters
	std::string validKey = this->getKey(key);
	if(validKey.empty()) {
		return Statement(Operation::UNKNOWN);
	}

	if (numArgs == 2) { // If number arguments is two, we either GET || DELETE 
		if (op != Operation::GET && op != Operation::DELETE) { // If we don't GET || DELETE ==> ERROR
			return Statement(Operation::UNKNOWN);
		} else {
			return Statement(op, validKey);
		}
	} else if (numArgs == 3) { // Three argument => Write operation
		if(op != Operation::SET && op != Operation::PUT) { // Must be write operation SET, PUT 
			return Statement(Operation::UNKNOWN);
		} else {
			if(getValue(value) == Value::VALID) { // Check that the value is numeric
				return Statement(op,validKey,value);
			} else {
				return Statement(UNKNOWN);
			}
		}
	}

	return Statement(Operation::UNKNOWN);
}

Operation Interpreter::getOperation(const std::string& operation) noexcept {
	if(operation == "GET") {
		return Operation::GET;
	} else if(operation == "SET") {
		return Operation::SET;
	} else if(operation == "PUT") {
		return Operation::PUT;
	} else if(operation == "DELETE") {
		return Operation::DELETE;
	}else if(operation == "EXIT") {
		return Operation::EXIT; 
	} else if(operation.empty()) {
		return Operation::EMPTY;
	} else {
		return Operation::UNKNOWN;
	}
}

std::string Interpreter::getKey(const std::string& k) noexcept {
	for (size_t i = 0; i < k.length(); i++) {
		int c = (int)k[i];
		if((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) { 
			return k;	
		} 
	}
	return std::string();
}

// TODO: Might need to adapt this
Value Interpreter::getValue(const std::string& value) {
	return Value::VALID;	
}
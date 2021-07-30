#include "../include/Interpreter.hpp"
#include "../include/StringUtils.hpp"

Statement Interpreter::parse(const std::string& input) {
	std::string operation = "";
	std::string key = "";
	std::string value = "";
	int numArgs = -1;

	// Tokenise the input
	tokenise(input,operation,key,value,numArgs);

	// Get Operation type
	Operation op = getOperation(operation);

	// Check if we have an unary operation
	if(isUnaryOperation(op)) {
		if(numArgs > 1) { // Unary operation takes no arguments
			throw std::invalid_argument("Unary Operator: Too Many Arguments");
		} else {
			return Statement(op); // Statement complete
		}
	}

	// Key must consist of only alphabetic characters
	std::string validKey = this->getKey(key);
	if(validKey.empty()) { // Indicates a non-valid string
		throw std::invalid_argument("Invalid Key: Key should only consist of alphabetic characters");
	}

	if (numArgs == 2) { // If number arguments is two, we either GET || DELETE 
		return prepareBinaryStatement(op,validKey);
	} else if (numArgs >= 3) { // Three arguments => Write operation

		if(op == Operation::GET || op == Operation::DELETE) { // Check for attempt of binary operation
			throw std::invalid_argument("Invalid Key: Keys must not contain spaces");
		}

		return prepareWriteStatement(op,validKey,value);
	}

	// Undefined Operation
	return Statement(Operation::UNKNOWN);
}

// Determine operation type from string
Operation Interpreter::getOperation(const std::string& operation) const noexcept {
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
	} else if(operation == "PRINT") {
		return Operation::PRINT;
	} else if(operation == "BEGIN") {
		return Operation::BEGIN;
	} else if(operation == "COMMIT") {
		return Operation::COMMIT;
	} else if(operation == "ROLLBACK") {
		return Operation::ROLLBACK;
	} else if(operation == "END") {
		return Operation::END;
	} else if(operation.empty()) {
		return Operation::EMPTY;
	} else if(operation == "CLEAR") {
		return Operation::CLEAR;	
	} else {
		return Operation::UNKNOWN;
	}
}

// Determine if key consists of alphabetic characters
std::string Interpreter::getKey(const std::string& k) const noexcept {
	bool valid = true;
	for (size_t i = 0; i < k.length(); i++) {
		int c = (int)k[i];
		if(!isalpha(c)) { 
			return std::string();
		} 
	}
	return k;
}

// TODO: Might need to adapt this
Value Interpreter::getValue(const std::string& value) const noexcept {
	return Value::VALID;	
}

// Tokenise => Extract Operation, key, value and number of arguments from input
void Interpreter::tokenise(const std::string& input, std::string& operation, std::string& key, std::string& value, int& numArgs) {
	std::string temp;
	std::stringstream ss(input);

	while(getline(ss,temp,' ')) { 
		if(numArgs == -1) {
			operation = temp;	
			operation = StringUtils::toUpperCase(operation);
			numArgs++;
		} else if(numArgs == 0) {
			key = temp;
			numArgs++;
		} else { // Read rest of the input
			value += temp + " ";
			numArgs++;
		} 
	}
	numArgs++;
}

// Prepare statement from unary operation
bool Interpreter::isUnaryOperation(const Operation& op) const noexcept {
	bool isUnary = false;
	if(op == Operation::UNKNOWN) {
		return !isUnary;
	}else if(op == Operation::EXIT) {
		return !isUnary;
	} else if(op == Operation::EMPTY) {
		return !isUnary;
	} else if(op == Operation::PRINT) {
		return !isUnary;
	} else if(op == Operation::BEGIN) {
		return !isUnary;
	} else if(op == Operation::END) {
		return !isUnary;
	} else if(op == Operation::ROLLBACK) {
		return !isUnary;
	} else if(op == Operation::COMMIT) {
		return !isUnary;
	} else if(op == Operation::CLEAR) {
		return !isUnary;
	}
	return isUnary;
}

// Prepare a statement object to represent a read
Statement Interpreter::prepareBinaryStatement(const Operation& op, const std::string& key) const noexcept {
	if (op != Operation::GET && op != Operation::DELETE) { // If we don't GET || DELETE ==> ERROR
		return Statement(Operation::UNKNOWN);
	} else {
		return Statement(op, key);
	}
}

// Prepare a statement object to represent a write
Statement Interpreter::prepareWriteStatement(const Operation& op, const std::string& key, const std::string& value) const noexcept {
	if(op != Operation::SET && op != Operation::PUT) { // Must be write operation SET, PUT 
			return Statement(Operation::UNKNOWN);
		} else {
			if (getValue(value) == Value::VALID) { 
				return Statement(op,key,value);
			} else {
				return Statement(UNKNOWN);
			}
	}
}
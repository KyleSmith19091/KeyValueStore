#ifndef STATEMENT_HPP
#define STATEMENT_HPP 

#include "Operation.hpp"

#include <string>
#include <sstream>
#include <iostream>

class Statement {

	public: 
		Operation operation;
		std::string value;
		std::string key;

		Statement() {};

		Statement(Operation op) {
			this->operation = op;
			this->key = "";
			this->value = "";
		};

		Statement(Operation op, std::string k) {
			this->operation = op;
			this->key = k;
			this->value = "";
		};

		Statement(Operation op, std::string k, std::string v) {
			this->operation = op;
			this->key = k;
			this->value = v;
		};

		std::string getString() noexcept {
			std::string operationString = "";
			if(this->operation == Operation::GET) {
				operationString = "GET";		
			} else if(this->operation == Operation::SET) {
				operationString = "SET";
			} else if(this->operation == Operation::PUT) {
				operationString = "PUT";
			} else if(this->operation == Operation::DELETE) {
				operationString = "DELETE";
			} else {
				operationString = "UNKNOWN";
			}
			return operationString + " " + this->value;
		};
};

#endif
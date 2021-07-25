#ifndef STATEMENT_HPP
#define STATEMENT_HPP 

#include "Operation.hpp"

#include <string>
#include <sstream>
#include <iostream>

class Statement {
	private: 

	public: 
		Operation operation;
		int value;
		std::string key;
		Statement(Operation);
		Statement(Operation, std::string);
		Statement(Operation, std::string, int);
		std::string getString() noexcept;
};

#endif
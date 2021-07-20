#ifndef STATEMENT_HPP
#define STATEMENT_HPP 

#include "Operation.hpp"

#include <string>
#include <sstream>
#include <iostream>

class Statement {
	private: 
		Operation operation;
		int value;

	public: 
		Statement(Operation op, int v);
		std::string getString() noexcept;
};

#endif
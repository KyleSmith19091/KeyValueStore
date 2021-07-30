#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP 

#include "Statement.hpp"
#include "Value.hpp"

#include <string>

class Interpreter {
	private:
		Operation getOperation(const std::string&) const noexcept;
		Value getValue(const std::string&) const noexcept;
		std::string getKey(const std::string&) const noexcept;
		void tokenise(const std::string&, std::string&, std::string&, std::string&, int&);
		bool isUnaryOperation(const Operation&) const noexcept;
		Statement prepareReadStatement(const Operation&, const std::string&) const noexcept;
		Statement prepareWriteStatement(const Operation&, const std::string&, const std::string&) const noexcept;

	public:
		Statement parse(const std::string&);
};

#endif
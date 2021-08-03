#ifndef SHELL_HPP
#define SHELL_HPP 

#include "Interpreter.hpp"
#include "Statement.hpp"
#include "KeyValue.hpp"
#include "ANSIColorTable.h"

#include <string>
#include <iostream>
#include <csignal>
#include <ctime>

class Shell {
	private:
		std::string prompt;
		void clear();
		void createSignalListeners();
		void printPrompt();
		void showOutput(const std::string& output, const bool = false);
		Statement getUserInput(std::string&, Interpreter&);

		void showActiveTransaction(Transaction*&);
		void startNewTransaction(KeyValue&, Transaction*&);
		void endTransaction(KeyValue&, Transaction*&);
		void rollbackTransaction(Transaction*&);
		void commitTransaction(KeyValue&, Transaction*&);
		void readWriteOperation(Statement& s, KeyValue&, Transaction*&);

	public:
		Shell(const std::string&);
		void init();
};

#endif
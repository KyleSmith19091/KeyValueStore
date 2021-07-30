#ifndef SHELL_HPP
#define SHELL_HPP 

#include "../include/Interpreter.hpp"
#include "../include/Statement.hpp"
#include "../include/KeyValue.hpp"

#include <string>
#include <iostream>
#include <csignal>

class Shell {
	private:
		std::string prompt;
		void clear();
		void createSignalListeners();
		void printPrompt();
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
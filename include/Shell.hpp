#ifndef SHELL_HPP
#define SHELL_HPP 

#include <string>
#include <iostream>
#include <csignal>

class Shell {
	private:
		std::string prompt;

	public:
		Shell(const std::string&);
		void init();
};

#endif
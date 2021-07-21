#include "../include/Shell.hpp"
#include "../include/Interpreter.hpp"
#include "../include/Statement.hpp"

Shell::Shell(const std::string& prompt) {
	this->prompt = prompt;
}

void Shell::init() {
	std::string input = "";
	Interpreter interpreter;

	signal(SIGINT, [](int sigNum) {
		std::cout << "Doing cleanup!\n";
   		exit(sigNum);
	});

	while (true) {
		std::cout << prompt + " ";
		getline(std::cin,input);
		Statement s = interpreter.parse(input);

		if(s.operation != Operation::UNKNOWN) {
			std::cerr << s.getString() << "\n";
		} else {
			std::cerr << "INVALID STATEMENT!\n";
		}
	}

}
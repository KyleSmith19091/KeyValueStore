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

		try {
			Statement s = interpreter.parse(input);
		} catch (const std::exception& e) {
			std::cerr << e.what() << '\n';
		}
	}

}
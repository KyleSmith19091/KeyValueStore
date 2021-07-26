#include "../include/Shell.hpp"
#include "../include/Interpreter.hpp"
#include "../include/Statement.hpp"
#include "../include/KeyValue.hpp"

// Give Shell custom prompt value
Shell::Shell(const std::string& prompt) {
	this->prompt = prompt;
}

void Shell::init() {
	std::string input = "";
	Interpreter interpreter;

	KeyValue keyValue;

	// Signal Interrupt listeners
	// Ctrl+C Listener (sigNum=2)
	signal(SIGINT, [](int sigNum) {
		std::cout << "\nDoing cleanup!\n";
   		exit(0);
	});

	// EXIT typed out, raised manually (sigNum=3) 
	signal(SIGQUIT, [](int sigNum) {
		std::cout << "\nDoing cleanup!\n";
		exit(0);
	});

	// Active Transaction Pointer
	Transaction *tx = keyValue.getActiveTransaction();	

	while (true) {
		std::cout << prompt + " ";
		getline(std::cin,input);
		Statement s = interpreter.parse(input);

		if(s.operation == Operation::EXIT) { // EXIT 
			raise(SIGQUIT);
		} else if(s.operation == Operation::EMPTY) { // No Input
			continue;
		} else if(s.operation == Operation::PRINT) { // Prints active transaction
			if(tx != NULL) {
				std::cerr << tx->getTransactionString() << "\n";
			} else {
				std::cerr << "** No Active Transaction **\n";
			}
		} else if(s.operation != Operation::UNKNOWN) { // Valid Input

			if(tx == nullptr) { // No active transactions, create one
				tx = new Transaction();
				keyValue.addTransaction(tx); // Push transaction onto stack
			} 

			if(s.operation == Operation::GET) { // Read operation
				try
				{
					std::string value = tx->readLocalStore(s);
					std::cerr << "= " <<  value << "\n";
				}
				catch(const std::out_of_range& e) {
					std::cerr << "!! Key Not Found !!\n";
				}
				
			} else { // Must be a write operation then
				tx->writeLocalStore(s);
			}

		} else {
			std::cerr << "!! INVALID STATEMENT!\n";
		}

	}

}
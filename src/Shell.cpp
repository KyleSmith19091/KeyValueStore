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

		Statement s;

		try {
			s = interpreter.parse(input);
		} catch(const std::exception& e) {
			std::cerr << "!! " << e.what() << " !!\n";
			continue;
		}

		if(s.operation == Operation::EXIT) { // EXIT 
			raise(SIGQUIT);
		} else if(s.operation == Operation::EMPTY) { // No Input
			continue;
		} else if(s.operation == Operation::PRINT) { // Prints active transaction
			if(tx != nullptr) { 
				std::cerr << tx->getTransactionString() << "\n";
			} else {
				std::cerr << "** No Active Transaction **\n";
			}
		} else if(s.operation == Operation::BEGIN) { // Starts a new transaction
			tx = (tx == nullptr) ? new Transaction() : new Transaction(*tx);
			keyValue.addTransaction(tx);
			std::cerr << "ADDED NEW TRANSACTION\n";
		} else if(s.operation == Operation::END) {
			if(tx != nullptr) {
				tx = keyValue.removeTransaction();
				if(tx == nullptr) {
					std::cerr << "** No Active Transaction **\n";
				}
			} else {
				std::cerr << "** No Active Transaction **\n";
			}
		} else if(s.operation == Operation::ROLLBACK) {
			if(tx != nullptr) {
				tx->rollbackChanges();
			}	
		} else if(s.operation == Operation::COMMIT) {
			if(tx != nullptr) {
				keyValue.commitTransaction(tx);
				tx = keyValue.removeTransaction();
				std::cerr << keyValue.getGlobalStoreString() << "\n";
			}
		}else if(s.operation != Operation::UNKNOWN) { // Valid Input

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
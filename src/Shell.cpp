#include "../include/Shell.hpp"

// Give Shell custom prompt value
Shell::Shell(const std::string& prompt) {
	this->prompt = prompt;
}

void Shell::init() {
	std::string input = "";
	Interpreter interpreter;
	KeyValue keyValue;

	// Create listeners for signals generated in the shell
	createSignalListeners();

	// Active Transaction Pointer
	Transaction *tx = keyValue.getActiveTransaction();	

	// REPL
	while (true) {

		// Show Prompt
		printPrompt();

		// Generate statement from user input
		Statement s = getUserInput(input,interpreter);

		// Determine what to do from statement
		if(s.operation == Operation::EXIT) {              // EXIT 
			raise(SIGQUIT); 
		} else if(s.operation == Operation::EMPTY) {      // No Input
			continue;
		} else if(s.operation == Operation::PRINT) {      // Prints active transaction
			showActiveTransaction(tx);
		} else if(s.operation == Operation::BEGIN) {      // Starts a new transaction
			startNewTransaction(keyValue, tx);
		} else if(s.operation == Operation::CLEAR) {      // Clear the 'shell' output
			clear();
		}else if(s.operation == Operation::END) {         // END Current transaction
			endTransaction(keyValue, tx);	
		} else if(s.operation == Operation::ROLLBACK) {   // Rollback the changes of current transaction
			rollbackTransaction(tx);
		} else if(s.operation == Operation::COMMIT) {     // Commit the changes of current transaction
			commitTransaction(keyValue, tx);
		}else if(s.operation != Operation::UNKNOWN) {     // Valid Input
			readWriteOperation(s,keyValue,tx);
		} else {									      // Invalid Operation hit	
			std::cerr << "!! INVALID STATEMENT!\n";
		}
	}

}

// Clear shell output
void Shell::clear() {
	#if defined _WIN32
		system("cls");
	#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
		system("clear");
	#elif defined (__APPLE__)
		system("clear");
	#endif
}

// Signal Interrupt listeners
void Shell::createSignalListeners() {

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

}

// Show prompt to user in stdout
void Shell::printPrompt() {
	std::cout << prompt + " ";
}

// Get and parse user input to a Statement
Statement Shell::getUserInput(std::string& input, Interpreter& interpreter) {
	getline(std::cin,input);
	try {
		return interpreter.parse(input);
	} catch(const std::exception& e) {
		std::cerr << "!! " << e.what() << " !!\n";
		return Statement(Operation::UNKNOWN);
	}
}

// Print local store from active transaction  
void Shell::showActiveTransaction(Transaction*& tx) {
	if(tx != nullptr) { 
		std::cerr << tx->getTransactionString() << "\n";
	} else {
		std::cerr << "** No Active Transaction **\n";
	}
}

// Start a new transaction
void Shell::startNewTransaction(KeyValue& keyValue, Transaction*& tx) {
	tx = (tx == nullptr) ? new Transaction() : new Transaction(*tx);
	keyValue.addTransaction(tx);
	std::cerr << "ADDED NEW TRANSACTION\n";
}

// End the current active transaction
void Shell::endTransaction(KeyValue& keyValue, Transaction*& tx) {
	if(tx != nullptr) {
		tx = keyValue.removeTransaction();
		if(tx == nullptr) {
			std::cerr << "** No Active Transaction **\n";
		}
	} else {
		std::cerr << "** No Active Transaction **\n";
	}
}

// Rollback the changes made to local store of the current transaction
void Shell::rollbackTransaction(Transaction*& tx) {
	if(tx != nullptr) {
		tx->rollbackChanges();
	}
}

// Commit the changes made in local store of the current transaction to global store
void Shell::commitTransaction(KeyValue& keyValue, Transaction*& tx) {
	if(tx != nullptr) {
		keyValue.commitTransaction(tx);
		tx = keyValue.removeTransaction();
		std::cerr << keyValue.getGlobalStoreString() << "\n";
	}
}

// Handle a read/write statement
void Shell::readWriteOperation(Statement& s, KeyValue& keyValue, Transaction*& tx) {
	if(tx == nullptr) { // No active transactions, create one
		tx = new Transaction();
		keyValue.addTransaction(tx); // Push transaction onto stack
	} 

	if(s.operation == Operation::GET) { // Read operation
		try {
			std::string value = tx->readLocalStore(s);
			std::cerr << "= " <<  value << "\n";
		} catch(const std::out_of_range& e) {
			std::cerr << "!! Key Not Found !!\n";
		}
	} else { // Must be a write operation then
		tx->writeLocalStore(s);
	}
}
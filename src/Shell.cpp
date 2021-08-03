#include "../include/Shell.hpp"

#define DEBUG

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
			showOutput("INVALID STATEMENT",true);
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
	std::time_t t = std::time(0); 
	std::tm* now = std::localtime(&t);
	std::cout << BGRN << now->tm_hour << ":" << now->tm_min << reset << " ";
	std::cout << BLU << prompt + " " << reset;
}

// Shows user output to error stream rather std::out
void Shell::showOutput(const std::string& output, const bool error) {
	if(error) {
		std::cerr << BRED << "!! " << output << "\n";
	} else {
		std::cerr << BGRN << output << "\n";
	}	
}

// Get and parse user input to a Statement
Statement Shell::getUserInput(std::string& input, Interpreter& interpreter) {
	getline(std::cin,input);
	try {
		return interpreter.parse(input);
	} catch(const std::exception& e) {
		showOutput(e.what(), true);
		return Statement(Operation::UNKNOWN);
	}
}

// Print local store from active transaction  
void Shell::showActiveTransaction(Transaction*& tx) {
	if(tx != nullptr) { 
		showOutput(tx->getTransactionString());
	} else {
		showOutput("No Active Transaction",true);
	}
}

// Start a new transaction
void Shell::startNewTransaction(KeyValue& keyValue, Transaction*& tx) {
	tx = (tx == nullptr) ? new Transaction() : new Transaction(*tx);
	keyValue.addTransaction(tx);
	showOutput("New Transaction Added");
}

// End the current active transaction
void Shell::endTransaction(KeyValue& keyValue, Transaction*& tx) {
	if(tx != nullptr) {
		tx = keyValue.removeTransaction();
	} else {
		showOutput("No Active Transaction",true);
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
		// Add data to global store
		keyValue.commitTransaction(tx);

		// Pop transaction off stack
		tx = keyValue.removeTransaction();

		// Printing for debugging
		#ifdef DEBUG
			showOutput(keyValue.getGlobalStoreString());
		#endif
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
			std::cerr << value << "\n";
		} catch(const std::out_of_range& e) {
			showOutput("Key Not Found",true);
		}
	} else { // Must be a write operation then
		tx->writeLocalStore(s);
	}
}
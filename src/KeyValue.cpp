#include "../include/KeyValue.hpp"

KeyValue::KeyValue() {}

// THis might be a bit extreme, might have to write transactions to a file
KeyValue::~KeyValue() {
	delete transactions;
}

// Add a new transaction to the top of the stack
void KeyValue::addTransaction(Transaction* t) { // O(1)
	transactions->push(new Transaction(t));	
}

// Get 'Top' transaction from transaction stack
Transaction* KeyValue::getActiveTransaction() const { // O(1)
	return transactions->peek() == nullptr ? nullptr : transactions->peek()->val;
}

// Pop 'Top' transaction from transaction stack
Transaction* KeyValue::removeTransaction() { // O(1)
	if(this->getActiveTransaction() == nullptr) {
		return nullptr;
	} else {
 		return transactions->pop()->val;
	}
}

// Get number of 'active' transactions from the stack 
int KeyValue::getNumTransactions() { // O(n), n is num transactions
	return transactions->size();
}

// Commit the transaction to the global store
void KeyValue::commitTransaction(Transaction* t) { // O(m), m is number of operations in transaction
	std::unordered_map<std::string,std::string> m = t->getLocalStore();

	for(std::unordered_map<std::string,std::string>::iterator it = m.begin(); it != m.end(); ++it) {
		try {
			this->globalStore.at(it->first);
			this->globalStore[it->first] = it->second;
		} catch(const std::out_of_range& e) {
			this->globalStore.insert(std::make_pair(it->first,it->second));
		}
	}
}

// Print contents of the global store
std::string KeyValue::getGlobalStoreString() { 
	std::string output = "";
	for(std::unordered_map<std::string,std::string>::const_iterator it = this->globalStore.begin(); it != this->globalStore.end(); ++it) {
		output += "[" + it->first + "] => " + it->second + "\n";	
	}
	return output;
}
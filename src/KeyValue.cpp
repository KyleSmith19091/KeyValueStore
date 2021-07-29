#include "../include/KeyValue.hpp"

KeyValue::KeyValue() {}

// THis might be a bit extreme, might have to write transactions to a file
KeyValue::~KeyValue() {
	delete transactions;
}

// Add a new transaction to the top of the stack
void KeyValue::addTransaction(Transaction* t) {
	transactions->push(new Transaction(t));	
}

// Get 'Top' transaction from transaction stack
Transaction* KeyValue::getActiveTransaction() const {
	return transactions->peek() == nullptr ? nullptr : transactions->peek()->val;
}

// Pop 'Top' transaction from transaction stack
Transaction* KeyValue::removeTransaction() {
	if(this->getActiveTransaction() == nullptr) {
		return nullptr;
	} else {
 		return transactions->pop()->val;
	}
}

int KeyValue::getNumTransactions() {
	return transactions->size();
}

void KeyValue::commitTransaction(Transaction* t) {
	std::unordered_map<std::string,std::string> m = t->getLocalStore();

	for(std::unordered_map<std::string,std::string>::iterator it = m.begin(); it != m.end(); ++it) {
		std::cerr << it->first << " " << it->second << "\n";
		this->globalStore.insert(std::make_pair(it->first,it->second));
	}
	 
}



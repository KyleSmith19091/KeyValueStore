#include "../include/Transaction.hpp"

// Start transaction with initial operation
Transaction::Transaction() noexcept {}

// Start transaction with context of previous transaction
Transaction::Transaction(const Transaction& tx) {	
	this->store = tx.getLocalStore();
}

// Wrapper around convertMapToString() for more 'semantic' code
std::string Transaction::getTransactionString() const noexcept {
	std::string output = "";
	for(citer i = this->store.cbegin(); i != this->store.cend(); ++i){
		output += "[" + i->first + "] => " + std::to_string(i->second);	
	}
	return output;
}

// Local store functions //

// Set given key to value, can also be used to update
void Transaction::set (const std::string& key, int value) {
	this->store[key] = value;
}

// Get value given key
int Transaction::get (const std::string& key) const {
	return this->store.at(key);
}

// Delete given key
void Transaction::deleteKey (const std::string& key) {
	this->store.erase(key);
}

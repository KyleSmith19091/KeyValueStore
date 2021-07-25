#include "../include/Transaction.hpp"

// Create initial transaction
Transaction::Transaction() noexcept {}

// Start transaction with context of previous transaction
Transaction::Transaction(const Transaction& tx) {	
	this->store = tx.getLocalStore();
}

// Transaction map to string conversion
std::string Transaction::getTransactionString() const noexcept {
	std::string output = "";
	for(citer i = this->store.cbegin(); i != this->store.cend(); ++i){
		output += "[" + i->first + "] => " + i->second + "\n";	
	}
	return output;
}

// Local store getter
std::unordered_map<std::string,std::string> Transaction::getLocalStore() const noexcept {
	return this->store;
}

// Read Statement
std::string Transaction::readLocalStore(const Statement& s) const {
	return get(s.key); 
}

// Write Statement
void Transaction::writeLocalStore(const Statement& s) {
	if(s.operation == Operation::SET) {
		set(s.key, s.value);
	} else if(s.operation == Operation::DELETE) {
		deleteKey(s.key);
	}
}

// Local store functions //
// Set given key to value, can also be used to update
void Transaction::set (const std::string& key, const std::string& value) {
	this->store[key] = value;
}

// Get value given key
std::string Transaction::get (const std::string& key) const {
	return this->store.at(key);
}

// Delete given key
void Transaction::deleteKey (const std::string& key) {
	this->store.erase(key);
}
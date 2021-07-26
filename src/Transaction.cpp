#include "../include/Transaction.hpp"

// Create initial transaction
Transaction::Transaction() noexcept {
}

// Start transaction with context of previous transaction
Transaction::Transaction(const Transaction& tx) {	
	this->store = tx.getLocalStore();
}

// Destructor
Transaction::~Transaction() {
}

// Transaction map to string conversion
std::string Transaction::getTransactionString() {
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
	if(s.operation == Operation::SET) { // Set can update and set a value
		try {
			get(s.key);
			updateKey(s.key, s.value);
		} catch(const std::out_of_range& e) {
			set(s.key, s.value);
		}
	} else if(s.operation == Operation::DELETE) {
		deleteKey(s.key);
	} else {
		std::cerr << "!! Undefined Write Operation\n";
	}
}

// Local store functions //
// Set given key to value, can also be used to update
void Transaction::set (const std::string& key, const std::string& value) {
	this->store.insert(std::make_pair(key, value));
}

// Get value given key
std::string Transaction::get (const std::string& key) const {
	return this->store.at(key);
}

// Delete given key
void Transaction::deleteKey (const std::string& key) {
	this->store.erase(key);
}

// Update value for given key
void Transaction::updateKey(const std::string& key, const std::string& value) {
	this->store[key] = value;
}
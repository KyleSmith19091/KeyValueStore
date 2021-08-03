#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP
#define citer std::unordered_map<std::string,std::string>::const_iterator

#include "Statement.hpp"

#include <unordered_map>
#include <string>

// Class representing an active transaction
class Transaction{
	private:
		// Local store => Will be written to global store on commit
		std::unordered_map<std::string,std::string> store;

		// Set given key to value, can also be used to update
		void set (const std::string& key, const std::string& value) noexcept {
			this->store.insert(std::make_pair(key, value));
		};

		// Get value given key
		std::string get (const std::string& key) const {
			try {
				return this->store.at(key);
			} catch(const std::out_of_range& e) {
				throw e;
			}
		};

		// Delete given key
		void deleteKey (const std::string& key) noexcept {
			this->store.erase(key);
		}

		// Update given key to value
		void updateKey (const std::string& key, const std::string& value) noexcept {
			this->store[key] = value;
		};

	public:
		// Start transaction with initial operation
		Transaction() noexcept {}; 

		// Start transaction with context of previous transaction
		Transaction(const Transaction* tx) {
			this->store = std::unordered_map<std::string,std::string>(tx->getLocalStore());
		};

		// Destructor
		~Transaction() {};

		// Wrapper around convertMapToString() for more 'semantic' code
		std::string getTransactionString() const noexcept {
			std::string output = "";
			for(citer i = this->store.cbegin(); i != this->store.cend(); ++i){
				output += "[" + i->first + "] => " + i->second + "\n";	
			}
			return output;
		}

		// Local store getter
		std::unordered_map<std::string,std::string> getLocalStore() const noexcept {
			return this->store;
		};

		// GET statement to read data from store
		std::string readLocalStore(const Statement& s) const {
			return get(s.key); 
		};

		// Any statement that writes data to store
		void writeLocalStore(const Statement& s) {
			if(s.operation == Operation::SET) { // Set can update and set a value
				try {
					get(s.key);
					updateKey(s.key, s.value);
				} catch(const std::out_of_range& e) {
					set(s.key, s.value);
				}
			} else if(s.operation == Operation::DELETE) {
				deleteKey(s.key);
			} else if(s.operation == Operation::PUT) {
				updateKey(s.key, s.value);
			} else {
				std::cerr << "!! Undefined Write Operation\n";
			}
		};

		// Discard changes made to local store
		void rollbackChanges() noexcept {
			this->store.clear();
		};

};
#endif
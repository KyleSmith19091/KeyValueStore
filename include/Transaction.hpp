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
		void set (const std::string& key, const std::string& value);

		// Get value given key
		std::string get (const std::string& key) const;

		// Delete given key
		void deleteKey (const std::string& key); 

		// Update given key to value
		void updateKey (const std::string& key, const std::string& value);

	public:
		// Start transaction with initial operation
		Transaction() noexcept; 

		// Start transaction with context of previous transaction
		Transaction(const Transaction&);

		// Destructor
		~Transaction();

		// Wrapper around convertMapToString() for more 'semantic' code
		std::string getTransactionString();

		// Local store getter
		std::unordered_map<std::string,std::string> getLocalStore() const noexcept;

		// GET statement to read data from store
		std::string readLocalStore(const Statement&) const;

		void writeLocalStore(const Statement&);


};
#endif
#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP
#define citer std::unordered_map<std::string,int>::const_iterator

#include "Statement.hpp"

#include <unordered_map>
#include <string>

// Class representing an active transaction
class Transaction{
	private:
		// Local store => Will be written to global store on commit
		std::unordered_map<std::string,int> store;

		// Set given key to value, can also be used to update
		void set (const std::string& key, int value);

		// Get value given key
		int get (const std::string& key) const;

		// Delete given key
		void deleteKey (const std::string& key); 

	public:
		// Start transaction with initial operation
		Transaction() noexcept; 

		// Start transaction with context of previous transaction
		Transaction(const Transaction&);

		// Wrapper around convertMapToString() for more 'semantic' code
		std::string getTransactionString() const noexcept;

		// Local store getter
		std::unordered_map<std::string,int> getLocalStore() const noexcept;

		// GET statement to read data from store
		int readLocalStore(const Statement&) const;

		void writeLocalStore(const Statement&);


};
#endif
#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP
#define citer std::unordered_map<std::string,std::string>::const_iterator

#include <unordered_map>
#include <string>

// Class representing an active transaction
class Transaction{
	private:
		// Local store => Will be written to global store on commit
		std::unordered_map<std::string,std::string> store;

		// Convert the local store for debugging
		std::string convertMapToString() const noexcept {
			std::string output = "";
			for(citer i = this->store.cbegin(); i != this->store.cend(); ++i){
				output += "[" + i->first + "] => " + i->second;	
			}
			return output;
		}

	public:
		// Start transaction with initial operation
		Transaction(const std::string& op, const std::string& value) noexcept {
			store[op] = value;
		}

		// Wrapper around convertMapToString() for more 'semantic' code
		std::string getTransactionString() const noexcept {
			return convertMapToString();
		}
};
#endif
#ifndef KEYVALUE_HPP
#define KEYVALUE_HPP 

#include "./Stack.hpp"
#include "./Transaction.hpp"

#include <unordered_map>
#include <string>

class KeyValue {
	private:
		Stack<Transaction>* transactions = new Stack<Transaction>();
		std::unordered_map<std::string,std::string> globalStore;
			
	public:
		KeyValue();
		~KeyValue();
		void addTransaction(Transaction* t);
};

#endif
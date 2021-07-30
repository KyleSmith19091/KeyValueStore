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
		KeyValue() {};

		~KeyValue() {
			delete transactions;
		};

		void addTransaction(Transaction* t) {
			transactions->push(new Transaction(t));	
		};

		Transaction* getActiveTransaction() const {
			return transactions->peek() == nullptr ? nullptr : transactions->peek()->val;
		};

		Transaction* removeTransaction() {
			if(this->getActiveTransaction() == nullptr) {
				return nullptr;
			} else {
 				return transactions->pop()->val;
			}
		};

		int getNumTransactions() {
			return transactions->size();
		};

		void commitTransaction(Transaction* t) {
			std::unordered_map<std::string,std::string> m = t->getLocalStore();

			if(m.size() == 0) {
				std::cerr << "** Nothing to commit **\n";
				return;
			}

			for(std::unordered_map<std::string,std::string>::iterator it = m.begin(); it != m.end(); ++it) {
				try {
					this->globalStore.at(it->first);
					this->globalStore[it->first] = it->second;
				} catch(const std::out_of_range& e) {
					this->globalStore.insert(std::make_pair(it->first,it->second));
				}
			}
		};

		std::string getGlobalStoreString() {
			std::string output = "";
			for(std::unordered_map<std::string,std::string>::const_iterator it = this->globalStore.begin(); it != this->globalStore.end(); ++it) {
				output += "[" + it->first + "] => " + it->second + "\n";	
			}
			return output;
		};
};

#endif
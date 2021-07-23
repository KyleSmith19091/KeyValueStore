#include "../include/KeyValue.hpp"

KeyValue::KeyValue() {}

// THis might be a bit extreme, might have to write transactions to a file
KeyValue::~KeyValue() {
	delete transactions;
}

// Add a new transaction to the top of the stack
void KeyValue::addTransaction(Transaction* t) {
	transactions->push(t);	
}



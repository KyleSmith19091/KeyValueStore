#include <iostream>
#include "../include/Stack.hpp"
#include "../include/Node.hpp"
#include "../include/Transaction.hpp"

using namespace std;

int main()
{
	// Transaction stack test
	Stack<Transaction>* t = new Stack<Transaction>();
	t->push(new Transaction("k","v"));

	return 0;
}
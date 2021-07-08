#include <iostream>
#include "../include/Stack.hpp"
#include "../include/Node.hpp"

using namespace std;

int main()
{
	Stack *s = new Stack();

	s->push(new Node(3));
	s->push(new Node(4));
	s->push(new Node(5));
	s->push(new Node(6));
	s->pop();

	std::cout << s->getStackString() << "\n";

	return 0;
}
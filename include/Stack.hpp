#ifndef STACK_HPP
#define STACK_HPP
#include "Node.hpp"
class Stack
{
private:
	// Top of stack
	Node *top;

	// Bottom of stack
	Node *bottom;

public:
	// Default Constructor
	Stack()
	{
		this->top = nullptr;
		this->bottom = nullptr;
	}

	// Overloaded Constructor
	Stack(Node *n)
	{
		this->top = new Node(n);
		this->bottom = this->top;
	}

	// Destructor
	~Stack()
	{
		delete this->bottom;
		delete this->top;
	}

	// Push new node on to the stack
	void push(Node *n)
	{
		Node *newNode = new Node(n);

		// Empty stack case
		if (this->top == nullptr)
		{
			this->top = newNode;
			this->bottom = newNode;
			this->bottom->next = this->top;
			return;
		}
		else if (this->bottom == this->top) // One node case
		{
			this->top->next = newNode;
			this->top = newNode;
			return;
		}

		this->top->next = newNode;
		this->top = newNode;
	}

	Node *pop()
	{
		if (this->top == nullptr)
		{
			std::cerr << "Popping off empty stack!\n";
			return nullptr;
		}
		else if (this->top->next == this->bottom || this->bottom == this->top)
		{
			Node *oldHead = this->top;
			this->top = nullptr;
			this->bottom = nullptr;
			return oldHead;
		}

		Node *oldHead = this->top;
		Node *tempNode = this->bottom;
		while (tempNode->next != oldHead)
		{
			tempNode = tempNode->next;
		}

		this->top = tempNode;
		this->top->next = nullptr;
		return oldHead;
	}

	std::string getStackString()
	{
		if (this->top == nullptr)
		{
			return "";
		}

		if (this->top == this->bottom)
		{
			return std::to_string(this->top->val);
		}

		std::string sReturn = "";

		Node *tempNode = this->bottom;
		while (tempNode != nullptr)
		{
			sReturn += std::to_string(tempNode->val) + " ";
			tempNode = tempNode->next;
		}
		return sReturn;
	}
};
#endif
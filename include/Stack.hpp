#ifndef STACK_HPP
#define STACK_HPP

#include "Node.hpp"

template<class T>
class Stack
{
private:
	// Top of stack
	Node<T> *top;

	// Bottom of stack
	Node<T> *bottom;

public:
	// Default Constructor
	Stack()
	{
		this->top = nullptr;
		this->bottom = nullptr;
	}

	// Overloaded Constructor
	Stack(Node<T> *n)
	{
		this->top = new Node<T>(n);
		this->bottom = this->top;
	}

	// Destructor
	~Stack()
	{
		delete this->bottom;
		delete this->top;
	}

	// Push new node on to the stack
	void push(T *n)
	{
		Node<T> *newNode = new Node<T>(*n);

		// Empty stack case
		if (this->top == nullptr)
		{
			this->top = newNode;
			this->bottom = newNode;
			this->bottom->next = this->top;
			return;
		}

		// Non empty stack
		this->top->next = newNode;
		this->top = newNode;
	}

	// Remove top node from stack
	Node<T> *pop()
	{
		// Removing from empty stack
		if (this->top == nullptr)
		{
			std::cerr << "Popping off empty stack!\n";
			return nullptr;
		}
		else if (this->top->next == this->bottom || this->bottom == this->top) // One node case
		{
			Node<T> *oldHead = this->top;
			this->top = nullptr;
			this->bottom = nullptr;
			return oldHead;
		}

		Node<T> *oldHead = this->top;
		Node<T> *tempNode = this->bottom;
		while (tempNode->next != oldHead)
		{
			tempNode = tempNode->next;
		}

		this->top = tempNode;
		this->top->next = nullptr;
		return oldHead;
	}

	bool isEmpty() const noexcept {
		return this->top == nullptr;
	}

};
#endif
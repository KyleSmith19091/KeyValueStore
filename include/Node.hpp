#ifndef NODE_HPP
#define NODE_HPP
class Node
{

public:
	Node *next;
	int val;
	Node(int v, Node *n = nullptr)
	{
		this->val = v;
		this->next = n;
	}

	Node(Node *n)
	{
		this->val = n->val;
		this->next = n->next;
	}
};
#endif
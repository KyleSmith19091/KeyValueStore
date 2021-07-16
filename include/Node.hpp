#ifndef NODE_HPP
#define NODE_HPP
template<class T>
class Node
{
public:
	Node *next;
	T *val;

	Node(T v, Node *n = nullptr)
	{
		this->val = new T(v);
		this->next = n;
	}

	Node(Node *n)
	{
		this->val = n->val;
		this->next = n->next;
	}
};
#endif
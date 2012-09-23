#include "Node.h"


Node::Node()
{
	next_ = prev_ = this;
	shape = new Shape();
}

void Node::insert_after(Node* current, Shape* shape)
{
	Node* insertedNode = new Node();
	insertedNode->shape = shape;
	insertedNode->next_ = current->next_;
	current->next_ = insertedNode;
}
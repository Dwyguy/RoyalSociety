#include "Node.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Node::Node()
{
	next_ = prev_ = this;
	shape = new Shape((rand()%800 + 1), (rand()%600 + 1), (rand()%200 + 1));
}

void Node::insert_after(Node* insert, Node* sentinel)
{
	Node* temp = sentinel->prev_;
	insert->next_ = sentinel;
	insert->prev_ = temp;
	insert->prev_->next_ = insert;
}

void Node::reverse(Node* sentinel)
{
	Node* cur = sentinel;

	do
	{
		Node* temp = cur->next_;
		cur->next_ = cur->prev_;
		cur->prev_ = temp;
		cur = cur->prev_;
	}while(cur != sentinel);
}
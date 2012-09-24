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
	insert->next_ = sentinel;
	insert->prev_ = sentinel->prev_;
	sentinel->prev_->next_ = insert;
	sentinel->prev_ = insert;
	/*Node* temp = sentinel->prev_;
	insert->next_ = sentinel;
	insert->prev_ = temp;
	//insert->prev_->next_ = insert;
	sentinel->prev_ = insert;*/
}

void Node::reverse(Node* sentinel)
{
	Node* temp;
	Node* cur = sentinel;

	do
	{
		temp = cur->next_;
		cur->next_ = cur->prev_;
		cur->prev_ = temp;
		cur = cur->prev_;
	}while(cur != sentinel);
}
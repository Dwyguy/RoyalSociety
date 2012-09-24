#include "Node.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Node::Node()
{
	next_ = prev_ = this;
	shape = new Shape((rand()%800 + 1), (rand()%600 + 1), (rand()%300 + 1));
}

void Node::insert_after(Node* current, Shape* shape)
{
	Node* insertedNode = new Node();
	insertedNode->shape = shape;
	insertedNode->next_ = current->next_;
	current->next_ = insertedNode;
}
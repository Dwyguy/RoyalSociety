/**
* @file Node.cpp
* CSE 274 - Fall 2012
*
* @author Matthew Dwyer
* @date 9/24/2012
*
* @note This file is (c) 2012. It is licensed under the
* CC BY 3.0 license (http://creativecommons.org/licenses/by/3.0/),
* which means you are free to use, share, and remix it as long as you
* give attribution. Commercial uses are allowed.
*
*/

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
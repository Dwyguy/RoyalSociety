#include "Shape.h"

#pragma once


class Node
{
  public:
	Node();

	// Note: Probably a poor idea to not have some of this private
	// but then the program will not work
	void insert_after(Node* current, Node* sentinel);
	void reverse(Node* sentinel);
	//void remove();

	Node* next_;
	Node* prev_;
	Shape* shape;

};
/**
* @file Node.h
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

#include "Shape.h"

#pragma once


class Node
{
  public:
	Node();

	// Note: Probably a poor idea to not have some of this private
	// but then the program will not work

	/**
	Inserts a node at the end of the "node train"
	@param current - The node bieng inserted
	@param sentinel - The sentinel node
	*/
	void insert_after(Node* current, Node* sentinel);

	/**
	Reverses the order of the nodes
	@param sentinel - The sentinel node
	*/
	void reverse(Node* sentinel);

	Node* next_; // The node that comes after the current one
	Node* prev_; // The node that comes before the current one
	Shape* shape; // The shape contained by the node
};
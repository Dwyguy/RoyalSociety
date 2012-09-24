/**
* @file Shape.h
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

#pragma once


class Shape
{
public:
	/**
	Constructor for a Shape object
	@param x - The starting x coordinate of the shape
	@param y - The starting y coordinate of the shape
	@param radius - The radius (or length and width, as it is modified) of the shape
	*/
	Shape(int x, int y, int radius);

	/**
	Specifices a rectangle shape
	@param x - The starting x coordinate of the rectangle
	@param y - The starting y coordinate of the rectangle
	@param radius - The length and width, as it is modified of the rectangle
	*/
	void rectangle(int x, int y, int radius);


	int x;
	int y;
	int radius;
	int type;

};


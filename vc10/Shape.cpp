/**
* @file Shape.cpp
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
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Shape::Shape(int x, int y, int radius)
{
	rectangle(x, y, radius);
}

void Shape::rectangle(int ex, int ey, int eradius)
{
	x = ex;
	y = ey;
	radius = eradius; // Radius in this case means length of the rectangle
}
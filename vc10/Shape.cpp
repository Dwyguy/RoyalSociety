#include "Shape.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

//int shapeType = 0;

Shape::Shape(int x, int y, int radius)
{
	shapeType = (rand()%2) + 1;

	switch(shapeType)
	{
		case 1 : rectangle(x, y, radius);
			break;
		case 2 : circle(x, y, radius);
			break;
	}


}

void Shape::rectangle(int x, int y, int radius)
{
	x = (rand()%150) + 50;
	y = (rand()%150) + 50;
	radius = 0; // Radius in this case means length of the rectangle
	shapeType = 1;
}

void Shape::circle(int x, int y, int radius)
{
	// x is the radius
	x = (rand()%100) + 50;
	shapeType = 2;
}

void Shape::draw()
{
	if(shapeType == 1)
	{
	}
}

#include "Shape.h"

int shapeType = 0;

Shape::Shape(int x, int y, int radius)
{
	shapeType = (rand()%2) + 1;

	switch(shapeType)
	{
		case 1 : rectangle(int x, int y, int radius);
			break;
		case 2 : circle(int x, int y, int radius);
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

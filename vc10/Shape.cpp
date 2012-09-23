#include "Shape.h"

int shapeType = 0;

Shape::Shape()
{
	shapeType = (rand()%2) + 1;

	switch(shapeType)
	{
		case 1 : rectangle();
			break;
		case 2 : circle();
			break;
	}


}

void Shape::rectangle()
{
	x = (rand()%150) + 50;
	y = 1.5 * x;
	shapeType = 1;
}

void Shape::circle()
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

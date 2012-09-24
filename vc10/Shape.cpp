#include "Shape.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

//int shapeType = 0;

Shape::Shape(int x, int y, int radius)
{
	type = 1;

	switch(type)
	{
		case 1 : rectangle(x, y, radius);
			break;
		case 2 : circle(x, y, radius);
			break;
	}

}

void Shape::rectangle(int ex, int ey, int eradius)
{
	x = ex;
	y = ey;
	radius = eradius; // Radius in this case means length of the rectangle
	//shapeType = 1;
}

void Shape::circle(int x, int y, int radius)
{
	
}

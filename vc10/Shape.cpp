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
#pragma once
//#include "cinder\app\AppBasic.h"
//#include "cinder\gl\gl.h"

class Shape
{
public:
	Shape(int x, int y, int radius);
	void rectangle(int x, int y, int radius);
	void circle(int x, int y, int radius);

	int x;
	int y;
	int radius;
	int type;

};


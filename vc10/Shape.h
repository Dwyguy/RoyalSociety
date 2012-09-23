#pragma once
#include "cinder\app\AppBasic.h"
#include "cinder\gl\gl.h"

class Shape
{
public:
	Shape();
	void rectangle();
	void circle();
	void draw();
	void update();

	int x;
	int y;
	//int radius;

	//Color8u color;
	

};


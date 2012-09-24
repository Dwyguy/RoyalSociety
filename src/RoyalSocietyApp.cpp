#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"
#include "cinder\ImageIo.h"
#include "cinder/CinderResources.h"
#include "cinder/app/KeyEvent.h"
#include "cinder/Text.h"
#include "Node.h"
#include "Shape.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class RoyalSocietyApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void keyDown(KeyEvent event);
	void update();
	void draw();
	void prepareSettings(Settings* settings);
  
  private:
	Node* sentinel;
	Surface* mySurface_;
	Font* font;
	float brightness, greenValue;
	bool showMenu;

	static const int appWidth_ = 800;
	static const int appHeight_ = 600;
	static const int surfaceSize_ = 1024;

	/**
	Draws a rectangle on the screen.
	@param surfaceArray - A uint8_t array that gets the current Surface of the screen.
	@param x1, x2, y1, y2 - A starting or ending point of the rectangle, depending on their
		locations.
	@param c - A color parameter to set the color of the rectangle

	This method was copied over from a previous project,
	which can be found here: https://github.com/Dwyguy/CatPicture
	*/
	void drawRectangle(uint8_t* surfaceArray, int x1, int y1, int x2, int y2);

	/**
	Draws a circle on the screen.
	@param surfaceArray - A uint8_t array that gets the current Surface of the screen.
	@param centerX - The x-coordinate of the center of the circle
	@param centerY - The y-coordinate of the center of the circle
	@param radius - The radius of the circle
	@param c - A color parameter to set the color of the rectangle

	This method was copied over from a previous project,
	which can be found here: https://github.com/Dwyguy/CatPicture
	*/
	void drawCircle(uint8_t* surfaceArray, int centerX, int centerY, int radius);

	void drawGradient(uint8_t* surfaceArray);
	void findClickedRectangle(int x, int y);
	void ascend(Node* current);
};

void RoyalSocietyApp::prepareSettings(Settings* settings)
{
	(*settings).setWindowSize(appWidth_, appHeight_);
	(*settings).setResizable(false);
}

void RoyalSocietyApp::setup()
{
	srand(time(0));
	font = new Font("Palatino Linotype",30);
	brightness = 0.0;
	greenValue = 0.0;
	showMenu = true;

	sentinel = new Node();
	sentinel->next_ = sentinel;
	sentinel->prev_ = sentinel;
	//sentinel->shape = new Shape((rand()%150) + 50, (rand()%150) + 50, (rand()%150) + 50);

	mySurface_ = new Surface(surfaceSize_, surfaceSize_, false);
	//nodeCount_ = 1;

	uint8_t* surfaceArray = (*mySurface_).getData();
	drawGradient(surfaceArray); // Doing this just to give a nice gradient background

}

void RoyalSocietyApp::drawRectangle(uint8_t* surfaceArray, int x1, int y1, int x2, int y2)//, Color8u c)
{
	int startX = (x1 < x2) ? x1 : x2;
	int endX = (x1 < x2) ? x2 : x1;
	int startY = (y1 < y2) ? y1 : y2;
	int endY = (y1 < y2) ? y2 : y1;

	int r = rand()%255;
	int g = rand()%255;
	int b = rand()%255;

	if(endX < 0 || endY < 0)
		return;
	if(startX > appWidth_ || startY > appHeight_)
		return;
	if(endX >= appWidth_)
		endX = appWidth_ - 1;
	if(endY >= appHeight_)
		endY = appHeight_ - 1;

	// 100 means 100 pixels down
	for(int y = startY; y <= endY; y++)
	{
		for(int x = startX; x <= endX; x++)
		{
			int ribbon = 3 * (x + y * surfaceSize_);

			surfaceArray[ribbon] = r;
			surfaceArray[ribbon + 1] = g;
			surfaceArray[ribbon + 2] = b;
		}
	}
}

void RoyalSocietyApp::drawCircle(uint8_t* surfaceArray, int centerX, int centerY, int radius)
{
	// Make sure the radius isn't negative
	if(radius < 0)
		return;

	//Color8u c = Color8u(0, 255, 0);

	// As a not for interesting effects later, if you get rid of the
	// "- radius" in the initialization of the loop control variables
	// you get only a quarter of the circle (bottom right quadrant)

	for(int y = centerY - radius; y <= centerY + radius; y++)
	{
		for(int x = centerX - radius; x <= centerX + radius; x++)
		{
			// Taken by Prof. Brinkman's suggestion in his code to make sure
			// the array isn't accessed out of bounds (see documentation at top)
			if(y < 0 || x < 0 || x >= appWidth_ || y >= appHeight_)
				continue;

			int distance = (int)sqrt(pow((x - centerX), 2.0)  + pow((y - centerY), 2.0));

			if(distance <= radius)
			{
				int ribbon = 3 * (x + y * surfaceSize_);
				surfaceArray[ribbon] = 0;//c.r;
				surfaceArray[ribbon + 1] = 0;//c.g;
				surfaceArray[ribbon + 2] = 0;//c.b;
			}
		}
	}

}

void RoyalSocietyApp::drawGradient(uint8_t* surfaceArray)
{
	Color8u c = Color8u(0, 0, 0);
	
	for(int y = 0; y < surfaceSize_; y++)
	{
		for(int x = 0; x < appWidth_; x++)
		{
			int ribbon = 3 * (x + y * surfaceSize_);
			int special = (int)((256 * x) / appWidth_);

			surfaceArray[ribbon] = c.r ;//+ special;
			surfaceArray[ribbon + 1] = c.g;// + special;
			surfaceArray[ribbon + 2] = c.b + special;		
		}
	}
}

void RoyalSocietyApp::findClickedRectangle(int x, int y)
{
	Node* current = sentinel->prev_;
	int xcoord, ycoord, length, width;

	while(current != sentinel)
	{
		xcoord = current->shape->x;
		ycoord = current->shape->y;
		length = current->shape->radius * 1.5 + xcoord;
		width = current->shape->radius + ycoord;

		if(x > xcoord && x < width && x > ycoord && x < length)
		{
			current->insert_after(current, sentinel);
			current = sentinel;
		}
		current = current->prev_;
	}
}

void RoyalSocietyApp::ascend(Node* current)
{
	current->next_->prev_ = current->prev_;
	current->prev_->next_ = current->next_;

}

void RoyalSocietyApp::mouseDown( MouseEvent event )
{
	uint8_t* surfaceArray = (*mySurface_).getData();
	Node* newNode = new Node();
	sentinel->insert_after(newNode, sentinel);
	if(sentinel->shape->type == 1)
	{
		drawRectangle(surfaceArray, newNode->shape->x, newNode->shape->y, newNode->shape->radius * 1.5, newNode->shape->radius);
	}

	if(event.isLeftDown())
	{
	//	findClickedRectangle(event.getX(), event.getY());
	}
}


void RoyalSocietyApp::keyDown(KeyEvent event)
{
	char yup = event.getChar();
	if(yup == '/' || yup == '?')
	{
		if(showMenu)
			showMenu = false;
		else
			showMenu = true;
	}

	if(event.getCode() == KeyEvent::KEY_SPACE)
	{
		sentinel->reverse(sentinel);
	}

}

void RoyalSocietyApp::update()
{
	uint8_t* surfaceArray = (*mySurface_).getData();

	Node* temp = sentinel->next_;
	
	if(temp == sentinel)
	{
		//drawRectangle(surfaceArray, temp->shape->x, temp->shape->y, temp->shape->radius * 1.5, temp->shape->radius);
	}

	while(temp != sentinel)
	{
		drawRectangle(surfaceArray, temp->shape->x, temp->shape->y, temp->shape->radius * 1.5, temp->shape->radius);
		temp = temp->next_;
	}
}

void RoyalSocietyApp::draw()
{
	if(brightness < 1.0f && greenValue <= 0.0f)
	{
		brightness += 0.01f; // Raise red
	}
	else if(brightness >= 1.0f && greenValue < 1.0f)
	{
		//brightness = 1.0f;
		greenValue += 0.01f; // Raise to yellow
	}
	else if(greenValue >= 1.0f && brightness > 0.0f)
	{
		brightness -= 0.01f;
	}
	else if(greenValue > 0.0f)
	{
		greenValue -= 0.01f;
		brightness += 0.01f;
	}

	if(showMenu)
	{
		gl::clear(Color(0,0,0));
		gl::drawString("Welcome to the Royal Society!", Vec2f(250.0f,100.0f),Color(brightness,greenValue,0.0f), *font);
		gl::drawString("Press '?' to turn this menu off and on.", Vec2f(200.0f,150.0f),Color(brightness,greenValue,0.0f), *font);
		gl::drawString("Click to create new shapes on the screen!", Vec2f(180.0f,200.0f),Color(brightness,greenValue,0.0f), *font);
		gl::drawString("Want to reverse the order of the shapes? Hit spacebar.", Vec2f(100.0f,250.0f),Color(brightness,greenValue,0.0f), *font);
	}
	else
	{
		gl::clear(Color(0,0,0));
		gl::draw(*mySurface_);
	}
}

CINDER_APP_BASIC( RoyalSocietyApp, RendererGl )

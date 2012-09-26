/**
* @file RoyalSocetyApp.cpp
* CSE 274 - Fall 2012
* My solution for HW02
*
* @author Matthew Dwyer
* @date 9/24/2012
*
* @note This file is (c) 2012. It is licensed under the
* CC BY 3.0 license (http://creativecommons.org/licenses/by/3.0/),
* which means you are free to use, share, and remix it as long as you
* give attribution. Commercial uses are allowed.
*
* @note This project satisfies goals A, B, C, D, E, and K
*/

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"
#include "cinder/ImageIo.h"
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
	bool showMenu, raveMode;
	int shift;
	
	bool mouseClick; // JO: added mouse click flag

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
	Draws a gradient background on the Surface
	@param surfaceArray - A uint8_t array that gets the current Surface of the screen.

	This method was copied over from a previous project,
	which can be found here: https://github.com/Dwyguy/CatPicture
	*/
	void drawGradient(uint8_t* surfaceArray);

	/**
	Brings the node/shape on the bottom of the pile to the top, making it visible on the screen
	*/
	void ascend();
};

void RoyalSocietyApp::prepareSettings(Settings* settings)
{
	(*settings).setWindowSize(appWidth_, appHeight_);
	(*settings).setResizable(false);
}

void RoyalSocietyApp::setup()
{
	srand(time(0)); // Needed to seed for random numbers
	font = new Font("Palatino Linotype",30); // Cool looking font

	brightness = 0.0;
	greenValue = 0.0;
	showMenu = true;
	raveMode = false;
	
	mouseClick = false; // JO: initialize variable
	
	shift = 0;

	// Initializing sentinel
	sentinel = new Node();
	sentinel->next_ = sentinel;
	sentinel->prev_ = sentinel;

	mySurface_ = new Surface(surfaceSize_, surfaceSize_, false);

	uint8_t* surfaceArray = (*mySurface_).getData();
	drawGradient(surfaceArray); // Doing this just to give a nice gradient background
}

void RoyalSocietyApp::drawRectangle(uint8_t* surfaceArray, int x1, int y1, int x2, int y2)//, Color8u c)
{
	int startX = (x1 < x2) ? x1 : x2;
	int endX = (x1 < x2) ? x2 : x1;
	int startY = (y1 < y2) ? y1 : y2;
	int endY = (y1 < y2) ? y2 : y1;

	int r, g ,b;

	if(raveMode) // Flashy colors :)
	{
		r = rand()%255;
		g = rand()%255;
		b = rand()%255;
	}
	else // Using these variables creates some interesting effects when the shapes move around
	{
		r = startX;
		g = endX;
		b = startY;
	}

	if(endX < 0 || endY < 0)
		return;
	if(startX > appWidth_ || startY > appHeight_)
		return;
	if(startY <= 0 || endY <= 0)
		return;
	if(endX >= appWidth_)
		endX = appWidth_ - 1;
	if(endY >= appHeight_)
		endY = appHeight_ - 1;

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


// Just for decoration
void RoyalSocietyApp::drawGradient(uint8_t* surfaceArray)
{
	Color8u c = Color8u(0, 0, 0);
	
	for(int y = 0; y < surfaceSize_; y++)
	{
		for(int x = 0; x < appWidth_; x++)
		{
			int ribbon = 3 * (x + y * surfaceSize_);
			int special = (int)((256 * x) / appWidth_);

			surfaceArray[ribbon] = c.r;
			surfaceArray[ribbon + 1] = c.g;
			surfaceArray[ribbon + 2] = c.b + special;		
		}
	}
}

// Satisfies goal C
void RoyalSocietyApp::ascend()
{
	Node* current = sentinel->next_;
	sentinel->next_ = current->next_;
	sentinel->next_->prev_ = sentinel;
	sentinel->insert_after(current, sentinel);
}


void RoyalSocietyApp::mouseDown( MouseEvent event )
{
	mouseClick = true; // JO: set flag as true
}


void RoyalSocietyApp::keyDown(KeyEvent event)
{
	// Satisfies goal B
	// Pressing / or ? brings up or hides the menu
	if(event.getChar() == '/' || event.getChar() == '?')
	{
		if(showMenu)
			showMenu = false;
		else
			showMenu = true;
	}

	// Satisfies goal E
	// Pressing the spacebar causes a reverse
	if(event.getCode() == KeyEvent::KEY_SPACE)
	{
		sentinel->reverse(sentinel);
	}

	//Satisfies goal C
	if(event.getCode() == KeyEvent::KEY_UP)
		ascend();

	// Satisfies goals D and K... interestingly as possible
	if(event.getCode() == KeyEvent::KEY_LEFT && shift > -300 && shift < 300)
		shift--;
	if(event.getCode() == KeyEvent::KEY_RIGHT && shift > -300 && shift < 300)
		shift++;
	if(shift >= 300 || shift <= -300)
		shift = 0;

	// For funsies!
	if(event.getChar() == 'r')
	{
		if(raveMode)
			raveMode = false;
		else
			raveMode = true;
	}

}

void RoyalSocietyApp::update()
{
	/*
		JO: Moved code from mouseDown(). I don't know how much it matterns what method it's in, it just made
			more sense to me to have this in update().
	*/
	if(mouseClick)
	{
		mouseClick = false;
		uint8_t* surfaceArray = (*mySurface_).getData();

		Node* newNode = new Node();
		sentinel->insert_after(newNode, sentinel);
		if(sentinel->shape->type == 1) // Was put in place to add different shapes, but they didn't pan out
		{
			/*
				JO: Draw code should be in draw()
			*/
			drawRectangle(surfaceArray, newNode->shape->x, newNode->shape->y, newNode->shape->radius * 1.5, newNode->shape->radius);
		}
	}
	
	uint8_t* surfaceArray = (*mySurface_).getData();
	
	Node* temp = sentinel->next_;

	// Shift is added to create cool effects
	while(temp != sentinel)
	{
		/*
			JO: Draw code should be in draw(). It works fine this way, it's just standard to have all draw
				methods executed in draw().
		*/
		drawRectangle(surfaceArray, temp->shape->x + shift, temp->shape->y + shift, temp->shape->radius * 1.5 + shift, temp->shape->radius);
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

	// Cool intro messages
	if(showMenu)
	{
		gl::clear(Color(0,0,0));
		gl::drawString("Welcome to the Royal Society!", Vec2f(245.0f,100.0f),Color(brightness,greenValue,0.0f), *font);
		gl::drawString("Press '?' to turn this menu off and on.", Vec2f(215.0f,140.0f),Color(brightness,greenValue,0.0f), *font);
		gl::drawString("Click to create new shapes on the screen!", Vec2f(200.0f,180.0f),Color(brightness,greenValue,0.0f), *font);
		gl::drawString("Want to reverse the order of the shapes? Hit spacebar.", Vec2f(130.0f,220.0f),Color(brightness,greenValue,0.0f), *font);
		gl::drawString("Bringing the bottom shape to the top? Use the up arrow.", Vec2f(120.0f,260.0f),Color(brightness,greenValue,0.0f), *font);
		gl::drawString("Use the left and right arrows to make some interesting colors and effects.", Vec2f(30.0f,300.0f),Color(brightness,greenValue,0.0f), *font);
		gl::drawString("PRESS 'R' FOR RAVE MODE!!", Vec2f(250.0f,340.0f),Color(brightness,greenValue,0.0f), *font);
	}
	else
	{
		gl::clear(Color(0,0,0));
		gl::draw(*mySurface_);
	}
}

CINDER_APP_BASIC( RoyalSocietyApp, RendererGl )

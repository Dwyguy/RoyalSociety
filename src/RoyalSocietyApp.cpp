#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class RoyalSocietyApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void RoyalSocietyApp::setup()
{
}

void RoyalSocietyApp::mouseDown( MouseEvent event )
{
}

void RoyalSocietyApp::update()
{
}

void RoyalSocietyApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( RoyalSocietyApp, RendererGl )

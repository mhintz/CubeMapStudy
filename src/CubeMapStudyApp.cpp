#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CubeMapStudyApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void CubeMapStudyApp::setup()
{
}

void CubeMapStudyApp::mouseDown( MouseEvent event )
{
}

void CubeMapStudyApp::update()
{
}

void CubeMapStudyApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( CubeMapStudyApp, RendererGl )

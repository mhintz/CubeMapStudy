#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/CameraUi.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CubeMapStudyApp : public App {
  public:
	static void prepSettings(Settings * settings);

	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

	void keyDown(KeyEvent event) override;

	CameraPersp mCamera;
	CameraUi mUiCamera;

	gl::FboCubeMapRef mFbo;

	TriMeshRef mMesh;
	gl::GlslProgRef mShader;
};

void CubeMapStudyApp::prepSettings(Settings * settings) {
	settings->setTitle("Cube Map Study");
	settings->setFullScreen();
	settings->setHighDensityDisplayEnabled();
}

void CubeMapStudyApp::setup()
{
	mMesh = TriMesh::create(geom::Sphere().center(vec3(0)).subdivisions(60).radius(1.0f));

	mFbo = gl::FboCubeMap::create(600, 600);

	mCamera.lookAt(vec3(0, 0, 4), vec3(0), vec3(0, 1, 0));
	mUiCamera = CameraUi(& mCamera, getWindow());

	mShader = gl::GlslProg::create(loadAsset("passThrough_v.glsl"), loadAsset("cubeMapSample_f.glsl"));

	gl::enableDepth();
	gl::enableFaceCulling();
	gl::cullFace(GL_BACK);
}

void CubeMapStudyApp::mouseDown( MouseEvent event )
{
}

void CubeMapStudyApp::keyDown(KeyEvent event) {
	if (event.getCode() == KeyEvent::KEY_ESCAPE) {
		quit();
	}
}

void CubeMapStudyApp::update()
{

}

void CubeMapStudyApp::draw()
{
	mFbo->bindFramebufferFace(GL_TEXTURE_CUBE_MAP_POSITIVE_X);
	gl::clear(Color(1, 0, 0));

	mFbo->bindFramebufferFace(GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
	gl::clear(Color(0, 1, 0));

	mFbo->bindFramebufferFace(GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
	gl::clear(Color(0, 0, 1));

	mFbo->bindFramebufferFace(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
	gl::clear(Color(1, 1, 0));

	mFbo->bindFramebufferFace(GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
	gl::clear(Color(1, 0, 1));

	mFbo->bindFramebufferFace(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
	gl::clear(Color(0, 1, 1));

	mFbo->unbindFramebuffer();

	gl::setMatrices(mCamera);

	gl::clear( Color( 0, 0, 0 ) );

	gl::ScopedGlslProg scpShader(mShader);
	gl::ScopedTextureBind scpTex(mFbo->getTextureCubeMap());

	gl::draw(* mMesh.get());
}

CINDER_APP( CubeMapStudyApp, RendererGl, & CubeMapStudyApp::prepSettings )

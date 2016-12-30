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
	gl::VboMeshRef mPointMesh;
	gl::VboMeshRef mSphereMesh;
	gl::GlslProgRef mSdrUpdateCubeMap;
	gl::GlslProgRef mSdrRenderCubeMap;
};

static int const cubeMapSide = 600;

void CubeMapStudyApp::prepSettings(Settings * settings) {
	settings->setTitle("Cube Map Study");
	settings->setFullScreen();
	settings->setHighDensityDisplayEnabled();
}

void CubeMapStudyApp::setup()
{
	mSphereMesh = gl::VboMesh::create(geom::Sphere().center(vec3(0)).subdivisions(60).radius(1.0f));
	vec3 pointBuf[1] = { vec3(cubeMapSide / 2, cubeMapSide / 2, 0) };
	auto pointVbo = gl::Vbo::create(GL_ARRAY_BUFFER, sizeof(vec3), pointBuf, GL_STATIC_DRAW);
	auto pointVboLayout = geom::BufferLayout({ geom::AttribInfo(geom::POSITION, 3, 0, 0) });
	mPointMesh = gl::VboMesh::create(1, GL_POINTS, { { pointVboLayout, pointVbo } });

	auto colorTextureFormat = gl::TextureCubeMap::Format()
		.internalFormat(GL_RGB32F)
		.wrap(GL_CLAMP_TO_EDGE)
		.minFilter(GL_NEAREST)
		.magFilter(GL_NEAREST);

	auto fboFmt = gl::FboCubeMap::Format()
		.textureCubeMapFormat(colorTextureFormat)
		.disableDepth();

	mFbo = gl::FboCubeMap::create(cubeMapSide, cubeMapSide, fboFmt);

	mCamera.lookAt(vec3(0, 0, 4), vec3(0), vec3(0, 1, 0));
	mUiCamera = CameraUi(& mCamera, getWindow());

	mSdrUpdateCubeMap = gl::GlslProg::create(loadAsset("updateCubeMap_v.glsl"), loadAsset("updateCubeMap_f.glsl"), loadAsset("updateCubeMap_g.glsl"));
	mSdrRenderCubeMap = gl::GlslProg::create(loadAsset("cubeMapSample_v.glsl"), loadAsset("cubeMapSample_f.glsl"));

	gl::enableDepth();
	gl::enableFaceCulling();
	gl::cullFace(GL_BACK);

	// doesn't work :/
	mFbo->bindFramebufferFace(GL_TEXTURE_CUBE_MAP_POSITIVE_X);
	gl::clear(Color(1, 1, 1));

	mFbo->bindFramebufferFace(GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
	gl::clear(Color(1, 1, 1));

	mFbo->bindFramebufferFace(GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
	gl::clear(Color(1, 1, 1));

	mFbo->bindFramebufferFace(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
	gl::clear(Color(1, 1, 1));

	mFbo->bindFramebufferFace(GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
	gl::clear(Color(1, 1, 1));

	mFbo->bindFramebufferFace(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
	gl::clear(Color(1, 1, 1));

	mFbo->unbindFramebuffer();
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
	{
		gl::ScopedMatrices scpMat;
		gl::setMatricesWindow(cubeMapSide, cubeMapSide);
		gl::ScopedViewport scpView(0, 0, cubeMapSide, cubeMapSide);
		gl::ScopedGlslProg scpShader(mSdrUpdateCubeMap);

		mFbo->bindFramebuffer();

		// gl::clear(Color(0, 0, 0));

		gl::draw(mPointMesh);

		// mFbo->bindFramebufferFace(GL_TEXTURE_CUBE_MAP_POSITIVE_X);
		// gl::clear(Color(0, 0, 0));
		// mSdrUpdateCubeMap->uniform("cubeSide", 0);
		// gl::drawSolidRect(Rectf(0, 0, cubeMapSide, cubeMapSide));

		// mFbo->bindFramebufferFace(GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
		// gl::clear(Color(0, 0, 0));
		// mSdrUpdateCubeMap->uniform("cubeSide", 1);
		// gl::drawSolidRect(Rectf(0, 0, cubeMapSide, cubeMapSide));

		// mFbo->bindFramebufferFace(GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
		// gl::clear(Color(0, 0, 0));
		// mSdrUpdateCubeMap->uniform("cubeSide", 2);
		// gl::drawSolidRect(Rectf(0, 0, cubeMapSide, cubeMapSide));

		// mFbo->bindFramebufferFace(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
		// gl::clear(Color(0, 0, 0));
		// mSdrUpdateCubeMap->uniform("cubeSide", 3);
		// gl::drawSolidRect(Rectf(0, 0, cubeMapSide, cubeMapSide));

		// mFbo->bindFramebufferFace(GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
		// gl::clear(Color(0, 0, 0));
		// mSdrUpdateCubeMap->uniform("cubeSide", 4);
		// gl::drawSolidRect(Rectf(0, 0, cubeMapSide, cubeMapSide));

		// mFbo->bindFramebufferFace(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
		// gl::clear(Color(0, 0, 0));
		// mSdrUpdateCubeMap->uniform("cubeSide", 5);
		// gl::drawSolidRect(Rectf(0, 0, cubeMapSide, cubeMapSide));

		mFbo->unbindFramebuffer();
	}

	{
		gl::ScopedMatrices scpMat;
		gl::setMatrices(mCamera);

		gl::clear( Color( 0, 0, 0 ) );

		gl::ScopedGlslProg scpShader(mSdrRenderCubeMap);
		gl::ScopedTextureBind scpTex(mFbo->getTextureCubeMap());

		gl::draw(mSphereMesh);
	}
}

CINDER_APP( CubeMapStudyApp, RendererGl, & CubeMapStudyApp::prepSettings )

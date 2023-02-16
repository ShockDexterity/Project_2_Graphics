#include "ofApp.h"

void ofApp::reloadShaders()
{
	firstShader.load("shaders/temp.vert", "shaders/temp.frag");
	shadersNeedReload = false;
}

//--------------------------------------------------------------
void ofApp::setup()
{
	ofDisableArbTex();
	ofEnableDepthTest();
	susMesh.load("models/susImposter.ply");
}

//--------------------------------------------------------------
void ofApp::update()
{
	if (shadersNeedReload) { reloadShaders(); }
}

//--------------------------------------------------------------
void ofApp::draw()
{
	using namespace glm;

	const float width { static_cast<float>(ofGetViewportWidth()) };
	const float height { static_cast<float>(ofGetViewportHeight()) };
	const float aspect { width / height };

	mat4 view {};

	mat4 susModel { translate(vec3(0, 0, -5)) * rotate(radians(180.0f), vec3(1, 1, 1)) };
	mat4 susProj { perspective(radians(100.0f), aspect, 0.01f, 10.0f) };

	firstShader.begin();
	firstShader.setUniformMatrix4f("mvp", susProj * view * susModel);
	susMesh.draw();
	firstShader.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == '`') { shadersNeedReload = true; }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}

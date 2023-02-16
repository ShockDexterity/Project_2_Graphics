#include "ofApp.h"

void ofApp::reloadShaders()
{
	susShader.load("shaders/temp.vert", "shaders/temp.frag");
	sceneShader.load("shaders/temp.vert", "shaders/temp.frag");
	shadersNeedReload = false;
}

//--------------------------------------------------------------
void ofApp::setup()
{
	ofDisableArbTex();
	ofEnableDepthTest();
	susMesh.load("models/susImposter.ply");
	sceneMesh.load("models/scene.ply");
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

	time += ofGetLastFrameTime() * 100;
	mat4 susModel { translate(vec3(0, 0, -3)) * rotate(radians(-time), vec3(0, 1, 0)) };
	mat4 susProj { perspective(radians(100.0f), aspect, 0.01f, 10.0f) };


	susShader.begin();
	susShader.setUniformMatrix4f("mvp", susProj * view * susModel);
	susMesh.draw();
	susShader.end();

	mat4 sceneModel { translate(vec3(0,0,-5)) * rotate(radians(245.0f), vec3(0, 1, 0)) * rotate(radians(-10.0f),vec3(1,0,0)) };
	mat4 sceneProj { perspective(radians(90.0f), aspect, 0.01f, 10.0f) };
	sceneShader.begin();
	sceneShader.setUniformMatrix4f("mvp", sceneProj * view * sceneModel);
	sceneMesh.draw();
	sceneShader.end();
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

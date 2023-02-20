#include "ofApp.h"

void ofApp::reloadShaders()
{
	susShader.load("shaders/temp.vert", "shaders/temp.frag");
	sceneShader.load("shaders/temp.vert", "shaders/temp.frag");
	shadersNeedReload = false;
}

void ofApp::updateCameraRotation(float dx, float dy)
{
	using namespace glm;
	cameraHead += dx;
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
	auto window{ ofGetCurrentWindow() };
	if (shadersNeedReload) { reloadShaders(); }

	using namespace glm;

	// calculate world soace velocity
	vec3 velocityWorldSpace{ mat3(rotate(-cameraHead, vec3(0, 1, 0))) * velocity };

	// time since last frame
	float dt{ static_cast<float>(ofGetLastFrameTime()) };

	// update position
	position += velocityWorldSpace * dt;

}

//--------------------------------------------------------------
void ofApp::draw()
{
	using namespace glm;

	const float width{ static_cast<float>(ofGetViewportWidth()) };
	const float height{ static_cast<float>(ofGetViewportHeight()) };
	const float aspect{ width / height };


	mat4 view{rotate(cameraHead, vec3(0, 1, 0)) * translate(-position)};

	time += ofGetLastFrameTime() * 100;
	mat4 susModel{ translate(vec3(0, 0, -3)) * rotate(radians(-time), vec3(0, 1, 0)) };
	mat4 projection{ perspective(radians(100.0f), aspect, 0.01f, 10.0f) };


	susShader.begin();
	susShader.setUniformMatrix4f("mvp", projection * view * susModel);
	susMesh.draw();
	susShader.end();

	mat4 sceneModel{ translate(vec3(-2,0,-5)) * rotate(radians(245.0f), vec3(0, 1, 0)) * rotate(radians(-10.0f),vec3(1,0,0)) };
	// mat4 sceneProj { perspective(radians(90.0f), aspect, 0.01f, 10.0f) };
	sceneShader.begin();
	sceneShader.setUniformMatrix4f("mvp", projection * view * sceneModel);
	sceneMesh.draw();
	sceneShader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == '`') { shadersNeedReload = true; }

	if (key == 'w')
	{
		velocity.z = -1;
	}
	else if (key == 's')
	{
		velocity.z = 1;
	}
	else if (key == 'a')
	{
		velocity.x = -1;
	}
	else if (key == 'd')
	{
		velocity.x = 1;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	if (key == 'w' || key == 's')
	{
		velocity.z = 0;
	}
	else if (key == 'a' || key == 'd')
	{
		velocity.x = 0;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
	if (prevX != 0 && prevY != 0)
	{
		//update camera rotation based on mouse movement
		updateCameraRotation(mouseSensitivity * (x - prevX), mouseSensitivity * (y - prevY));
	}

	//remember where the mouse was this frame
	prevX = x;
	prevY = y;
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

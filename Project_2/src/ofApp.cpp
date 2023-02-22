#include "ofApp.h"

using namespace glm;

void ofApp::reloadShaders()
{
	susShader.load("shaders/models.vert", "shaders/models.frag");
	sceneShader.load("shaders/models.vert", "shaders/models.frag");
	shadersNeedReload = false;
}

void ofApp::updateCameraRotation(float dx, float dy)
{
	cameraHead += dx;
	cameraPitch += dy;
}

//--------------------------------------------------------------
void ofApp::setup()
{
	ofDisableArbTex();
	ofEnableDepthTest();

	susMesh.load("models/susImposter.ply");
	susVbo.setMesh(susMesh, GL_STATIC_DRAW);

	sceneMesh.load("models/scene.ply");

	/*
	Loading 6900 ofMesh's at once took a very long time
	Changing the vector to holding Vbo's decreased the load time dramatically.
	*/

	for (int i { 0 }; i < 6900; ++i)
	{
		susVbos.emplace_back();
		susVbos.at(i).setMesh(susMesh, GL_STATIC_DRAW);
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	// time since last frame
	const float dt { static_cast<float>(ofGetLastFrameTime()) };

	// Grabbing the current window
	auto window { ofGetCurrentWindow() };

	// calculate world space velocity
	const vec3 vCamHead { mat3(rotate(-cameraHead, vec3(0, 1, 0))) * velocity };
	const vec3 vCamPitch { mat3(rotate(cameraPitch, vec3(1, 0 , 0))) * velocity };

	// update position
	position += (vCamHead + vCamPitch) * dt;

	susVbo.drawElements(GL_TRIANGLES, susVbo.getNumIndices());

	if (shadersNeedReload) { reloadShaders(); }
}

//--------------------------------------------------------------
void ofApp::draw()
{
	// finding the aspect ratio of the viewport
	const float width { static_cast<float>(ofGetViewportWidth()) };
	const float height { static_cast<float>(ofGetViewportHeight()) };
	const float aspect { width / height };

	time += ofGetLastFrameTime() * 100;

	// constant view and projection for the models
	const mat4 view { rotate(cameraHead, vec3(0, 1, 0)) * rotate(cameraPitch, vec3(1, 0, 0)) };
	const mat4 projection { perspective(radians(100.0f), aspect, 0.01f, 10.0f) };

	// setting fog
	// float alpha { smoothstep(0.01f, 10.0f, 5.0f) };

	// drawing the amogus model
	susShader.begin();
	const mat4 susModel { translate(vec3(0, 0, -3)) * rotate(radians(-time), vec3(0, 1, 0)) };
	susShader.setUniformMatrix4f("mvp", projection * view * susModel);
	//susMesh.draw();
	for (unsigned int i { 0 }; i < susVbos.size(); ++i)
	{
		susVbos.at(i).draw(GL_TRIANGLES, 0, susVbo.getNumIndices());
	}
	susShader.end();

	mat4 sceneModel { translate(vec3(-2,0,-5)) * rotate(radians(245.0f), vec3(0, 1, 0)) * rotate(radians(-10.0f),vec3(1,0,0)) };
	// mat4 sceneProj { perspective(radians(90.0f), aspect, 0.01f, 10.0f) };
	sceneShader.begin();
	sceneShader.setUniformMatrix4f("mvp", projection * view * sceneModel);
	sceneMesh.draw();
	sceneShader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key)
	{
		case '`':
			shadersNeedReload = true; break;
		case 'w':
			velocity.z = -1; break;
		case 's':
			velocity.z = 1; break;
		case 'a': 
			velocity.x = -1; break;
		case 'd': 
			velocity.x = 1; break;
		default:
			break;
	}

	/*if (key == '`')
	{
		shadersNeedReload = true;
	}
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
	}*/
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	switch (key)
	{
		case 'w': velocity.z = 0; break;
		case 's': velocity.z = 0; break;

		case 'a': velocity.x = 0; break;
		case 'd': velocity.x = 0; break;
	}

	/*if (key == 'w' || key == 's')
	{
		velocity.z = 0;
	}
	else if (key == 'a' || key == 'd')
	{
		velocity.x = 0;
	}*/
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

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

	/*for (int i { 0 }; i < 100; ++i)
	{
		susVbos.emplace_back();
		susVbos.at(i).setMesh(susMesh, GL_STATIC_DRAW);
	}*/
}

//--------------------------------------------------------------
void ofApp::update()
{
	// time since last frame
	const float dt { static_cast<float>(ofGetLastFrameTime()) };

	// Grabbing the current window
	auto window { ofGetCurrentWindow() };

	// calculate world space velocity
	const mat3 vCamHead { mat3(rotate(-cameraHead, vec3(0, 1, 0))) };
	const mat3 vCamPitch { mat3(rotate(-cameraPitch, vec3(1, 0, 0))) };

	// update position
	position += (vCamPitch * vCamHead) * velocity * dt;

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
	const mat4 view { (rotate(cameraHead, vec3(0, 1, 0)) * rotate(cameraPitch, vec3(1, 0, 0))) * translate(-position) };
	const mat4 projection { perspective(radians(100.0f), aspect, 0.01f, 10.0f) };

	const mat4 susModel { glm::translate(vec3(0, 0, -3)) * rotate(radians(-time), vec3(0, 1, 0)) };
	const mat4 sceneModel { glm::translate(vec3(-2,0,-5)) * rotate(radians(245.0f), vec3(0, 1, 0)) * rotate(radians(-10.0f), vec3(1,0,0)) };

	// drawing the amogus model
	{
		//***********************************************************************************************************

		/*
			This is the proper stress test here. When trying to draw almost 7000 meshes, the frames per second
			were very low and was near impossible to move anywhere because the dt was so high, often overshooting
			wherever you meant to end up.
			
			When we switched to drawing Vbo's, the frames did certainly increase however there was still noticable lag,
			most likely because there are still almost 7000 different models being drawn on the screen, even if the fog
			reduces their alpha to 0.
		*/

		//***********************************************************************************************************

		/*std::vector<mat4> susModels {};
		for (int i { 1 }; i <= 6900; ++i)
		{
			susModels.emplace_back(glm::translate(vec3(0, 0, -3 * i)) * rotate(radians(-time), vec3(0, 1, 0)));
		}*/

		/*for (unsigned int i { 0 }; i < susModels.size(); ++i)
		{
			 susShader.begin();
			 susShader.setUniformMatrix4f("mvp", projection * view * susModels.at(i));
			 susShader.setUniformMatrix4f("mv", view * susModels.at(i));
			 // susMesh.draw();
			 susVbo.drawElements(GL_TRIANGLES, susVbo.getNumIndices());
			 susShader.end();
		}*/
		susShader.begin();
		susShader.setUniformMatrix4f("mvp", projection * view * susModel);
		susShader.setUniformMatrix4f("mv", view * susModel);
		susVbo.draw(GL_TRIANGLES, 0, susVbo.getNumIndices());
		susShader.end();
	}

	// drawing the rest of the scene
	{
		sceneShader.begin();
		sceneShader.setUniformMatrix4f("mvp", projection * view * sceneModel);
		sceneShader.setUniformMatrix4f("mv", view * sceneModel);
		sceneMesh.draw();
		sceneShader.end();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key)
	{
		case '`': shadersNeedReload = true; break;

		case 'w': velocity.z = -1; break;
		case 's': velocity.z = 1; break;

		case 'a': velocity.x = -1; break;
		case 'd': velocity.x = 1; break;

		default: break;
	}
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

		default: break;
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

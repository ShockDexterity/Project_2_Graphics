#pragma once

#include "ofMain.h"
#include <vector>
#include <GLFW/glfw3.h>

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

private:
	// among us mesh and shaders
	ofVbo susVbo {};
	ofMesh susMesh {};
	ofShader susShader {};

	// background scene mesh and shader
	ofMesh sceneMesh {};
	ofShader sceneShader {};

	float time { 0.0f };

	bool shadersNeedReload { true };
	void reloadShaders();

	// previous mouse pos
	int prevX { 0 };
	int prevZ { 0 };

	// How many radians of rotation correspon to a single pixel
	float mouseSensitivity { 0.02f };

	// current head direction of the camera in radians
	float cameraHead { 0 };

	// current pitch direction of the camera in radians
	float cameraPitch { 0 };

	// velocity of camera (from WASD)
	glm::vec3 velocity {};

	// position of camera in world space
	glm::vec3 position { 0, 0, 1 };

	// update camera rotation based on mouse movement
	void updateCameraRotation(float dx, float dy);

	// we need a lot of mongus models
	std::vector<ofVbo> susVbos {};

};

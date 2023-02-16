#pragma once

#include "ofMain.h"

struct CameraData
{
	glm::vec3 position;
	float rotation;
};

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
	ofMesh susMesh {};
	ofShader susShader {};

	ofMesh sceneMesh {};
	ofShader sceneShader {};

	float time { 0.0f };

	bool shadersNeedReload { true };
	void reloadShaders();

	CameraData camera;
	glm::mat4 buildViewMatrix(CameraData cam)
	{
		return glm::mat4();
	}
};

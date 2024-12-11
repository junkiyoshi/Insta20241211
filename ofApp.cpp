#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();
}
//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofTranslate(0, 50, 0);
	ofRotateX(300);

	for (int deg = 0; deg < 360; deg += 15) {

		ofFill();
		ofPushMatrix();
		ofRotateZ(deg);
		ofDrawCircle(glm::vec3(0, 250, 0), 8);
		ofPopMatrix();

		for (int i = 0; i < 5; i++) {

			auto noise_value = ofNoise(cos(deg * DEG_TO_RAD) * 0.5, sin(deg * DEG_TO_RAD) * 0.5, ofGetFrameNum() * 0.02 + i * 0.025);

			auto z = 0;
			if (noise_value >= 0.6) {

				z = ofMap(noise_value, 0.6, 1.0, 0, 250);
			}
			else if (noise_value <= 0.4) {

				z = ofMap(noise_value, 0.0, 0.4, -250, 0);
			}

			ofPushMatrix();

			ofRotateZ(deg);

			ofNoFill();
			ofSetColor(239);
			ofDrawCircle(glm::vec3(0, 250, z), ofMap(i, 0, 5, 10, 25));

			ofPopMatrix();
		}
	}

	this->cam.end();

	/*
	int start = 250;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
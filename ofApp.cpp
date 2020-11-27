#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();

	ofTrueTypeFont font;
	font.loadFont("fonts/Kazesawa-Bold.ttf", 28, true, true, true);

	string word = "01234567890123456789";
	for (int i = 0; i < (int)word.size(); i++) {

		this->path_list.push_back(font.getCharacterAsPoints(word[i], true, false));
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int radius = 150;
	for (auto y = -112; y <= 112; y += 28) {

		for (int deg = 0; deg < 360; deg += 6) {

			auto location = glm::vec3(0, y, -radius);
			auto rotation_y = glm::rotate(glm::mat4(), (float)(deg * DEG_TO_RAD), glm::vec3(0, 1, 0));
			location = glm::vec4(location, 0) * rotation_y;

			ofPushMatrix();
			ofTranslate(location);
			ofRotateY(180 - deg);
			ofRotateX(180);

			int noise_index = ofMap(ofNoise(location.y * 0.001, deg * 0.0005 + ofGetFrameNum() * 0.005), 0, 1, 0, path_list.size());
			int tmp_size = (2 * radius * PI) / 48;
			auto outline = path_list[noise_index].getOutline();
			
			if (location.z > 0) {
			
				ofSetColor(39);
			}
			else{

				ofSetColor(ofMap(location.z, 0, -150, 39, 239));
			}

			ofFill();
			ofBeginShape();
			for (int line_index = 0; line_index < outline.size(); line_index++) {

				if (line_index != 0) { ofNextContour(true); }

				auto vertices = outline[line_index].getVertices();
				for (int i = 0; i < vertices.size(); i++) {

					ofVertex((vertices[i] / 28 * tmp_size) + glm::vec2(tmp_size * -0.5, tmp_size * 0.5));
				}
			}
			ofEndShape(true);


			ofNoFill();
			ofSetColor(239);
			ofBeginShape();
			for (int line_index = 0; line_index < outline.size(); line_index++) {

				if (line_index != 0) { ofNextContour(true); }

				auto vertices = outline[line_index].getVertices();
				for (int i = 0; i < vertices.size(); i++) {

					ofVertex((vertices[i] / 28 * tmp_size) + glm::vec2(tmp_size * -0.5, tmp_size * 0.5));
				}
			}
			ofEndShape(true);

			ofPopMatrix();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
#pragma once

#include "ofMain.h"
#include "ofxCsv.h"
#include "ofxCsvRow.h"
#include "ofxJSONElement.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
private:
    int fileSize;
    ofImage p1;
    string filepath1;
    string jsoninfo1;
    string jsonname;
    vector<string> labels;

    bool isJson;
    bool isSaved;

    ofxJSONElement je1;
    ofxCsv csv1;
    
    vector<ofRectangle> rects;
    vector<ofPoint> points;
    
    float ratiox;
    float ratioy;
		
};

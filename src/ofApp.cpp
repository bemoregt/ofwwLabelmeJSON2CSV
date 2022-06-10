#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //ratiox= 1.0;
    //ratioy= 1.0;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    //float ratiox= 1024.0/2944;
    //float ratioy= 768.0/2352;
    
    // draw image
    ofEnableAntiAliasing();
    // draw selected image
    ofSetColor(255);
    p1.draw(1,1, 1024, 768);
    
    // show filename & json name
    ofEnableAntiAliasing();
    if (isJson) {
        ofSetColor(0, 0, 255);
        jsoninfo1= jsonname;
        ofDrawBitmapString(jsoninfo1, 30, 30);
    }else {
        jsoninfo1="No JSon ...";
        ofSetColor(0, 0, 0);
        ofDrawBitmapString(jsoninfo1, 30, 30);
    }
    
    // draw a box
    ofSetLineWidth(1);
    ofEnableAntiAliasing();
    for(int i=0; i< rects.size(); i++){
        ofFill();
        ofSetColor(255, 155, 55, 50);
        ofDrawRectangle(ratiox*rects[i].x, ratioy*rects[i].y,
                        ratiox*rects[i].width, ratioy*rects[i].height);
        ofNoFill();
        if(labels[i]=="ps"){
            ofSetColor(255, 0, 0);
        }else if(labels[i]=="norm"){
            ofSetColor(0, 255, 0);
        }else {
            ofSetColor(0, 0, 255);
        }
        
        ofDrawRectangle(ratiox*rects[i].x, ratioy*rects[i].y,
                        ratiox*rects[i].width, ratioy*rects[i].height);
   }
    
    // draw key points
    /*
    ofSetLineWidth(3);
    ofEnableAntiAliasing();
    ofNoFill();
    for(int i=0; i< points.size(); i++){
        ofSetColor(255, 0, 0);
        ofDrawCircle(points[i].x, points[i].y, 3);
        ofSetColor(255, 255, 0, 150);
        ofDrawBitmapString(ofToString(i), points[i].x+3, points[i].y-3);
   }
     */
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    ofxCsvRow row1;
    row1.clear();
    
    if(key == 's' || key =='S'){
        //

        for(int i=0; i<rects.size(); i++){
            row1.clear();
            row1.setString(0, filepath1);
            row1.setString(1, labels[i]);
            row1.setInt(2, rects[i].x);
            row1.setInt(3, rects[i].y);
            row1.setInt(4, rects[i].x+rects[i].width);
            row1.setInt(5, rects[i].y+rects[i].height);
            csv1.addRow(row1);
            csv1.save(filepath1+".csv");
        }
        
        isSaved =true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

    isJson = false;
    points.clear();
    rects.clear();
    labels.clear();
    //rect1.set(0,0,1,1);

    if( dragInfo.files.size() > 0 ){
        fileSize= dragInfo.files.size();
        filepath1= dragInfo.files[0];
        p1.load(filepath1);
        
        ratiox= 1024.0/p1.getWidth();
        ratioy= 768.0/p1.getHeight();
        ofLog() << fileSize << endl;
        
        ofSetWindowTitle(filepath1);
    }// if
    //
    if( dragInfo.files.size() == 2 ){
        jsonname = dragInfo.files[1];
        isJson =true;
    }
    
    if( isJson) {
        
        bool parsingOK = je1.open(jsonname);
        
        if (parsingOK)
        {
            ofLogNotice("ofApp::setup") << je1.getRawString();
            
            for(int i=0; i<je1["shapes"].size(); i++){
                // parse label
                labels.push_back(je1["shapes"][i]["label"].asString());
                // parse bbox
                int x1= je1["shapes"][i]["points"][0][0].asInt();
                int y1= je1["shapes"][i]["points"][0][1].asInt();
                int x2= je1["shapes"][i]["points"][1][0].asInt();
                int y2= je1["shapes"][i]["points"][1][1].asInt();
                rects.push_back(ofRectangle(x1, y1,(x2-x1),(y2-y1)));
            }
        }
    }
            // for test
            ofLog() << "value= 336:" << je1["shapes"][1]["points"][0][0].asInt();
}

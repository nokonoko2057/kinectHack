#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    if(!kinect.isConnected()){
        ofSystemAlertDialog("Error!!!!!");
        
    }
    
    ofxGuiSetDefaultWidth(300);
    ofxGuiSetDefaultHeight(18);
    
    gui.setup("Depth Masking Control");
    gui.setPosition(10,10);
   // gui.add(radius.set("Radius", 0, 0, 255));
    gui.add(near.set("near",0,0,255));
    gui.add(far.set("far",255,0,255));
    
  gui.add(color.set("color",ofColor(255,255,255,255),ofColor(0,0,0,0),ofColor(255,255,255,255)))
    ;
  
}

//--------------------------------------------------------------
void ofApp::update(){

    kinect.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    //kinect.draw(0, 0, ofGetWidth(),ofGetHeight());
    
    if (kinect.isFrameNew()) {
        cameraImage.setFromPixels(kinect.getPixels(), kinect.width, kinect.height, OF_IMAGE_COLOR);
        
        depthImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height, OF_IMAGE_GRAYSCALE);
        
        unsigned char * cameraPixcels = cameraImage.getPixels();
        unsigned char * depthPixcels = depthImage.getPixels();
        maskedImage.allocate(kinect.width, kinect.height, OF_IMAGE_COLOR);
        
        unsigned char * maskedPixels = maskedImage.getPixels();
        
        for (int i=0; i<kinect.width*kinect.height; i++) {
            if ((255-far.get()<depthPixcels[i])&&(depthPixcels[i]<255-near.get())) {
                maskedPixels[i*3]=cameraPixcels[i*3];
                maskedPixels[i*3+1]=cameraPixcels[i*3+1];
                maskedPixels[i*3+2]=cameraPixcels[i*3+2];
                
            }else{
                maskedPixels[i*3]=0;
                maskedPixels[i*3+1]=0;
                maskedPixels[i*3+2]=0;
            }
        }
        maskedImage.setFromPixels(maskedPixels, kinect.width, kinect.height, OF_IMAGE_COLOR);
        
    }
    cameraImage.draw(0, 0, kinect.width,kinect.height);
    depthImage.draw(0, kinect.height, kinect.width/2, kinect.height/2);
    
    ofSetColor(color);
    
    maskedImage.draw(kinect.width/2, kinect.height, kinect.width/2,kinect.height/2);
    ofSetColor(255);
    //ofCircle(ofGetWidth()/2, ofGetHeight()/2, radius.get());
    gui.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (key) {
        case ' ' :
            kinect.init();
            kinect.open();
            if (!kinect.isConnected()) {
                ofSystemAlertDialog("error:Kinect is not connected");
            }
            break;
            
        default:
            break;
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

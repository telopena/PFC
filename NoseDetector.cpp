#include "NoseDetector.h"


NoseDetector::NoseDetector(void) :Runnable()
{
	nose_classifier=NULL;
	String nose_cascade_name = "C:/Users/telo/Documents/Visual Studio 2012/Projects/Prueba_opencv/Release/haarcascade_mcs_nose.xml";
	nose_classifier=new CascadeClassifier();  
	nose_classifier->load( nose_cascade_name );
}


NoseDetector::~NoseDetector(void)
{
	if(nose_classifier!=NULL){delete(nose_classifier);nose_classifier=NULL;	}
}

void NoseDetector::Detect(){


	std::vector<Rect> v_nose;

	nose_classifier->detectMultiScale( frame_ROI, v_nose, 1.1, 2, 0 |CV_HAAR_FIND_BIGGEST_OBJECT, Size(18, 15) );

	setVector(v_nose);
}

void NoseDetector::setROI(Mat frame){
	frame_ROI=frame;
}

Mat NoseDetector::getROI(){
	return(frame_ROI);
}

void NoseDetector::setVector(std::vector<Rect> vector){
	my_noses=vector;
}

std::vector<Rect> NoseDetector::getVector(){
	return(my_noses);
}


void NoseDetector:: run(){

Detect();
}

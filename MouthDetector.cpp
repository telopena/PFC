#include "MouthDetector.h"


MouthDetector::MouthDetector(void) :Runnable()
{
	mouth_classifier=NULL;
	String mouth_cascade_name = "C:/Users/telo/Documents/Visual Studio 2012/Projects/Prueba_opencv/Release/haarcascade_mcs_mouth.xml";
	mouth_classifier=new CascadeClassifier();  
	mouth_classifier->load( mouth_cascade_name );
}


MouthDetector::~MouthDetector(void)
{
	if(mouth_classifier!=NULL){delete(mouth_classifier);mouth_classifier=NULL;	}
}

void MouthDetector::Detect(){

	std::vector<Rect> v_mouth;

	mouth_classifier->detectMultiScale( frame_ROI, v_mouth, 1.1, 2, 0 |CV_HAAR_FIND_BIGGEST_OBJECT, Size(22, 15) ); //22x15

	setVector(v_mouth);
}

void MouthDetector::setROI(Mat frame){
	frame_ROI=frame;
}

void MouthDetector::setVector(std::vector<Rect> vector){
	my_mouths=vector;

}

Mat MouthDetector::getROI(){
	return(frame_ROI);
}

std::vector<Rect> MouthDetector::getVector(){
	return(my_mouths);


}


void MouthDetector:: run(){

	Detect();
}

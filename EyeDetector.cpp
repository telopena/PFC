#include "EyeDetector.h"


EyeDetector::EyeDetector(int opcion) :Runnable()

{
	eye_classifier=NULL;
	String eye_cascade_name_r = "C:/Users/telo/Documents/Visual Studio 2012/Projects/Prueba_opencv/Release/haarcascade_mcs_righteye.xml";
	String eye_cascade_name_l= "C:/Users/telo/Documents/Visual Studio 2012/Projects/Prueba_opencv/Release/haarcascade_mcs_lefteye.xml";
	eye_classifier=new CascadeClassifier(); 
	if(opcion==0){eye_classifier->load(eye_cascade_name_r);}
	if(opcion==1){eye_classifier->load(eye_cascade_name_l);}

}


EyeDetector::~EyeDetector(void)
{
	if(eye_classifier!=NULL){delete(eye_classifier);eye_classifier=NULL;	}
}


void EyeDetector::Detect(){


	std::vector<Rect> v_eye;


	eye_classifier->detectMultiScale( frame_ROI, v_eye, 1.1, 2, 0 |CV_HAAR_FIND_BIGGEST_OBJECT, Size(18, 12) );


	setVector(v_eye);
}


void EyeDetector::setROI(Mat frame){
	frame_ROI=frame;
}

void EyeDetector::setVector(std::vector<Rect> vector){
	my_eyes=vector;
}

Mat EyeDetector::getROI(){
	return(frame_ROI);
}

std::vector<Rect> EyeDetector::getVector(){
	return(my_eyes);
}

void EyeDetector:: run(){

	Detect();
}


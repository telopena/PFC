#include "ProfileLeft.h"

ProfileLeft::ProfileLeft()

{
	profile_classifier = NULL;
	String aux="C:/Users/telo/Documents/Visual Studio 2012/Projects/Prueba_opencv/Release/lbpcascade_profileface.xml";
	profile_classifier = new CascadeClassifier();
	profile_classifier->load(aux);

}

ProfileLeft::~ProfileLeft(void) {
	if (profile_classifier != NULL) {
		delete (profile_classifier);
		profile_classifier = NULL;
	}

}

vector<Rect> ProfileLeft::Detect(Mat gray) {

	std::vector<Rect> profiles;

	profile_classifier->detectMultiScale(gray, profiles, 1.2, 2,
		CV_HAAR_SCALE_IMAGE |CV_HAAR_FIND_BIGGEST_OBJECT, Size(20, 34)); //20x34 //

	return (profiles);

}


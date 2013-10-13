#include "ProfileRigth.h"

ProfileRigth::ProfileRigth()

{
	profile_classifier = NULL;
	String aux="C:/Users/telo/Documents/Visual Studio 2012/Projects/Prueba_opencv/Release/lbpcascade_profileface.xml";
	profile_classifier = new CascadeClassifier();
	profile_classifier->load(aux);

}

ProfileRigth::~ProfileRigth(void) {
	if (profile_classifier != NULL) {
		delete (profile_classifier);
		profile_classifier = NULL;
	}

}

vector<Rect> ProfileRigth::Detect(Mat gray) {

	std::vector<Rect> profiles;

	flip(gray, gray, 1);

	profile_classifier->detectMultiScale(gray, profiles, 1.2, 2,
		CV_HAAR_SCALE_IMAGE |CV_HAAR_FIND_BIGGEST_OBJECT, Size((20*5*320)/640, (34*5*240)/480)); //20x34 //

	return (profiles);

}


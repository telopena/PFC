#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include "Draw.h"

using namespace std;
using namespace cv;

class ProfileRigth {
private:
	CascadeClassifier *profile_classifier;

public:
	ProfileRigth();
	~ProfileRigth(void);
	vector<Rect> Detect(Mat gray);

};

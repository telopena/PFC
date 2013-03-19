#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>

#include "EyeDetector.h"
#include "NoseDetector.h"
#include "MouthDetector.h"
#include "Almacena.h"

using namespace std;
using namespace cv;

class FaceDetector
{
private:
	CascadeClassifier *face_classifier;
	EyeDetector *eyes_detect_r;
	EyeDetector *eyes_detect_l;
	NoseDetector *nose_detect;
	MouthDetector *mouth_detect;
	Almacena almacena;

public:
	FaceDetector();
	~FaceDetector(void);
	Almacena Detect(Mat frame);

};








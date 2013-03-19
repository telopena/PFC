#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Runnable.h"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

class EyeDetector :public Runnable
{
private:
	CascadeClassifier * eye_classifier;
	Mat frame_ROI;
	std::vector<Rect> my_eyes;

public:
	EyeDetector(int opcion);
	~EyeDetector(void);
	void Detect();
	void setROI(Mat frame);
	void setVector(std::vector<Rect> vector);
	Mat getROI();
	std::vector<Rect> getVector();
	
 private:
	virtual void run();

	
	};


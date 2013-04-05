#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Runnable.h"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

class NoseDetector :public Runnable
{
private:
	CascadeClassifier *nose_classifier;
	Mat frame_ROI;
	std::vector<Rect> my_noses;
public:
	NoseDetector(void);
	~NoseDetector(void);
	void Detect();
	void setROI(Mat frame);
	Mat getROI();
	void setVector(std::vector<Rect>);
	std::vector<Rect>getVector();

private:
	virtual void run();

};


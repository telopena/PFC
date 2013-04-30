#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/video/tracking.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

class LucasKanade 
{
private:
	vector<Point2f> points[2];
	

public:
	LucasKanade(void);
	~LucasKanade(void);
	void set_points(Point2f aux,int x, int y);

	void calcula_fujo_optico(Mat pregray, Mat gray);
	Point2f get_points(int x, int y);


	};


#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>


using namespace std;
using namespace cv;

class FrameClasificado
{
	
private:
	double my_time;
	int my_decision;
	int lanzado;
public:
	FrameClasificado(void);
	~FrameClasificado(void);
	void setTime(double time);
	void setmy_decision(int decision);
	void setlanzado(int lanzar);
	double getTime();
	int getmy_decision();
	int getlanzado();

};


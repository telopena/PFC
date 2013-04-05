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
	enum options {L,R,D,UP,OK,N,U}my_LR,my_UD;
public:
	FrameClasificado(void);
	~FrameClasificado(void);
	void setTime(double time);
	void setLR(enum options aux);
	void setUD(enum options aux);
	double getTime();
	//options getLR();
	//options getUD();

};


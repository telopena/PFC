#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

class FrameClasificado {

private:
	double my_time;
	int my_decisionhor;
	int my_decisionver;
	int lanzado;
	int caradetect;
	int poscenter_x;
	int poscenter_y;
	int algdecision;
	int alg1;
	int profileR;
	int profileL;

public:
	FrameClasificado(void);
	~FrameClasificado(void);
	void setTime(double time);
	void setmy_decisionhor(int decision);
	void setmy_decisionver(int decision);
	void setlanzado(int lanzar);
	void setdetect(int dete);
	void setposcenter_x(int x);
	void setposcenter_y(int y);
	void setalgdecision(int algo);
	void setalg1(int algLR);
	void setprofileR(int profile);
	void setprofileL(int profile);

	double getTime();
	int getmy_decisionhor();
	int getmy_decisionver();
	int getlanzado();
	int getdetect();
	int getposcenter_x();
	int getposcenter_y();
	int getalgdecision();
	int getalg1();
	int getprofileR();
	int getprofileL();

};


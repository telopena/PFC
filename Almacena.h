#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

class Almacena
{
private:
	std::vector<Rect> myfaces;
	std::vector<Rect> myeyes_r;
	std::vector<Rect> myeyes_l;
	std::vector<Rect> mynoses;
	std::vector<Rect> mymouths;
	Point2f P0;
	Point2f P1;
	Point2f P2;
	Point2f P3;


public:
	Almacena(void);
	~Almacena(void);
	void set_faces(std::vector<Rect> faces);
	void set_eyes_r(std::vector<Rect> eyes_r);
	void set_eyes_l(std::vector<Rect> eyes_l);
	void set_noses(std::vector<Rect> noses);
	void set_mouths(std::vector<Rect> mouths);
	void set_P0(Point2f aux);
	void set_P1(Point2f aux1);
	void set_P2(Point2f aux2);
	void set_P3(Point2f aux3);

	std::vector<Rect> get_faces();
	std::vector<Rect> get_eyes_r();
	std::vector<Rect> get_eyes_l();
	std::vector<Rect> get_noses();
	std::vector<Rect> get_mouths();
	Point2f get_P0();
	Point2f get_P1();
	Point2f get_P2();
	Point2f get_P3();

};


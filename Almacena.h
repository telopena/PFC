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



public:
	Almacena(void);
	~Almacena(void);
	void set_faces(std::vector<Rect> faces);


	std::vector<Rect> get_faces();


};


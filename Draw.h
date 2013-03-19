#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>
#include "Almacena.h"

using namespace std;
using namespace cv;

class Draw
{
public:
	Draw(void);
	~Draw(void);
	Mat Dibujar(Mat frame,Almacena almacena);
};


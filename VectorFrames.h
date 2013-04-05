#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "FrameClasificado.h"


#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;



class VectorFrames
{
private:
	std::vector<FrameClasificado> frames;
public:
	VectorFrames(void);
	~VectorFrames(void);
};


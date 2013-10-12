#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "FrameClasificado.h"
#include "NoseDetector.h"
#include "Almacena.h"


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
	void Decide(int i);
	void addtovector(FrameClasificado);
	std::vector<FrameClasificado> getvector();
	int comprobar (int i,double marca);
};


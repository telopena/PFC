#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include"Almacena.h"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

class Clasificador
{
public:
	Clasificador(void);
	~Clasificador(void);
	void Clasifica(Almacena cara);
};


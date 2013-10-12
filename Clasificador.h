#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include"Almacena.h"
#include"LucasKanade.h"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

class Clasificador
{
private:
	double restahorizontal;
	double restavertical;
public:
	Clasificador(void);
	~Clasificador(void);
	int Clasifica(Almacena cara,LucasKanade kanade, int a);
};


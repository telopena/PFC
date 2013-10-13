/*
# Copyright (C) 2013 Eutelo Pena Barreiro
# 
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License Version 3
# as published by the Free Software Foundation.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#  
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 */

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
	int facestate;

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
	void setfacestate(int opcion);

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
	int getfacestate();

};


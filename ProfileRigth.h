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
#include "Runnable.h"
#include "Draw.h"

using namespace std;
using namespace cv;

class ProfileRigth :public Runnable {
private:
	CascadeClassifier *profile_classifier;
	Mat frame_ROI;
	std::vector<Rect> my_profiles;

public:
	ProfileRigth();
	~ProfileRigth(void);
	void Detect();
	void setROI(Mat frame);
	void setVector(std::vector<Rect> vector);
	Mat getROI();
	std::vector<Rect> getVector();

private:
	virtual void run();

};

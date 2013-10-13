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

#include "ProfileRigth.h"

ProfileRigth::ProfileRigth() :Runnable()

{
	profile_classifier = NULL;
	String aux="C:/Users/telo/Documents/Visual Studio 2012/Projects/Prueba_opencv/Release/lbpcascade_profileface.xml";
	profile_classifier = new CascadeClassifier();
	profile_classifier->load(aux);

}

ProfileRigth::~ProfileRigth(void) {
	if (profile_classifier != NULL) {
		delete (profile_classifier);
		profile_classifier = NULL;
	}

}

void ProfileRigth::Detect() {



	flip(frame_ROI, frame_ROI, 1);

	profile_classifier->detectMultiScale(frame_ROI, my_profiles, 1.2, 3,
		CV_HAAR_SCALE_IMAGE |CV_HAAR_FIND_BIGGEST_OBJECT, Size((20*5*320)/640, (34*5*240)/480)); //20x34 //



}

void ProfileRigth:: setROI(Mat frame){
	frame_ROI=frame;
}

void ProfileRigth:: setVector(std::vector<Rect> vector){
	my_profiles=vector;

}

Mat ProfileRigth:: getROI(){
	return(frame_ROI);
}

std::vector<Rect> ProfileRigth:: getVector(){
	return(my_profiles);


}


void ProfileRigth:: run(){

	Detect();
}



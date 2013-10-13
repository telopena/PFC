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

#include "FaceDetector.h"




FaceDetector::FaceDetector(void) :Runnable()

{
	face_classifier=NULL;
	//String face_cascade_name = "C:/Users/telo/Documents/Visual Studio 2012/Projects/Prueba_opencv/Release/haarcascade_frontalface_alt2.xml";
	String face_cascade_name ="C:/Users/telo/Documents/Visual Studio 2012/Projects/Prueba_opencv/Release/lbpcascade_frontalface.xml";
	face_classifier=new CascadeClassifier();  
	face_classifier->load( face_cascade_name );


}


FaceDetector::~FaceDetector(void)
{
	if(face_classifier!=NULL){delete(face_classifier);face_classifier=NULL;	}


}

void FaceDetector::Detect(){



	face_classifier->detectMultiScale( frame_ROI, my_faces, 1.1, 2, CV_HAAR_SCALE_IMAGE |CV_HAAR_FIND_BIGGEST_OBJECT,Size((200*320)/640, (200*240)/480) ); //100x100



}

void FaceDetector::setROI(Mat frame){
	frame_ROI=frame;
}

void FaceDetector::setVector(std::vector<Rect> vector){
	my_faces=vector;

}

Mat FaceDetector::getROI(){
	return(frame_ROI);
}

std::vector<Rect> FaceDetector::getVector(){
	return(my_faces);


}


void FaceDetector::run(){

	Detect();
}


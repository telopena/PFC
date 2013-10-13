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

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/video/tracking.hpp"

#include <iostream>
#include <stdio.h>
#include "FaceDetector.h"
#include "Draw.h"
#include "Almacena.h"
#include "FrameClasificado.h"
#include "VectorFrames.h"
#include "ProfileLeft.h"
#include "ProfileRigth.h"
#include "TemplateMatching.h"
#include <time.h>

using namespace std;
using namespace cv;


int main( void )
{

	CvCapture* capture;
	Mat frame_capturado,frame_gray,frame_gray2,template_cara1,velocidad_cara,frameycrcb;
	Mat channels[3];
	Almacena almacena;
	Draw draw;
	FaceDetector face_detector;
	FrameClasificado frame_clasificado;
	VectorFrames vector_frames;
	ProfileLeft profile_detectorL;
	ProfileRigth profile_detectorR;
	TemplateMatching matching;
	int i=0,solape_cara=1,profileL=0,profileR=0,state=0;
	double t_fps1,t_fps2,marca;
	double minVal,maxVal;
	Size dimensiones_cara;
	Point2f coor_cara;
	std::vector<Rect> newfaces,profilesL,profilesR;
	Rect aux,face,mask,aux2;
	IplImage img1;
	IplImage *roiImg=NULL;
	CvPoint minloc,maxloc;

	velocidad_cara.create(240,320,CV_8UC3);



	capture = cvCaptureFromCAM(-1);
	cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, 320 );
	cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, 240 );
	coor_cara.x=-1;
	coor_cara.y=-1;



	if( capture )
	{
		for(;;)
		{  

			velocidad_cara.release();
			t_fps1 = (double)cv::getTickCount();
			t_fps2=(double)cv::getTickCount();
			frame_capturado = cvQueryFrame( capture );
			marca= ((double)cv::getTickCount())*1000. / cv::getTickFrequency(); 
			flip(frame_capturado,frame_capturado,1);
			cvtColor(frame_capturado ,frame_gray , CV_BGR2GRAY );
			equalizeHist( frame_gray, frame_gray );
			cvtColor(frame_capturado,frame_gray2, CV_BGR2GRAY);
			equalizeHist( frame_gray2, frame_gray2 );
			cvtColor(frame_capturado,frameycrcb,CV_BGR2YCrCb);
			split(frameycrcb,channels);


			velocidad_cara.create(240,320,CV_8UC3);

			solape_cara=0;
			profileL=0;
			profileR=0;
			frame_clasificado.setprofileL(0);
			frame_clasificado.setprofileR(0);


			if( !frame_gray.empty() )
			{ 


				face_detector.setROI(frame_gray);
				face_detector.start_thread();

				profile_detectorL.setROI(frame_gray);
				profile_detectorL.start_thread();

				profile_detectorR.setROI(frame_gray2);
				profile_detectorR.start_thread();

				if(i!=0){

					matching.setBuscar(channels[1]);
					matching.setTemplate(template_cara1);
					matching.run();
					//imshow("prob",matching.getResult());

				}

				face_detector.join_thread();
				profile_detectorL.join_thread();
				profile_detectorR.join_thread();


				almacena.set_faces(face_detector.getVector());
				profilesL = profile_detectorL.getVector();
				profilesR = profile_detectorR.getVector();

				for(size_t w = 0; w < (profilesL).size(); w++){
					if (profilesL.size() != 0) {
						profileL = 1;
						frame_clasificado.setprofileL(1);


					}
				}

				for(size_t w = 0; w < (profilesR).size(); w++){
					if (profilesR.size() != 0) {
						profileR = 1;
						frame_clasificado.setprofileR(1);


					}
				}


				if(frame_clasificado.getfacestate() == -1 ||frame_clasificado.getfacestate() == 1 ){


					if(almacena.get_faces().size()!=0) {
						state=1;}

					if(almacena.get_faces().size()==0){

						if(profilesL.size()!=0){
							state=2;}
						if(profilesR.size()!=0){
							state=3;}


					}

				}

				if(frame_clasificado.getfacestate()==2 ){ 				

					if(profilesL.size()==0 && almacena.get_faces().size()!=0){
						state=1;}
					else{
						state=2;}

				}


				if(frame_clasificado.getfacestate()==3 ){ 				

					if(profilesR.size()==0 && almacena.get_faces().size()!=0){
						state=1;}
					else{
						state=3;}

				}

				if(state!=0){
					frame_clasificado.setfacestate(state);
				}

				if(almacena.get_faces().size()!=0){


					for(size_t w = 0; w < (almacena.get_faces()).size(); w++){

						dimensiones_cara=(almacena.get_faces())[w].size();

						face=almacena.get_faces()[w];
						coor_cara.x=face.x+dimensiones_cara.width/2;
						coor_cara.y=face.y+dimensiones_cara.height/2;

						aux2.x=coor_cara.x-dimensiones_cara.width/4;
						aux2.y=face.y;
						aux2.width=dimensiones_cara.width*1/2;
						aux2.height=dimensiones_cara.height;


						template_cara1.release();
						template_cara1=channels[1](aux2).clone();
						//imshow("template",template_cara1);



						solape_cara=1;

					}


					frame_capturado=draw.Dibujar(frame_capturado,almacena);
					frame_clasificado.setposcenter_x(coor_cara.x);
					frame_clasificado.setposcenter_y(coor_cara.y);
					frame_clasificado.setTime(marca);
					frame_clasificado.setdetect(1);
					vector_frames.addtovector(frame_clasificado);
					vector_frames.Decide(i,marca,velocidad_cara,almacena,profileL,profileR,frame_capturado);


					i++;
					t_fps1 = ((double)cv::getTickCount() - t_fps1) / cv::getTickFrequency();
					cout << "I am working at " << 1/t_fps1 << " FPS" << std::endl;
				}


				if((i!=0 ) && (vector_frames.comprobar(i,marca)==1) && (almacena.get_faces().size()==0)){

					img1=matching.getResult();

					if(roiImg!=NULL){
						cvReleaseImage(&roiImg);
						roiImg=NULL;
					}

					roiImg=cvCreateImage ( cvSize ( img1.width,img1.height ),8,1 );
					cvZero(roiImg);
					mask.x=face.x - dimensiones_cara.width*0.15;
					mask.y=face.y-dimensiones_cara.height*0.15;
					mask.width=1.15*dimensiones_cara.width;
					mask.height=1.15*dimensiones_cara.height;
					if(mask.x<0){mask.x=0;}
					if(mask.y<0){mask.y=0;}
					if(mask.x+mask.width > img1.width){mask.width=img1.width;}
					if(mask.y+mask.height > img1.height){mask.height=img1.height;}

					cvSetImageROI(roiImg,mask);
					cvSet(roiImg,cvScalar(255));
					cvResetImageROI(roiImg);
					Mat telo=roiImg;
					//imshow("telo",telo);



					cvMinMaxLoc(&img1,&minVal,&maxVal,&minloc,&maxloc,roiImg);


					aux.x=maxloc.x - dimensiones_cara.width/4;
					aux.y=maxloc.y ;
					aux.width=dimensiones_cara.width;
					aux.height=dimensiones_cara.height;



					if(aux.x<0){aux.x=0;}
					if(aux.y<0){aux.y=0;}


					Point center_aux(aux.x+aux.width/2,aux.y+aux.height/2);


					if((face.x < aux.x + aux.width) && (aux.x < face.x + face.width) && (face.y < aux.y +aux.height )){

						int x = std::max(int(face.x), int(aux.x));
						int num2 = std::min(int(face.x + face.width), int(aux.x+ aux.width));
						int y = std::max(int(face.y),int(aux.y));
						int num4 = std::min(int(face.y + face.height),int(aux.y+ aux.height));

						if (num2 >= x && num4 >= y)
						{

							int commun_area = ((num2 - x)*(num4 - y));
							int own_area= face.width* face.height;
							int other_area= aux.width * aux.height;


							if ((commun_area> ((other_area)*0.50))&& (commun_area> ((own_area)*0.50))){solape_cara=1;}

						}

					}






					if(solape_cara==1){

						rectangle(frame_capturado,Point(aux.x,aux.y),Point(aux.x + aux.width,aux.y+aux.height),Scalar(0,0,255),1,CV_AA);

						face=aux;
						coor_cara.x=center_aux.x;
						coor_cara.y=center_aux.y;
						dimensiones_cara.width=aux.width;
						dimensiones_cara.height=aux.height;

					}


					if(solape_cara==0){
						rectangle(frame_capturado,Point(aux.x,aux.y),Point(aux.x + aux.width,aux.y+aux.height),Scalar(255,255,255),1,CV_AA);
					}


				}


				if( (almacena.get_faces().size()==0)  ){


					if((i!=0) && (vector_frames.comprobar(i,marca)==1) && solape_cara==1 ){

						newfaces.assign(1,aux);
						almacena.set_faces(newfaces);
						frame_clasificado.setdetect(0);
						frame_clasificado.setposcenter_x(coor_cara.x);
						frame_clasificado.setposcenter_y(coor_cara.y);
						frame_clasificado.setTime(marca);

						if (profilesL.size() != 0 || profilesR.size() != 0) {

							frame_clasificado.setdetect(1);

						}

						vector_frames.addtovector(frame_clasificado);
						vector_frames.Decide(i,marca,velocidad_cara,almacena,profileL,profileR,frame_capturado);
						i++;



					}

					t_fps2 = ((double)cv::getTickCount() - t_fps2) / cv::getTickFrequency();
					cout << "I am working at " << 1/t_fps2 << " FPS" << std::endl;
				}



				//imshow("velocidadcara",velocidad_cara);

				imshow("Aplicación",frame_capturado);


			}



			else

			{ printf(" --(!) No captured frame -- Break!"); break; }

			int c = waitKey(10);

			if( (char)c == 'c' ) { break; }



		}
	}
	cvReleaseCapture( &capture );
	face_detector.~FaceDetector();
	almacena.~Almacena();
	draw.~Draw();
	frame_clasificado.~FrameClasificado();
	vector_frames.~VectorFrames();
	profile_detectorR.~ProfileRigth();
	profile_detectorL.~ProfileLeft();
	matching.~TemplateMatching();
	return 0;
}


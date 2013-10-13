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
#include <time.h>

using namespace std;
using namespace cv;


int main( void )
{

	CvCapture* capture;
	Mat frame_capturado,frame_gray,template_cara1,result1,buscar_cara,velocidad_cara;
	Almacena almacena;
	Draw draw;
	FaceDetector face_detector;
	FrameClasificado frame_clasificado;
	VectorFrames vector_frames;
	ProfileLeft profile_detectorL;
	ProfileRigth profile_detectorR;
	int retorno,i=0,solape_cara=1,profileL=0,profileR=0;
	double t_fps1,t_fps2,marca;
	double minVal,maxVal;
	Size dimensiones_cara;
	Point2f p3,coor_cara;
	std::vector<Rect> newfaces,profilesL,profilesR;
	Rect aux,face;
	IplImage img1;
	CvPoint minloc,maxloc;
	bool permiso;

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
			permiso=false;
			velocidad_cara.release();
			t_fps1 = (double)cv::getTickCount();
			t_fps2=(double)cv::getTickCount();
			frame_capturado = cvQueryFrame( capture );
			marca= ((double)cv::getTickCount())*1000. / cv::getTickFrequency(); //REFERENCIA DESDE QUE ENCENDIU O PC
			flip(frame_capturado,frame_capturado,1);
			cvtColor(frame_capturado ,frame_gray , CV_BGR2GRAY );
			equalizeHist( frame_gray, frame_gray );
			velocidad_cara.create(240,320,CV_8UC3);

			solape_cara=1;
			profileL=0;
			profileR=0;
			frame_clasificado.setprofileL(0);
			frame_clasificado.setprofileR(0);






			if( !frame_gray.empty() )
			{ 

				almacena=face_detector.Detect(frame_gray); 

				profilesL = profile_detectorL.Detect(frame_gray);

				profilesR = profile_detectorR.Detect(frame_gray);

				if (profilesL.size() != 0) {
					profileL = 1;
					frame_clasificado.setprofileL(1);
					//cout<<"perfilizquierda"<<endl;

				}
				if (profilesR.size() != 0) {
					profileR = 1;
					frame_clasificado.setprofileR(1);
					//cout<<"perfilderecha"<<endl;
				}







				if(almacena.get_faces().size()!=0){


					for(size_t w = 0; w < (almacena.get_faces()).size(); w++){

						dimensiones_cara=(almacena.get_faces())[w].size();

						template_cara1=frame_gray(almacena.get_faces()[w]).clone();

						face=almacena.get_faces()[w];
						coor_cara.x=face.x+dimensiones_cara.width/2;
						coor_cara.y=face.y+dimensiones_cara.height/2;

						solape_cara=1;

					}


					frame_capturado=draw.Dibujar(frame_capturado,almacena);
					frame_clasificado.setposcenter_x(coor_cara.x);
					frame_clasificado.setposcenter_y(coor_cara.y);
					frame_clasificado.setTime(marca);
					frame_clasificado.setdetect(1);
					vector_frames.addtovector(frame_clasificado);
					vector_frames.Decide(i,marca,velocidad_cara,almacena,profileL,profileR);


					i++;
					t_fps1 = ((double)cv::getTickCount() - t_fps1) / cv::getTickFrequency();
					cout << "I am working at " << 1/t_fps1 << " FPS" << std::endl;
				}




				if((i!=0 ) && (vector_frames.comprobar(i,marca)==1) && (almacena.get_faces().size()==0)){

					matchTemplate(frame_gray,template_cara1,result1,CV_TM_CCOEFF_NORMED);

					img1=result1;

					cvMinMaxLoc(&img1,&minVal,&maxVal,&minloc,&maxloc);
					aux.x=maxloc.x;
					aux.y=maxloc.y;
					aux.width=dimensiones_cara.width;
					aux.height=dimensiones_cara.height;



					if(aux.x<0){aux.x=0;}
					if(aux.y<0){aux.y=0;}
					if(aux.x+aux.width > frame_gray.cols){aux.width=frame_gray.cols;}
					if(aux.y+aux.height >frame_gray.rows){aux.height=frame_gray.rows;}

					Point center_aux(aux.x+aux.width/2,aux.y+aux.height/2);



					if(coor_cara.x!=-1 && coor_cara.y!=-1){

						if( (abs(coor_cara.x - aux.x) > dimensiones_cara.width/2) && (abs(coor_cara.x - (aux.x+aux.width)) > dimensiones_cara.width/2) ){solape_cara=0;}
						if( (abs(coor_cara.y - aux.y) > dimensiones_cara.height/2) && (abs(coor_cara.y - (aux.y+aux.height)) > dimensiones_cara.height/2) ){solape_cara=0;}
						if(	(abs(coor_cara.x - center_aux.x) > dimensiones_cara.width/10 )){solape_cara=0;}
						if(	(abs(coor_cara.y - center_aux.y) > dimensiones_cara.height/10 )){solape_cara=0;}

					}




					if(solape_cara==1){
						rectangle(frame_capturado,Point(aux.x,aux.y),Point(aux.x + aux.width,aux.y+aux.height),Scalar(0,0,255),1,CV_AA);


						coor_cara.x=center_aux.x;
						coor_cara.y=center_aux.y;
						dimensiones_cara.width=aux.width;
						dimensiones_cara.height=aux.height;
						face = aux;



					}


					if(solape_cara==0){



						rectangle(frame_capturado,Point(aux.x,aux.y),Point(aux.x + aux.width,aux.y+aux.height),Scalar(255,255,255),1,CV_AA);
					}



				}


				if( (almacena.get_faces().size()==0)  ){


					if((i!=0) && (vector_frames.comprobar(i,marca)==1) && solape_cara==1 ){


						if(almacena.get_faces().size()==0){
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
							vector_frames.Decide(i,marca,velocidad_cara,almacena,profileL,profileR);
							permiso=true;
						}




						if(permiso==true){
							i++;
						}
					}

					t_fps2 = ((double)cv::getTickCount() - t_fps2) / cv::getTickFrequency();
					cout << "I am working at " << 1/t_fps2 << " FPS" << std::endl;
				}



				imshow("velocidadcara",velocidad_cara);

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
	return 0;
}


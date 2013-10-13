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
	Mat frame_capturado,frame_gray,frame_gray2,template_cara1,result1,buscar_cara,velocidad_cara;
	Almacena almacena;
	Draw draw;
	FaceDetector face_detector;
	FrameClasificado frame_clasificado;
	VectorFrames vector_frames;
	ProfileLeft profile_detectorL;
	ProfileRigth profile_detectorR;
	int retorno,i=0,solape_cara=1,profileL=0,profileR=0,state=0;
	double t_fps1,t_fps2,marca;
	double minVal,maxVal;
	Size dimensiones_cara;
	Point2f p3,coor_cara;
	std::vector<Rect> newfaces,profilesL,profilesR;
	Rect aux,face;
	IplImage img1;
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
			cvtColor(frame_capturado,frame_gray2, CV_BGR2GRAY);
			equalizeHist( frame_gray, frame_gray );
			equalizeHist( frame_gray2, frame_gray2 );
			velocidad_cara.create(240,320,CV_8UC3);

			solape_cara=0;
			profileL=0;
			profileR=0;
			frame_clasificado.setprofileL(0);
			frame_clasificado.setprofileR(0);







			if( !frame_gray.empty() )
			{ 

				almacena=face_detector.Detect(frame_gray); 

				profilesL = profile_detectorL.Detect(frame_gray2);

				profilesR = profile_detectorR.Detect(frame_gray2);

				if (profilesL.size() != 0) {
					profileL = 1;
					frame_clasificado.setprofileL(1);

				}
				if (profilesR.size() != 0) {
					profileR = 1;
					frame_clasificado.setprofileR(1);
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


							if ((commun_area> ((other_area)*0.25))&& (commun_area> ((own_area)*0.25))){solape_cara=1;}

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
						vector_frames.Decide(i,marca,velocidad_cara,almacena,profileL,profileR);
						i++;



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


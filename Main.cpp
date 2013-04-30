#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/video/tracking.hpp"

#include <iostream>
#include <stdio.h>
#include "FaceDetector.h"
#include "Draw.h"
#include "Almacena.h"
#include "Clasificador.h"
#include "FrameClasificado.h"
#include "VectorFrames.h"
#include <time.h>
#include "LucasKanade.h"

using namespace std;
using namespace cv;


int main( void )
{

	CvCapture* capture;
	Mat frame_capturado,frame_gray,frame_pregay;
	Almacena almacena;
	Draw draw;
	FaceDetector face_detector;
	Clasificador clasificador;
	FrameClasificado frame_clasificado;
	VectorFrames vector_frames;
	LucasKanade kanade;
	int retorno;
	double t_fps;
	double marca;
	int i=0;
	Size dimensiones_cara;
	Point2f p3,p4,p5;





	capture = cvCaptureFromCAM(-1);

	if( capture )
	{
		for(;;)
		{  
			t_fps = (double)cv::getTickCount();
			frame_capturado = cvQueryFrame( capture );
			marca= ((double)cv::getTickCount())*1000. / cv::getTickFrequency(); //REFERENCIA DESDE QUE ENCENDIU O PC
			flip(frame_capturado,frame_capturado,1);
			cvtColor(frame_capturado ,frame_gray , CV_BGR2GRAY );
			//equalizeHist( frame_gray, frame_gray );





			if( !frame_gray.empty() )
			{ 
				almacena=face_detector.Detect(frame_gray); 



				t_fps = ((double)cv::getTickCount() - t_fps) / cv::getTickFrequency();
				cout << "I am working at " << 1/t_fps << " FPS" << std::endl;


				for(size_t w = 0; w < (almacena.get_faces()).size(); w++){

					dimensiones_cara=(almacena.get_faces())[w].size();



					if( (almacena.get_noses()).size() != 0) {
						Point2f p2((float)(almacena.get_faces()[w].x +	(dimensiones_cara.width)/4 + (almacena.get_noses())[w].x + 	((almacena.get_noses())[w].width)/2	), (float)(almacena.get_faces()[w].y + (dimensiones_cara.height)/4 + (almacena.get_noses())[w].y + ((almacena.get_noses())[w].height)/2)); 
						kanade.set_points(p2,0,0);
						line(frame_capturado,p2,p2,Scalar(255,0,0),3,8,0);
						p3=p2;
					}





					if( (almacena.get_noses()).size()==0){
						kanade.set_points(p3,0,0);
					}



				}



				//OJO SI EN SEGUNDO FRAME NO DETECTA NINGUN PUNTO CASCA

				if( (i!=0) && ( (almacena.get_noses()).size() ==0) ){

					kanade.calcula_fujo_optico(frame_pregay,frame_gray);
					line(frame_capturado,kanade.get_points(1,0),kanade.get_points(1,0),Scalar(255,0,0),3,8,0);

				}

				frame_capturado=draw.Dibujar(frame_capturado,almacena);

				retorno=clasificador.Clasifica(almacena,kanade);
				frame_clasificado.setmy_decision(retorno);
				frame_clasificado.setTime(marca);

				vector_frames.addtovector(frame_clasificado);
				vector_frames.Decide(i);

				imshow("Aplicación",frame_capturado);


			}



			else

			{ printf(" --(!) No captured frame -- Break!"); break; }

			int c = waitKey(10);

			if( (char)c == 'c' ) { break; }

			frame_gray.copyTo(frame_pregay);





			i++;

		}
	}
	cvReleaseCapture( &capture );
	face_detector.~FaceDetector();
	almacena.~Almacena();
	clasificador.~Clasificador();
	draw.~Draw();
	frame_clasificado.~FrameClasificado();
	vector_frames.~VectorFrames();
	kanade.~LucasKanade();
	~frame_capturado;
	~frame_gray;
	~frame_pregay;
	return 0;
}


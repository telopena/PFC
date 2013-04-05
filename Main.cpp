#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>
#include "FaceDetector.h"
#include "Draw.h"
#include "Almacena.h"
#include "Clasificador.h"
#include <time.h>

using namespace std;
using namespace cv;


int main( void )
{

	CvCapture* capture;
	Mat frame_capturado,frame_gray;
	Almacena almacena;
	Draw draw;
	FaceDetector face_detector;
	Clasificador clasificador;
	double t_fps;
	//double initTimeSeconds= time(NULL);
	//double initTimeMill= initTimeSeconds*1000;
	//double marca= (double)cv::getTickCount();




	capture = cvCaptureFromCAM(-1);

	if( capture )
	{
		for(;;)
		{
			t_fps = (double)cv::getTickCount();
			frame_capturado = cvQueryFrame( capture );
			//marca= ( (double)cv::getTickCount() - marca)*1000./getTickFrequency();
			flip(frame_capturado,frame_capturado,1);
			cvtColor(frame_capturado ,frame_gray , CV_BGR2GRAY );
			equalizeHist( frame_gray, frame_gray );



			if( !frame_gray.empty() )
			{ 
				almacena=face_detector.Detect( frame_gray); 
				t_fps = ((double)cv::getTickCount() - t_fps) / cv::getTickFrequency();
				cout << "I am working at " << 1/t_fps << " FPS" << std::endl;
				frame_capturado=draw.Dibujar(frame_capturado,almacena);
				clasificador.Clasifica(almacena);
				imshow("Mostrar",frame_capturado);
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
	clasificador.~Clasificador();
	draw.~Draw();
	~frame_capturado;
	~frame_gray;
	return 0;
}

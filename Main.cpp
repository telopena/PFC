#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>
#include "FaceDetector.h"
#include "Draw.h"
#include "Almacena.h"
#include "Clasificador.h"
#include "FrameClasificado.h"
#include "VectorFrames.h"
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
	FrameClasificado frame_clasificado;
	VectorFrames vector_frames;
	int retorno;
	double t_fps;
	double marca;
	int i=0;




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
			equalizeHist( frame_gray, frame_gray );



			if( !frame_gray.empty() )
			{ 
				almacena=face_detector.Detect( frame_gray); 
				t_fps = ((double)cv::getTickCount() - t_fps) / cv::getTickFrequency();
				cout << "I am working at " << 1/t_fps << " FPS" << std::endl;
				frame_capturado=draw.Dibujar(frame_capturado,almacena);
				retorno=clasificador.Clasifica(almacena);
				frame_clasificado.setmy_decision(retorno);
				frame_clasificado.setTime(marca);
				vector_frames.addtovector(frame_clasificado);
				vector_frames.Decide(i);
				imshow("Mostrar",frame_capturado);
			}

			else

			{ printf(" --(!) No captured frame -- Break!"); break; }

			int c = waitKey(10);

			if( (char)c == 'c' ) { break; }



			i++;

		}
	}

	cvReleaseCapture( &capture );
	face_detector.~FaceDetector();
	almacena.~Almacena();
	clasificador.~Clasificador();
	draw.~Draw();
	frame_clasificado.~FrameClasificado();
	//vector_frames.~VectorFrames();
	~frame_capturado;
	~frame_gray;
	return 0;
}

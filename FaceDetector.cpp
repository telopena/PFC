#include "FaceDetector.h"




FaceDetector::FaceDetector(void)

{
	face_classifier=NULL;
	String face_cascade_name = "C:/Users/telo/Documents/Visual Studio 2012/Projects/Prueba_opencv/Release/haarcascade_frontalface_alt2.xml";
	face_classifier=new CascadeClassifier();  
	face_classifier->load( face_cascade_name );


}


FaceDetector::~FaceDetector(void)
{
	if(face_classifier!=NULL){delete(face_classifier);face_classifier=NULL;	}


}

Almacena FaceDetector::Detect(Mat gray){


	std::vector<Rect> faces;





	face_classifier->detectMultiScale( gray, faces, 1.1, 2, 0|CV_HAAR_FIND_BIGGEST_OBJECT,Size((200*320)/640, (200*240)/480) ); //100x100
	almacena.set_faces(faces);




	return(almacena);


}

#include "FaceDetector.h"



FaceDetector::FaceDetector(void)

{
	face_classifier=NULL;
	String face_cascade_name = "C:/Users/telo/Documents/Visual Studio 2012/Projects/Prueba_opencv/Release/haarcascade_frontalface_alt2.xml";
	face_classifier=new CascadeClassifier();  
	face_classifier->load( face_cascade_name );
	eyes_detect_r=NULL;
	eyes_detect_r=new EyeDetector(0);
	eyes_detect_l=NULL;
	eyes_detect_l=new EyeDetector(1);
	nose_detect=NULL;
	nose_detect=new NoseDetector();
	mouth_detect=NULL;
	mouth_detect=new MouthDetector();
}


FaceDetector::~FaceDetector(void)
{
	if(face_classifier!=NULL){delete(face_classifier);face_classifier=NULL;	}
	eyes_detect_r->~EyeDetector();
	eyes_detect_l->~EyeDetector();
	nose_detect->~NoseDetector();
	mouth_detect->~MouthDetector();
}

Almacena FaceDetector:: Detect(Mat frame)

{


	std::vector<Rect> faces;
	



	face_classifier->detectMultiScale( frame, faces, 1.1, 2, 0|CV_HAAR_FIND_BIGGEST_OBJECT,Size(30, 30) );
	almacena.set_faces(faces);

	for( size_t i = 0; i < faces.size(); i++ ){
		Size dimensiones_cara= (frame(faces[i])).size();
		Mat cara=frame(faces[i]);
		Mat ROI_eyer,ROI_eyel,ROI_nose,ROI_mouth;
		ROI_eyer=cara(Range(0,(dimensiones_cara.height)/2),Range((dimensiones_cara.width)/2,dimensiones_cara.width));
		ROI_eyel=cara(Range(0,(dimensiones_cara.height)/2),Range(0,(dimensiones_cara.width)/2));
		ROI_nose=cara(Range((dimensiones_cara.height/4),(dimensiones_cara.height)*3/4),Range((dimensiones_cara.width/4),(dimensiones_cara.width)*3/4));
		ROI_mouth=cara(Range((dimensiones_cara.height)/2,dimensiones_cara.height),Range::all());


		
		eyes_detect_r->setROI(ROI_eyer);
		eyes_detect_r->start_thread();

		eyes_detect_l->setROI(ROI_eyel);
		eyes_detect_l->start_thread();

		nose_detect->setROI(ROI_nose);
		nose_detect->start_thread();

		mouth_detect->setROI(ROI_mouth);
		mouth_detect->start_thread();


        eyes_detect_r->join_thread();
		almacena.set_eyes_r(eyes_detect_r->getVector());
		
		eyes_detect_l->join_thread();
		almacena.set_eyes_l(eyes_detect_l->getVector());
		
		nose_detect->join_thread();
		almacena.set_noses(nose_detect->getVector());

		mouth_detect->join_thread();
		almacena.set_mouths(mouth_detect->getVector());


		/*
		eyes_detect_r->setROI(ROI_eyer);
		eyes_detect_r->Detect();
		almacena.set_eyes_r(eyes_detect_r->getVector());

		
		eyes_detect_l->setROI(ROI_eyel);
		eyes_detect_l->Detect();
		almacena.set_eyes_l(eyes_detect_l->getVector());

		nose_detect->setROI(ROI_nose);
		nose_detect->Detect();
		almacena.set_noses(nose_detect->getVector());


		mouth_detect->setROI(ROI_mouth);
		mouth_detect->Detect();
		almacena.set_mouths(mouth_detect->getVector());

		*/
	}



	return(almacena);


}

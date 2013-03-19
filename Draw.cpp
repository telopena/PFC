#include "Draw.h"


Draw::Draw(void)
{
}


Draw::~Draw(void)
{
}

Mat Draw:: Dibujar(Mat frame,Almacena almacena){

	Size dimensiones_cara;

	for( size_t i = 0; i < (almacena.get_faces()).size(); i++ )
	{
		//PINTAR CARAS//
		Point center( almacena.get_faces()[i].x + almacena.get_faces()[i].width/2, almacena.get_faces()[i].y + almacena.get_faces()[i].height/2 );
		ellipse( frame, center, Size( almacena.get_faces()[i].width/2, almacena.get_faces()[i].height/2), 0, 0, 360, Scalar( 255, 0, 0 ), 2, 8, 0 );


		dimensiones_cara=(frame(almacena.get_faces()[i])).size();


		for( size_t j = 0; j <(almacena.get_eyes_r()).size(); j++ ){ 
			//PINTAR OJO DERECHO    
			Point eye_center_r( almacena.get_faces()[i].x +(dimensiones_cara.width)/2+ almacena.get_eyes_r()[j].x + almacena.get_eyes_r()[j].width/2, almacena.get_faces()[i].y + almacena.get_eyes_r()[j].y + almacena.get_eyes_r()[j].height/2 );
			int radius_r = cvRound( (almacena.get_eyes_r()[j].width + almacena.get_eyes_r()[j].height)*0.10 );
			circle( frame, eye_center_r, radius_r, Scalar( 255, 0, 255 ), 3, 8, 0 );

		}

		for( size_t j = 0; j < (almacena.get_eyes_l()).size(); j++ ){ 
			//PINTAR OJO IZQUIERDO
			Point eye_center_l( almacena.get_faces()[i].x + almacena.get_eyes_l()[j].x + almacena.get_eyes_l()[j].width/2, almacena.get_faces()[i].y + almacena.get_eyes_l()[j].y + almacena.get_eyes_l()[j].height/2 );
			int radius_l = cvRound( (almacena.get_eyes_l()[j].width + almacena.get_eyes_l()[j].height)*0.10 );
			circle( frame, eye_center_l, radius_l, Scalar( 255, 255, 255 ), 3, 8, 0 ); 
		}

		for( size_t j = 0; j < (almacena.get_noses()).size(); j++ ){ 
			//PINTAR NARIZ
			Point nose_center( almacena.get_faces()[i].x +(dimensiones_cara.height)/4+ almacena.get_noses()[j].x + almacena.get_noses()[j].width/2, almacena.get_faces()[i].y+(dimensiones_cara.width)/4+ almacena.get_noses()[j].y + almacena.get_noses()[j].height/2 );
			int radius_nose = cvRound( (almacena.get_noses()[j].width + almacena.get_noses()[j].height)*0.20);
			circle( frame, nose_center, radius_nose, Scalar( 0, 0, 0 ), 3, 8, 0 ); 
		}

		for( size_t j = 0; j < (almacena.get_mouths()).size(); j++ ){ 
			//PINTAR BOCA
			Point mouth_center( almacena.get_faces()[i].x + almacena.get_mouths()[j].x + almacena.get_mouths()[j].width/2, almacena.get_faces()[i].y +(dimensiones_cara.height)/2+ almacena.get_mouths()[j].y + almacena.get_mouths()[j].height/2 );
			int radius_mouth = cvRound( (almacena.get_mouths()[j].width + almacena.get_mouths()[j].height)*0.20 );
			circle( frame, mouth_center, radius_mouth, Scalar( 0, 255, 0 ), 3, 8, 0 ); 
		}

	}
	return(frame);

}
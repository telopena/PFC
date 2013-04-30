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
		rectangle(frame,Point((almacena.get_faces())[i].x,(almacena.get_faces())[i].y),Point((almacena.get_faces())[i].x+(almacena.get_faces())[i].width,(almacena.get_faces())[i].y+(almacena.get_faces())[i].height), Scalar( 255, 0, 0 ), 2, 8, 0 );

		dimensiones_cara=(almacena.get_faces())[i].size();


		for( size_t j = 0; j <(almacena.get_eyes_r()).size(); j++ ){ 
			//PINTAR OJO DERECHO    
			rectangle(frame,Point((almacena.get_faces())[i].x+(dimensiones_cara.width)/2+(almacena.get_eyes_r()[j]).x,(almacena.get_faces())[i].y+(almacena.get_eyes_r())[j].y),Point((almacena.get_faces())[i].x+(dimensiones_cara.width)/2+(almacena.get_eyes_r())[j].x+(almacena.get_eyes_r())[j].width,(almacena.get_faces())[i].y+(almacena.get_eyes_r())[j].y+(almacena.get_eyes_r())[j].height), Scalar( 255, 0, 255 ), 2, 8, 0 );
		}

		for( size_t j = 0; j < (almacena.get_eyes_l()).size(); j++ ){ 
			//PINTAR OJO IZQUIERDO

			rectangle(frame,Point((almacena.get_faces())[i].x+(almacena.get_eyes_l())[j].x,(almacena.get_faces())[i].y+(almacena.get_eyes_l())[j].y),Point((almacena.get_faces())[i].x+(almacena.get_eyes_l())[j].x+(almacena.get_eyes_l())[j].width,(almacena.get_faces())[i].y+(almacena.get_eyes_l())[j].y+(almacena.get_eyes_l())[j].height), Scalar( 255, 255, 255 ), 2, 8, 0 );
		}

		for( size_t j = 0; j < (almacena.get_noses()).size(); j++ ){ 
			//PINTAR NARIZ
			rectangle(frame,Point((almacena.get_faces())[i].x+(dimensiones_cara.width)/4+(almacena.get_noses())[j].x,(almacena.get_faces())[i].y+(dimensiones_cara.height)/4+(almacena.get_noses())[j].y),Point((almacena.get_faces())[i].x+(dimensiones_cara.width)/4+(almacena.get_noses())[j].x+(almacena.get_noses())[j].width,(almacena.get_faces())[i].y+(dimensiones_cara.height)/4+(almacena.get_noses())[j].y+(almacena.get_noses())[j].height), Scalar( 0, 0, 0 ), 2, 8, 0 );		
		}

		for( size_t j = 0; j < (almacena.get_mouths()).size(); j++ ){ 
			//PINTAR BOCA
			rectangle(frame,Point((almacena.get_faces())[i].x+(almacena.get_mouths())[j].x,(almacena.get_faces())[i].y+(dimensiones_cara.height)/2+(almacena.get_mouths())[j].y),Point((almacena.get_faces())[i].x+(almacena.get_mouths())[j].x+(almacena.get_mouths())[j].width,(almacena.get_faces())[i].y+(dimensiones_cara.height)/2+(almacena.get_mouths())[j].y+(almacena.get_mouths())[j].height), Scalar( 0, 255, 0 ), 2, 8, 0 );

		}
		
		//line(frame,Point( (almacena.get_faces())[i].x+(dimensiones_cara.width)/2,(almacena.get_faces())[i].y),Point((almacena.get_faces())[i].x+(dimensiones_cara.width)/2,(almacena.get_faces())[i].y+dimensiones_cara.height),Scalar(20,20,20),2,8,0);
		//line(frame,Point( (almacena.get_faces())[i].x,(almacena.get_faces())[i].y + (dimensiones_cara.height)/2),Point((almacena.get_faces())[i].x+dimensiones_cara.width,(almacena.get_faces())[i].y+(dimensiones_cara.height)/2),Scalar(20,20,20),2,8,0);	
	}
	return(frame);

}
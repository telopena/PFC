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



		//line(frame,Point( (almacena.get_faces())[i].x+(dimensiones_cara.width)/2,(almacena.get_faces())[i].y),Point((almacena.get_faces())[i].x+(dimensiones_cara.width)/2,(almacena.get_faces())[i].y+dimensiones_cara.height),Scalar(20,20,20),2,8,0);
		//line(frame,Point( (almacena.get_faces())[i].x,(almacena.get_faces())[i].y + (dimensiones_cara.height)/2),Point((almacena.get_faces())[i].x+dimensiones_cara.width,(almacena.get_faces())[i].y+(dimensiones_cara.height)/2),Scalar(20,20,20),2,8,0);	
	}
	return(frame);

}
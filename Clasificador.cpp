#include "Clasificador.h"
#include <math.h>



Clasificador::Clasificador(void)
{
}


Clasificador::~Clasificador(void)
{
}


int Clasificador::Clasifica(Almacena cara,LucasKanade kanade){

	enum options {N,UP,R,D,L,OK,U} alg1,finalLR,alg3,finalUD,decision_final;




	for(size_t i = 0; i < (cara.get_faces()).size(); i++){


		Size dimensiones_cara=(cara.get_faces())[i].size();
		Point2f dimensiones_cara2;




		//ALGORITMO 1 IZQUIERDA-DERECHA BASADO EN LA DISTANCIA ENTRE EL CENTRO DEL NARIZ Y LA DIVISORIA//



		if ( (cara.get_noses()).size() != 0) {


			Point nose_center(	(dimensiones_cara.width)/4 + (cara.get_noses())[i].x + 	((cara.get_noses())[i].width)/2	, (dimensiones_cara.height)/4 + (cara.get_noses())[i].y + ((cara.get_noses())[i].height)/2);
			double porcentaje1 = (0.07) * ((cara.get_faces())[i].width);
			double porcentaje2 = (0.03) * ((cara.get_faces())[i].width);
			int resta1 = ((dimensiones_cara.width)/2) - nose_center.x ;

			if (resta1 > 0 ) { 
				if ( abs(resta1) > porcentaje1 ) {alg1=L;}
				if ( abs(resta1) < porcentaje1 ) {alg1=N;}
			}


			if (resta1 < 0 ) {
				if ( abs(resta1) > porcentaje2 ) {alg1=R;}
				if ( abs(resta1) < porcentaje2 ) {alg1=N;}
			}

		}

		if ( (cara.get_noses()).size() == 0 ) {

			dimensiones_cara2.x= (float) (((dimensiones_cara.width)/2) + cara.get_faces()[i].x ); 




			double porcentaje1 = (0.07) * ((cara.get_faces())[i].width);
			double porcentaje2 = (0.08) * ((cara.get_faces())[i].width);
			float resta1 = ((dimensiones_cara2.x) - kanade.get_points(1,0).x );


			if (resta1 < 0 ) { 
				if ( abs(resta1) > porcentaje1 ) {alg1=L;}
				if ( abs(resta1) < porcentaje1 ) {alg1=N;}
			}


			if (resta1 > 0 ) {
				if ( abs(resta1) > porcentaje2 ) {alg1=R;}
				if ( abs(resta1) < porcentaje2 ) {alg1=N;}
			}



		}






		finalLR=alg1;





		//ALGORITMO 3 BASADO EN POSICION CENTRO NARIZ RESPECTO MITAD ALTURA//

		if ( ((cara.get_noses()).size() != 0) ){

			Point nose_center(	(dimensiones_cara.width)/4 + (cara.get_noses())[i].x + 	((cara.get_noses())[i].width)/2	, (dimensiones_cara.height)/4 + (cara.get_noses())[i].y + ((cara.get_noses())[i].height)/2);
			double porcentaje3 = (0.07) * ((cara.get_faces())[i].height);
			double porcentaje4 = (0.015) * ((cara.get_faces())[i].height);
			int resta2 = ((dimensiones_cara.height)/2) - nose_center.y ;


			if (resta2 > 0 ) { 
				if ( abs(resta2) > porcentaje4 ) {alg3=UP;}
				if ( abs(resta2) < porcentaje4) {alg3=N;}
			}


			if (resta2 < 0 ) {
				if ( abs(resta2) > porcentaje3 ) {alg3=D;}
				if ( abs(resta2) < porcentaje3 ) {alg3=N;}
			}


		}


		if ( ((cara.get_noses()).size() != 0)  && ((cara.get_eyes_l()).size() != 0) && ((cara.get_eyes_r()).size() != 0)) {
			Point nose_up(  (dimensiones_cara.width)/4 + (cara.get_noses())[i].x + ((cara.get_noses())[i].width)/2   ,  (dimensiones_cara.height)/4 + (cara.get_noses())[i].y);
			Point eyer_center ((dimensiones_cara.width)/2 + (cara.get_eyes_r())[i].x + ((cara.get_eyes_r())[i].width)/2     ,  (cara.get_eyes_r())[i].y + ((cara.get_eyes_r())[i].height)/2);
			Point eyel_center( (cara.get_eyes_l())[i].x + ((cara.get_eyes_l())[i].width)/2     ,  (cara.get_eyes_l())[i].y + ((cara.get_eyes_l())[i].height)/2);
			if ( (nose_up.y <= eyer_center.y) || (nose_up.y <= eyel_center.y) ) {alg3=UP;}
		}


		if ( ((cara.get_noses()).size() == 0 ) ){


			dimensiones_cara2.y= (float) (((dimensiones_cara.height)/2) + cara.get_faces()[i].y); 

			
			double porcentaje1 = (0.08) * ((cara.get_faces())[i].height);
			double porcentaje2 = (0.08) * ((cara.get_faces())[i].height);
			float resta1 = ((dimensiones_cara2.y) - kanade.get_points(1,0).y );
			

			if (resta1 < 0 ) { 
				if ( abs(resta1) > porcentaje1 ) {alg3=UP;}
				if ( abs(resta1) < porcentaje1 ) {alg3=N;}
			}


			if (resta1 > 0 ) {
				if ( abs(resta1) > porcentaje2 ) {alg3=D;}
				if ( abs(resta1) < porcentaje2 ) {alg3=N;}
			}




		} 


		finalUD=alg3;







		if (	( (finalLR==L) && (finalUD==N) )  || ( (finalLR==L) && (finalUD==U ) )		){decision_final=L;}
		if (	( (finalLR==R) && (finalUD==N) )  || ( (finalLR==R) && (finalUD==U ) )		){decision_final=R;}
		if (	( (finalLR==N) && (finalUD==UP))  || ( (finalLR==U) && (finalUD==UP) )		){decision_final=UP;}
		if (	( (finalLR==N) && (finalUD==D) )  || ( (finalLR==U) && (finalUD==D)  )		){decision_final=D;}
		if (	( (finalLR==N) && (finalUD==N) ) ){decision_final=N;}
		if (    ( (finalLR==N) && (finalUD==U) ) || ( (finalLR==U) && (finalUD==N) )		 ){decision_final=N;}    







	}


	return(decision_final);
}
#include "Clasificador.h"
#include <math.h>


Clasificador::Clasificador(void)
{
}


Clasificador::~Clasificador(void)
{
}


void Clasificador::Clasifica(Almacena cara){

	int posicion=0;
	




	for(size_t i = 0; i < (cara.get_faces()).size(); i++){


		Size dimensiones_cara=(cara.get_faces())[i].size();
		enum options {L,R,D,UP,OK,N,U} alg1,alg2,finalLR,alg3,alg4,finalUD,decision_final;

		
		//ALGORITMO 1 IZQUIERDA-DERECHA BASADO EN LA DISTANCIA ENTRE EL CENTRO DEL NARIZ Y LA DIVISORIA//

		
		
		if ( (cara.get_noses()).size() != 0) {
			
			Point nose_center(	(dimensiones_cara.width)/4 + (cara.get_noses())[i].x + 	((cara.get_noses())[i].width)/2	, (dimensiones_cara.height)/4 + (cara.get_noses())[i].y + ((cara.get_noses())[i].height)/2);
			double porcentaje1 = (0.08) * ((cara.get_faces())[i].width);
			double porcentaje2 = (0.03) * ((cara.get_faces())[i].width);
			int resta1 = ((dimensiones_cara.width)/2) - nose_center.x ;

			if (resta1 > 0 ) { 
				if ( abs(resta1) > porcentaje1 ) {alg1=L;}//posicion=4;
				if ( abs(resta1) < porcentaje1 ) {alg1=N;}//posicion=0;
			}


			if (resta1 < 0 ) {
				if ( abs(resta1) > porcentaje2 ) {alg1=R;}//posicion=2;
				if ( abs(resta1) < porcentaje2 ) {alg1=N;}//posicion=0;
			}

		}

		if ( (cara.get_noses()).size() == 0 ) {alg1=U;}//posicion=6;
		
		
		
	
		
		//ALGORITMO 2 IZQUIERDA-DERECHA, BASÁNDONOS EN POSICIÓN BOCA/NARIZ//

		
		/*		
		if ( ((cara.get_noses()).size() != 0) && ((cara.get_mouths()).size() != 0) ) {

			Point nose_left( (dimensiones_cara.width)/4 + (cara.get_noses())[i].x   , (dimensiones_cara.height)/4 + (cara.get_noses())[i].y + ((cara.get_noses())[i].height)/2);
			Point nose_right( (dimensiones_cara.width)/4 + (cara.get_noses())[i].x + (cara.get_noses())[i].width   ,   (dimensiones_cara.height)/4 + (cara.get_noses())[i].y + ((cara.get_noses())[i].height)/2);
			Point mouth_left(  (cara.get_mouths())[i].x      ,   (dimensiones_cara.height)/2 + (cara.get_mouths())[i].y + ((cara.get_mouths())[i].height)/2);
			Point mouth_right( (cara.get_mouths())[i].x + (cara.get_mouths()[i]).width   ,  (dimensiones_cara.height)/2 + (cara.get_mouths())[i].y + ((cara.get_mouths())[i].height)/2);
			
			if ( mouth_right.x > nose_right.x ) {alg2=N;}// posicion=0;
			if ( mouth_right.x < nose_right.x ) {alg2=R;}// posicion=2;
			if ( mouth_left.x  > nose_left.x  ) {alg2=L;}//posicion=4;
		}

		if ( ((cara.get_noses()).size() == 0 ) || ((cara.get_noses()).size() == 0 ) ) {alg2=U;}//posicion=6;


		
		if (alg1 == alg2) {finalLR=alg1;}
		if (alg1 != alg2) {
		
			finalLR=alg1;

		}
		*/

		finalLR=alg1;
	

		
		//ALGORITMO 3 BASADO EN POSICION CENTRO NARIZ RESPECTO MITAD ALTURA//

		if ( ((cara.get_noses()).size() != 0)  && ((cara.get_eyes_l()).size() != 0) && ((cara.get_eyes_r()).size() != 0)) {
			
			Point nose_center(	(dimensiones_cara.width)/4 + (cara.get_noses())[i].x + 	((cara.get_noses())[i].width)/2	, (dimensiones_cara.height)/4 + (cara.get_noses())[i].y + ((cara.get_noses())[i].height)/2);
			Point nose_up(  (dimensiones_cara.width)/4 + (cara.get_noses())[i].x + ((cara.get_noses())[i].width)/2   ,  (dimensiones_cara.height)/4 + (cara.get_noses())[i].y);
			Point eyer_center ((dimensiones_cara.width)/2 + (cara.get_eyes_r())[i].x + ((cara.get_eyes_r())[i].width)/2     ,  (cara.get_eyes_r())[i].y + ((cara.get_eyes_r())[i].height)/2);
			Point eyel_center( (cara.get_eyes_l())[i].x + ((cara.get_eyes_l())[i].width)/2     ,  (cara.get_eyes_l())[i].y + ((cara.get_eyes_l())[i].height)/2);
			double porcentaje3 = (0.10) * ((cara.get_faces())[i].height);
			//double porcentaje4 = (0.05) * ((cara.get_faces())[i].height);
			int resta2 = ((dimensiones_cara.height)/2) - nose_center.y ;

			/*
			if (resta2 > 0 ) { 
				if ( abs(resta2) > porcentaje4 ) {alg3=UP;}//posicion=3;
				if ( abs(resta2) < porcentaje4) {alg3=N;}//posicion=0;
			}
			*/

			if (resta2 < 0 ) {
				if ( abs(resta2) > porcentaje3 ) {alg3=D;}//posicion=1;
				if ( abs(resta2) < porcentaje3 ) {alg3=N;}//posicion=0;
			}

			if ( (nose_up.y <= eyer_center.y) || (nose_up.y <= eyel_center.y) ) {alg3=UP;}//posicion=1;
		}

		if ( (cara.get_noses()).size() == 0 ) {alg3=U;}//posicion=6;
		

		finalUD=alg3;
		
		
		
		//ALGORITMO 4 ARRIBA/ABAJO, BASADO EN SUPERIOR NARIZ RESPECTO A OJOS Y INFERIOR BOCA RESPECTO A CARA//
		/*
		if(  ((cara.get_noses()).size() != 0) && ((cara.get_eyes_l()).size() != 0) && ((cara.get_eyes_r()).size() != 0) && ((cara.get_mouths()).size() != 0) ) {

			Point eyer_center ((dimensiones_cara.width)/2 + (cara.get_eyes_r())[i].x + ((cara.get_eyes_r())[i].width)/2     ,  (cara.get_eyes_r())[i].y + ((cara.get_eyes_r())[i].height)/2);
			Point eyel_center( (cara.get_eyes_l())[i].x + ((cara.get_eyes_l())[i].width)/2     ,  (cara.get_eyes_l())[i].y + ((cara.get_eyes_l())[i].height)/2);
			Point nose_up(  (dimensiones_cara.width)/4 + (cara.get_noses())[i].x + ((cara.get_noses())[i].width)/2   ,  (dimensiones_cara.height)/4 + (cara.get_noses())[i].y);
			Point mouth_up( (cara.get_mouths())[i].x + ((cara.get_mouths())[i].width)/2     , (dimensiones_cara.height)/2 + (cara.get_mouths())[i].y);
			Point nose_down(  (dimensiones_cara.width)/4 + (cara.get_noses())[i].x + ((cara.get_noses())[i].width)/2   ,  (dimensiones_cara.height)/4 + (cara.get_noses())[i].y + (cara.get_noses())[i].height);
			Point nose_center(	(dimensiones_cara.width)/4 + (cara.get_noses())[i].x + 	((cara.get_noses())[i].width)/2	, (dimensiones_cara.height)/4 + (cara.get_noses())[i].y + ((cara.get_noses())[i].height)/2);

			double porcentaje3 = (0.10) * ((cara.get_faces())[i].height);
			int resta3 = mouth_up.y - nose_center.y ;

			if (nose_up.y <= eyer_center.y) {alg4=UP;}//posicion=1;
			if (resta3 > 0 && abs(resta3)<porcentaje3){alg4=D;}//posicion=3;

		}
		
/*
		if (alg3 == alg4) {finalUD=alg3;}
		if (alg3 != alg4) {
			cout<<"DISTINTO"<<endl;
			finalUD=alg3;

		}
	*/	
		


		if ( (finalLR==L) && (finalUD==N) ){decision_final=L;}
		if ( (finalLR==R) && (finalUD==N) ){decision_final=R;}
		if ( (finalLR==N) && (finalUD==UP) ){decision_final=UP;}
		if ( (finalLR==N) && (finalUD==D) ){decision_final=D;}
		if ( (finalLR==N) && (finalUD==N) ){decision_final=N;}
		
		switch (decision_final)
		{
		case N: cout<<"Neutro"<<endl; 
			break;
		case UP: cout<<"Mirar hacia arriba"<<endl;
			break;
		case R: cout<<"Mirar hacia la derecha"<<endl;
			break;
		case D: cout<<"Mirar hacia abajo"<<endl;
			break;
		case L: cout<<"Mirar hacia la izquierda"<<endl;
			break;
		case OK: cout<<"Aceptar"<<endl;
			break;
		case U: cout<<"Desconocido"<<endl;
			break;

		}

		

	}


}
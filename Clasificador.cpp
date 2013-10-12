#include "Clasificador.h"
#include <math.h>



Clasificador::Clasificador(void)
{
}


Clasificador::~Clasificador(void)
{
}


int Clasificador::Clasifica(Almacena cara,LucasKanade kanade, int a){

	enum options {N,UP,R,D,L,U} alg1,finalLR,alg3,finalUD,decision_final;




	for(size_t i = 0; i < (cara.get_faces()).size(); i++){


		Size dimensiones_cara=(cara.get_faces())[i].size();
		Point2f dimensiones_cara2;

		if(a<20){
			if(cara.get_noses().size()!=0){
				Point nose_center((cara.get_noses())[i].x +((cara.get_noses())[i].width)/2	,(dimensiones_cara.height)/4 + (cara.get_noses())[i].y + ((cara.get_noses())[i].height)/2);
				int resta1 = (((dimensiones_cara.width)/2)) - nose_center.x ;
				restahorizontal= resta1;
				int resta2 = (((dimensiones_cara.height)/2)) - nose_center.y ;
				restavertical=resta2;
				decision_final=N;
			}

			else{decision_final=U;}
		}





		else{


			//ALGORITMO 1 IZQUIERDA-DERECHA BASADO EN LA DISTANCIA ENTRE EL CENTRO DEL NARIZ Y LA DIVISORIA//

			alg1=U;
			finalLR=U;
			alg3=U;
			finalUD=U;
			decision_final=U;

			if ( (cara.get_noses()).size() != 0) {

				Point nose_center((cara.get_noses())[i].x + ((cara.get_noses())[i].width)/2	,(dimensiones_cara.height)/4 + (cara.get_noses())[i].y + ((cara.get_noses())[i].height)/2);
				double porcentaje1 = ((0.05) * ((cara.get_faces())[i].width));
				double porcentaje2 = ((0.03) * ((cara.get_faces())[i].width));
				int resta1 = (((dimensiones_cara.width)/2)) - nose_center.x ;
				

				if(restahorizontal>0){

					if (resta1 > restahorizontal ) { 
						if ( abs(resta1-restahorizontal) > porcentaje2 ) {alg1=L;}
						if ( abs(resta1-restahorizontal) < porcentaje2 ) {alg1=N;}
					}


					if (resta1 < restahorizontal ) {
						if ( abs(restahorizontal-resta1) > porcentaje1 ) {alg1=R;}
						if ( abs(restahorizontal-resta1) < porcentaje1 ) {alg1=N;}
					}

				}



				if(restahorizontal<0){
					if (resta1 > restahorizontal ) { 
						if ( abs(resta1-restahorizontal) > porcentaje1 ) {alg1=L;}
						if ( abs(resta1-restahorizontal) < porcentaje1 ) {alg1=N;}
					}


					if (resta1 < restahorizontal ) {
						if ( abs(restahorizontal-resta1) > porcentaje2 ) {alg1=R;}
						if ( abs(restahorizontal-resta1) < porcentaje2 ) {alg1=N;}
					}

				}

			}


			if ( (cara.get_noses()).size() == 0 ) {
				
				dimensiones_cara2.x= (float) (((dimensiones_cara.width)/2)); 
				
				
				double porcentaje1 = ((0.05) * ((cara.get_faces())[i].width));
				double porcentaje2 = ((0.03) * ((cara.get_faces())[i].width));
				float resta1 = ((dimensiones_cara2.x) - kanade.get_points(1,0).x );


				if (restahorizontal>0){

					if (resta1 > restahorizontal ) { 
						if ( abs(restahorizontal-resta1) > porcentaje2 ) {alg1=L;}
						if ( abs(restahorizontal-resta1) < porcentaje2 ) {alg1=N;}
					}


					if (resta1 < restahorizontal ) {
						if ( abs(resta1-restahorizontal) > porcentaje1 ) {alg1=R;}
						if ( abs(resta1-restahorizontal) < porcentaje1 ) {alg1=N;}
					}

				}


				if (restahorizontal<0){

					if (resta1 > restahorizontal ) { 
						if ( abs(restahorizontal-resta1) > porcentaje1 ) {alg1=L;}
						if ( abs(restahorizontal-resta1) < porcentaje1 ) {alg1=N;}
					}


					if (resta1 < restahorizontal ) {
						if ( abs(resta1-restahorizontal) > porcentaje2 ) {alg1=R;}
						if ( abs(resta1-restahorizontal) < porcentaje2 ) {alg1=N;}
					}

				}
			
			}

			




			finalLR=alg1;





			//ALGORITMO 3 BASADO EN POSICION CENTRO NARIZ RESPECTO MITAD ALTURA//

			if ( ((cara.get_noses()).size() != 0) ){

				Point nose_center((cara.get_noses())[i].x +((cara.get_noses())[i].width)/2	,(dimensiones_cara.height)/4 + (cara.get_noses())[i].y + ((cara.get_noses())[i].height)/2);
				double porcentaje3 = (0.05) * ((cara.get_faces())[i].height);
				double porcentaje4 = (0.03) * ((cara.get_faces())[i].height);
				int resta2 = (((dimensiones_cara.height)/2)) - nose_center.y ;

				if(restavertical>0){

					if (resta2 > restavertical ) { 
						if ( abs(resta2-restavertical) > porcentaje4 ) {alg3=UP;}
						if ( abs(resta2-restavertical) < porcentaje4) {alg3=N;}
					}


					if (resta2 < restavertical ) {
						if ( abs(restavertical-resta2) > porcentaje3 ) {alg3=D;}
						if ( abs(restavertical-resta2) < porcentaje3 ) {alg3=N;}
					}

				}


				if(restavertical<0){

					if (resta2 > restavertical ) { 
						if ( abs(resta2-restavertical) > porcentaje3 ) {alg3=UP;}
						if ( abs(resta2-restavertical) < porcentaje3) {alg3=N;}
					}


					if (resta2 < restavertical ) {
						if ( abs(restavertical-resta2) > porcentaje4 ) {alg3=D;}
						if ( abs(restavertical-resta2) < porcentaje4 ) {alg3=N;}
					}

				}


			}


	

			if ( ((cara.get_noses()).size() == 0 ) ){
				
				
				dimensiones_cara2.y= (float) (((dimensiones_cara.height)/2)); 


				double porcentaje3 = (0.05) * ((cara.get_faces())[i].height);
				double porcentaje4 = (0.03) * ((cara.get_faces())[i].height);
				float resta1 = ((dimensiones_cara2.y) - kanade.get_points(1,0).y );


				if(restavertical>0){


					if (resta1 > restavertical ) { 
						if ( abs(restavertical-resta1) > porcentaje4 ) {alg3=UP;}
						if ( abs(restavertical-resta1) < porcentaje4 ) {alg3=N;}
					}


					if (resta1 < restavertical ) {
						if ( abs(resta1-restavertical) > porcentaje3 ) {alg3=D;}
						if ( abs(resta1-restahorizontal) < porcentaje3 ) {alg3=N;}
					}
				}

				if(restavertical<0){

					if (resta1 > restavertical ) { 
						if ( abs(restavertical-resta1) > porcentaje3 ) {alg3=UP;}
						if ( abs(restavertical-resta1) < porcentaje3 ) {alg3=N;}
					}


					if (resta1 < restavertical ) {
						if ( abs(resta1-restavertical) > porcentaje4 ) {alg3=D;}
						if ( abs(resta1-restahorizontal) < porcentaje4 ) {alg3=N;}
					}


				}




			} 

			
			finalUD=alg3;







			if (	( (finalLR==L) && (finalUD==N) )  || ( (finalLR==L) && (finalUD==U ) )		){decision_final=L;}
			if (	( (finalLR==R) && (finalUD==N) )  || ( (finalLR==R) && (finalUD==U ) )		){decision_final=R;}
			if (	( (finalLR==N) && (finalUD==UP))  || ( (finalLR==U) && (finalUD==UP) )		){decision_final=UP;}
			if (	( (finalLR==N) && (finalUD==D) )  || ( (finalLR==U) && (finalUD==D)  )		){decision_final=D;}
			if (	( (finalLR==N) && (finalUD==N) ) ){decision_final=N;}
			if (    ( (finalLR==N) && (finalUD==U) ) || ( (finalLR==U) && (finalUD==N) )		 ){decision_final=N;}    
			if (    ( (finalLR==U) && (finalUD==U) )		 ){decision_final=U;}




		}

	}


	return(decision_final);
}
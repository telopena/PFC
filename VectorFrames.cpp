/*
# Copyright (C) 2013 Eutelo Pena Barreiro
# 
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License Version 3
# as published by the Free Software Foundation.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#  
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 */

#include "VectorFrames.h"


VectorFrames::VectorFrames(void)
{
}


VectorFrames::~VectorFrames(void)
{
}




void VectorFrames::addtovector(FrameClasificado frame){

	frames.push_back(frame);
}

std::vector<FrameClasificado> VectorFrames::getvector(){
	return(frames);
}


int VectorFrames:: comprobar(int i, double marca){
	double time;
	int aux=i;

	while(frames[aux].getdetect()!=1){
		aux--;
	}
	time=frames[aux].getTime();

	if(marca-time <3000){return(1);}
	else{return(0);}

}


void VectorFrames:: Decide(int i,double marca,Mat velocara,Almacena cara,int profilesL, int profilesR, Mat pintar){

	if(i==0){frames[i].setlanzado(1);}

	enum options {N,UP,R,D,L,U} alg1,alg2,decision;
	alg1=U;
	alg2=U;
	int contquietohor=0;
	int contnoquietohor=0;
	int contquietover=0;
	int contnoquietover=0;
	int contador=0;
	int aux=i;
	double time;
	time=frames[i].getTime();

	for(size_t w = 0; w < (cara.get_faces()).size(); w++){

		if(i>20){



			while(marca-time <1000){

				aux--;
				time=frames[aux].getTime();
				contador++;
				if(abs(frames[i].getposcenter_x() - frames[aux].getposcenter_x()) < 0.08*cara.get_faces()[w].width){contquietohor++;}
				else{contnoquietohor++;}
				if(abs(frames[i].getposcenter_y() - frames[aux].getposcenter_y()) < 0.06*cara.get_faces()[w].height){contquietover++;}
				else{contnoquietover++;}

			}

			if(contquietohor>contnoquietohor  && contquietohor> 0.8 *contador){frames[i].setmy_decisionhor(0);}
			else{frames[i].setmy_decisionhor(1);}
			if(contquietover>contnoquietover  && contquietover> 0.8 *contador){frames[i].setmy_decisionver(0);}
			else{frames[i].setmy_decisionver(1);}




			line(velocara,Point(0,120),Point(320,120),Scalar(255,255,255),1,8,0);
			line(velocara,Point(160,0),Point(160,240),Scalar(255,255,255),1,8,0);


			if(frames[i].getmy_decisionhor()==0){line(velocara,Point(160,120),Point(160+40,120),Scalar(0,0,255),2,8,0);}//quiero rojo
			if(frames[i].getmy_decisionhor()==1){line(velocara,Point(160,120),Point(160+40,120),Scalar(255,0,0),2,8,0);}//movimiento azul
			if(frames[i].getmy_decisionver()==0){line(velocara,Point(160,120),Point(160,120-40),Scalar(0,0,255),2,8,0);}//quiero rojo
			if(frames[i].getmy_decisionver()==1){line(velocara,Point(160,120),Point(160,120-40),Scalar(255,0,0),2,8,0);}//movimiento azul



			aux=i;

			if(frames[i].getmy_decisionhor()==0){
				int comp;
				bool evento=false;
				aux--;
				int contposi=0;
				int contnega=0;
				int contprofilesL = 0;
				int contprofilesR = 0;
				int contadoraux = 0;



				while(frames[aux].getmy_decisionhor()!=0 && aux>=0){

					if(frames[aux].getposcenter_x() > frames[i].getposcenter_x()){contposi++;}
					if(frames[aux].getposcenter_x() < frames[i].getposcenter_x()){contnega++;}
					comp=abs(frames[i].getposcenter_x() - frames[aux].getposcenter_x());
					if(comp>0.18*cara.get_faces()[w].width){evento=true;}
					if (frames[aux].getprofileR() == 1) {
						contprofilesR++;
					}

					if (frames[aux].getprofileL() == 1) {
						contprofilesL++;
					}
					aux--;
					contadoraux++;

				}

				if(aux!=i-1){

					if(abs(frames[i].getposcenter_x() - frames[aux].getposcenter_x()) < 0.10*cara.get_faces()[w].width){

						if(evento==true){

							frames[i].setalgdecision(1);
							if(contposi>contnega){alg1=R;}
							if(contnega>contposi){alg1=L;}


						}
					}

					if (abs(
						frames[i].getposcenter_x()
						- frames[aux].getposcenter_x())
							> 0.18 * cara.get_faces()[w].width) {
								int der=0;
								int izq=0;
								int aux2=i;


								for(int b=0;b<3;b++){

									if(frames[aux2].getfacestate()==2){izq++;}
									if(frames[aux2].getfacestate()==3){der++;}
									aux2--;

								}

								if(izq>=2 || (profilesL == 1
									&& contprofilesL > 0.7 * contadoraux)){

										frames[i].setalgdecision(2);
										alg1 = L;
								}
								if(der>=2|| (profilesR == 1
									&& contprofilesR > 0.7 * contadoraux) ){
										frames[i].setalgdecision(2);
										alg1 = R;
								}

					}


				}

				else {

					while (frames[aux].getlanzado() != 1) {

						if (frames[aux].getmy_decisionhor() == 1) {
							break;
						}
						aux--;
					}

					if (frames[aux].getalgdecision() == 2) {

						if (marca - frames[aux].getTime() > 1000) {

							frames[i].setalgdecision(2);

							switch (frames[aux].getalg1()) {
							case 2:
								alg1 = R;
								break;
							case 4:
								alg1 = L;
								break;

							}

						}
					}


				}

			}



			aux=i;
			if(frames[i].getmy_decisionver()==0){
				aux--;
				int comp2;
				bool evento2=false;
				int contposi=0;
				int contnega=0;

				while(frames[aux].getmy_decisionver()!=0  && aux>=0){
					if(frames[aux].getposcenter_y() > frames[i].getposcenter_y()){contposi++;}
					if(frames[aux].getposcenter_y() < frames[i].getposcenter_y()){contnega++;}
					comp2=abs(frames[i].getposcenter_y() - frames[aux].getposcenter_y());
					if(comp2>0.18*cara.get_faces()[w].height){evento2=true;}
					aux--;

				}

				if(aux!=i-1){

					if(abs(frames[i].getposcenter_y() - frames[aux].getposcenter_y()) < 0.15*cara.get_faces()[w].height){

						if(evento2==true){
							if(contposi>contnega){alg2=D;}
							if(contnega>contposi){alg2=UP;}




						}
					}
				}
			}



			Point izq(0,120);
			Point der(230,120);
			Point arr(120,10);
			Point aba(120,240);


			if ((alg1==L) && (alg2==U)){frames[i].setalg1(L);decision=L;cout<<"izquierda"<<endl;putText(pintar,"IZQUIERDA",izq,FONT_HERSHEY_COMPLEX_SMALL,0.80,(255,255,0),1,8);}
			if ((alg1==R) && (alg2==U)){frames[i].setalg1(R);decision=R;cout<<"derecha"<<endl;putText(pintar,"DERECHA",der,FONT_HERSHEY_COMPLEX_SMALL,0.80,(255,255,0),1,8);}
			if ((alg1==U) && (alg2==UP)){decision=UP;cout<<"arriba"<<endl;putText(pintar,"ARRIBA",arr,FONT_HERSHEY_COMPLEX_SMALL,0.80,(255,255,0),1,8);}
			if ((alg1==U) && (alg2==D)){decision=D;cout<<"abajo"<<endl;putText(pintar,"ABAJO",aba,FONT_HERSHEY_COMPLEX_SMALL,0.80,(255,255,0),1,8);}

			if(decision==L || decision==R || decision==UP || decision==D){
				frames[i].setlanzado(1);
				aux = i;
				while ((frames[aux].getlanzado()) != 1) {
					frames.erase(frames.begin(), frames.begin() + aux);
					aux--;

				}

			}

		}





	}





}
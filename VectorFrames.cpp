#include "VectorFrames.h"


VectorFrames::VectorFrames(void)
{
}


VectorFrames::~VectorFrames(void)
{
}


void VectorFrames::Decide(int i){

	int aux=i;
	double time;
	int contador=0;

	if(i==0){
		frames[i].setlanzado(1);

		switch (frames[i].getmy_decision())
		{
		case 0: cout<<"Neutro"<<endl; 
			break;
		case 1: cout<<"Mirar hacia arriba"<<endl;
			break;
		case 2: cout<<"Mirar hacia la derecha"<<endl;
			break;
		case 3: cout<<"Mirar hacia abajo"<<endl;
			break;
		case 4: cout<<"Mirar hacia la izquierda"<<endl;
			break;
		case 5: cout<<"Aceptar"<<endl;
			break;
		case 6: cout<<"Desconocido"<<endl;
			break;

		}


	}

	else{

		while( (frames[aux].getlanzado())!= 1){
			time=frames[aux].getTime();
			aux--;

		}

		if (  (frames[i].getTime() - time)  > 1000 ){

			for(int j=1;j<11;j++){

				if( (frames[i].getmy_decision()) == (frames[i-j].getmy_decision()) ){contador++;}
			}

			if (contador > 4) {

				frames[i].setlanzado(1);


				switch (frames[i].getmy_decision())
				{
				case 0: cout<<"Neutro"<<endl; 
					break;
				case 1: cout<<"Mirar hacia arriba"<<endl;
					break;
				case 2: cout<<"Mirar hacia la derecha"<<endl;
					break;
				case 3: cout<<"Mirar hacia abajo"<<endl;
					break;
				case 4: cout<<"Mirar hacia la izquierda"<<endl;
					break;
				case 5: cout<<"Aceptar"<<endl;
					break;
				case 6: cout<<"Desconocido"<<endl;
					break;

				}
				aux=i;

				while( (frames[aux].getlanzado())!= 1){
					frames.erase(frames.begin(),frames.begin()+aux);
					aux--;

				}

			}

		}


	}

}


void VectorFrames::addtovector(FrameClasificado frame){

	frames.push_back(frame);
}

std::vector<FrameClasificado> VectorFrames::getvector(){
	return(frames);
}
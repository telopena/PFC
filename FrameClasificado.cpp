#include "FrameClasificado.h"


FrameClasificado::FrameClasificado(void)
{
	lanzado=0;
}


FrameClasificado::~FrameClasificado(void)
{
}

void FrameClasificado::setTime(double time){
	my_time=time;

}

void FrameClasificado::setmy_decision(int decision){

	my_decision=decision;

}

void FrameClasificado:: setlanzado(int lanzar){
	lanzado=lanzar;
}


double FrameClasificado:: getTime(){
	return(my_time);
}

int FrameClasificado:: getmy_decision(){
	return(my_decision);

}

int FrameClasificado:: getlanzado(){
	return(lanzado);
}
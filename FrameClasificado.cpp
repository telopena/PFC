#include "FrameClasificado.h"


FrameClasificado::FrameClasificado(void)
{
}


FrameClasificado::~FrameClasificado(void)
{
}

void FrameClasificado::setTime(double time){
	my_time=time;

}

void FrameClasificado:: setLR( enum options aux){
	my_LR=aux;
}

void FrameClasificado:: setUD(enum options aux){
	my_UD=aux;
}

double FrameClasificado:: getTime(){
	return(my_time);
}


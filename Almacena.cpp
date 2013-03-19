#include "Almacena.h"


Almacena::Almacena(void)
{
}


Almacena::~Almacena(void)
{
}

void Almacena::set_faces(std::vector<Rect> faces){
	myfaces=faces;
}

void Almacena::set_eyes_r(std::vector<Rect> eyes_r){
	myeyes_r=eyes_r;
}

void Almacena::set_eyes_l(std::vector<Rect> eyes_l){
	myeyes_l=eyes_l;
}

void Almacena::set_noses(std::vector<Rect> noses){
	mynoses=noses;
}

void Almacena::set_mouths(std::vector<Rect> mouths){
	mymouths=mouths;
}

void Almacena::set_time(double time){
	mytime=time;
}

std::vector<Rect> Almacena::get_faces(){
	return(myfaces);
}

std::vector<Rect> Almacena::get_eyes_r(){
	return(myeyes_r);
}

std::vector<Rect> Almacena::get_eyes_l(){
	return(myeyes_l);
}

std::vector<Rect> Almacena::get_noses(){
	return(mynoses);
}

std::vector<Rect> Almacena::get_mouths(){
	return(mymouths);
}

double Almacena::get_time(){ 
	return(mytime);
}
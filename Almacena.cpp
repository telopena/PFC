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


void Almacena:: set_P0(Point2f aux){
	P0=aux;
}

void Almacena:: set_P1(Point2f aux1){
	P1=aux1;
}

void Almacena:: set_P2(Point2f aux2){
	P2=aux2;
}

void Almacena:: set_P3(Point2f aux3){
	P3=aux3;
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



Point2f Almacena:: get_P0(){
	return(P0);
}

Point2f Almacena:: get_P1(){
	return(P1);
}

Point2f Almacena:: get_P2(){
	return(P2);
}

Point2f Almacena:: get_P3(){
	return(P3);
}
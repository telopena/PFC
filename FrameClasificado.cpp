#include "FrameClasificado.h"

FrameClasificado::FrameClasificado(void) {
	lanzado = 0;
	algdecision = 0;
	my_decisionhor=0;
	my_decisionver=0;
	alg1 = 5;
	profileL=0;
	profileR=0;

}

FrameClasificado::~FrameClasificado(void) {
}

void FrameClasificado::setTime(double time) {
	my_time = time;

}

void FrameClasificado::setmy_decisionhor(int decision) {

	my_decisionhor = decision;

}

void FrameClasificado::setmy_decisionver(int decision) {
	my_decisionver = decision;
}

void FrameClasificado::setlanzado(int lanzar) {
	lanzado = lanzar;
}

void FrameClasificado::setdetect(int detect) {
	caradetect = detect;
}

void FrameClasificado::setposcenter_x(int x) {
	poscenter_x = x;
}

void FrameClasificado::setposcenter_y(int y) {
	poscenter_y = y;
}

void FrameClasificado::setalgdecision(int algo) {
	algdecision = algo;
}

void FrameClasificado::setalg1(int algLR) {
	alg1 = algLR;
}

void FrameClasificado::setprofileR(int profile){
	profileR=profile;
}

void FrameClasificado::setprofileL(int profile){
	profileL=profile;
}



double FrameClasificado::getTime() {
	return (my_time);
}

int FrameClasificado::getmy_decisionhor() {
	return (my_decisionhor);

}

int FrameClasificado::getmy_decisionver() {
	return (my_decisionver);
}

int FrameClasificado::getlanzado() {
	return (lanzado);
}

int FrameClasificado::getdetect() {

	return (caradetect);
}

int FrameClasificado::getposcenter_x() {
	return (poscenter_x);
}

int FrameClasificado::getposcenter_y() {
	return (poscenter_y);
}

int FrameClasificado::getalgdecision() {
	return (algdecision);
}

int FrameClasificado::getalg1() {
	return (alg1);
}

int FrameClasificado::getprofileR(){
	return(profileR);
}

int FrameClasificado::getprofileL(){
	return(profileL);
}

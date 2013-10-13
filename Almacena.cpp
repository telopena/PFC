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



std::vector<Rect> Almacena::get_faces(){
	return(myfaces);
}


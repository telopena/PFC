#include "LucasKanade.h"


LucasKanade::LucasKanade(void) {

}


LucasKanade::~LucasKanade(void)
{

}

void LucasKanade:: set_points(Point2f aux, int x, int y){

	points[x].insert((points[x].begin())+y,aux);

}



void LucasKanade:: calcula_fujo_optico(Mat pregray, Mat gray){


	TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03);
	vector<uchar> status;
	vector<float> err;
	calcOpticalFlowPyrLK(pregray, gray,points[0], points[1], status, err, Size(31,31),3, termcrit, 0, 0.001);


}


Point2f LucasKanade:: get_points(int x,int y){


	return(points[x][y]);

}

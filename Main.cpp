#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/video/tracking.hpp"

#include <iostream>
#include <stdio.h>
#include "FaceDetector.h"
#include "Draw.h"
#include "Almacena.h"
#include "Clasificador.h"
#include "FrameClasificado.h"
#include "VectorFrames.h"
#include <time.h>
#include "LucasKanade.h"

using namespace std;
using namespace cv;


int main( void )
{

	CvCapture* capture;
	Mat frame_capturado,frame_gray,frame_pregay,hsv,mask,hue,hist,backproj,mat_aux,template_cara1,template_cara2,template_nariz1,template_nariz2,result1,result2,result_n1,result_n2;
	Almacena almacena;
	Draw draw;
	FaceDetector face_detector;
	Clasificador clasificador;
	FrameClasificado frame_clasificado;
	VectorFrames vector_frames;
	LucasKanade kanade;
	NoseDetector nose;
	int retorno,vmin = 10, vmax = 256, smin = 30,hsize = 16,i=0;
	double t_fps,marca;
	double minVal,minVal_n,maxVal,maxVal_n;
	Size dimensiones_cara,dimensiones_nariz;
	Point2f p3;
	std::vector<Rect> faces;
	std::vector<Rect> aux2;
	float hranges[] = {0,180};
	const float* phranges = hranges;
	CvConnectedComp track_comp;
	Rect trackWindow,aux,aux_n;
	IplImage img1,img2,img;
	CvPoint minloc,minloc_n,maxloc,maxloc_n;




	capture = cvCaptureFromCAM(-1);

	if( capture )
	{
		for(;;)
		{  

			t_fps = (double)cv::getTickCount();
			frame_capturado = cvQueryFrame( capture );
			marca= ((double)cv::getTickCount())*1000. / cv::getTickFrequency(); //REFERENCIA DESDE QUE ENCENDIU O PC
			flip(frame_capturado,frame_capturado,1);
			cvtColor(frame_capturado ,frame_gray , CV_BGR2GRAY );
			cvtColor(frame_capturado, hsv, CV_BGR2HSV);
			equalizeHist( frame_gray, frame_gray );
			

			//ME QUEDO SOLO CON EL CANAL HUE//
			//int ch[] = {0, 0};
			//hue.create(hsv.size(), hsv.depth());
			//mixChannels(&hsv, 1, &hue, 1, ch, 1);

			//imshow("gray",frame_gray);
			//imshow("hue",hue);


			
			//FILTRO PARA CADA CANAL, CON VALORES MÁXIMOS Y MÍNIMOS, y guardo en mask
			inRange(hsv, Scalar(0, smin, MIN(vmin,vmax)),
				Scalar(180, 256, MAX(vmin, vmax)), mask);

			//me quedo solo con el canal hue
			int ch[] = {0, 0};
			hue.create(hsv.size(), hsv.depth());
			mixChannels(&hsv, 1, &hue, 1, ch, 1);
			

			if( !frame_gray.empty() )
			{ 

				almacena=face_detector.Detect(frame_gray); 



				if(almacena.get_faces().size()!=0){

					cout<<"entro"<<endl;

					faces=almacena.get_faces();



					for(size_t w = 0; w < (almacena.get_faces()).size(); w++){

						dimensiones_cara=(almacena.get_faces())[w].size();
						
						template_cara1=frame_gray(faces[w]).clone();
						template_cara2=hue(faces[w]);
						imshow("template1",template_cara1);
						imshow("template2",template_cara2);
					

						
						//OBTENGO ZONAS DE INTERES Y CALCULO HISTOGRAMA DE DICHA ZONA
						Mat roi= hue (faces[w]);
						roi= roi(Range((dimensiones_cara.height)/4,(dimensiones_cara.height)*3/4),Range((dimensiones_cara.width)/4,(dimensiones_cara.width)*3/4));
						Mat maskroi = mask (faces[w]);
						maskroi= maskroi(Range((dimensiones_cara.height)/4,(dimensiones_cara.height)*3/4),Range((dimensiones_cara.width)/4,(dimensiones_cara.width)*3/4));
						calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
						imshow("hist",hist);
						normalize(hist, hist, 0, 255, CV_MINMAX);
						

						trackWindow=faces[w];
						

						if( (almacena.get_noses()).size() != 0) {

							dimensiones_nariz=almacena.get_noses()[w].size();
							Point2f p2((float)((almacena.get_noses())[w].x + 	((almacena.get_noses())[w].width)/2	), (float)((dimensiones_cara.height)/4 + (almacena.get_noses())[w].y + ((almacena.get_noses())[w].height)/2)); 
							Point2f p2p((float)(almacena.get_faces()[w].x +(almacena.get_noses())[w].x + 	((almacena.get_noses())[w].width)/2	), (float)(almacena.get_faces()[w].y + (dimensiones_cara.height)/4 + (almacena.get_noses())[w].y + ((almacena.get_noses())[w].height)/2)); 
							kanade.set_points(p2,0,0);
							line(frame_capturado,p2p,p2p,Scalar(255,0,0),3,8,0);
							p3=p2;
							template_nariz1=template_cara1(Range((dimensiones_cara.height)/4,(dimensiones_cara.height)*3/4),Range::all());
							template_nariz1=template_nariz1(almacena.get_noses()[w]).clone();
							//template_nariz2=template_cara2(Range((dimensiones_cara.height)/4,(dimensiones_cara.height)*3/4),Range::all());
							//template_nariz2=template_nariz2(almacena.get_noses()[w]);
							imshow("template3",template_nariz1);
							//imshow("template4",template_nariz2);

						}


						if( (almacena.get_noses()).size()==0){
							kanade.set_points(p3,0,0);
						}

						if( (i!=0) && ( (almacena.get_noses()).size() ==0) ){

							kanade.calcula_fujo_optico(frame_pregay,frame_gray);
							Point pnp(kanade.get_points(1,0).x+almacena.get_faces()[w].x,kanade.get_points(1,0).y+almacena.get_faces()[w].y);
							line(frame_capturado,pnp,pnp,Scalar(255,0,0),3,8,0);

						}


					}




					frame_capturado=draw.Dibujar(frame_capturado,almacena);
					retorno=clasificador.Clasifica(almacena,kanade,i);
					frame_clasificado.setmy_decision(retorno);
					frame_clasificado.setTime(marca);
					frame_clasificado.setdetect(1);
					vector_frames.addtovector(frame_clasificado);
					vector_frames.Decide(i);
					
					i++;
					t_fps = ((double)cv::getTickCount() - t_fps) / cv::getTickFrequency();
					cout << "I am working at " << 1/t_fps << " FPS" << std::endl;
				}

				if(i!=0 ){//&& (vector_frames.comprobar(i,marca)==1)){

				//result1.create(frame_gray.rows-template_cara1.rows +1,frame_gray.cols-template_cara1.cols +1,frame_gray.depth());
				//result2.create(hue.rows-template_cara2.rows +1,hue.cols-template_cara2.cols +1,hue.depth());
				imshow("template1",template_cara1);
					matchTemplate(frame_gray,template_cara1,result1,CV_TM_CCOEFF_NORMED);
				//matchTemplate(hue,template_cara2,result2,CV_TM_CCOEFF_NORMED);
				imshow("result1",result1);
				//imshow("result2",result2);
				img1=result1;
				//img1=result2;
				cvMinMaxLoc(&img1,&minVal,&maxVal,&minloc,&maxloc);
				aux.x=maxloc.x;
				aux.y=maxloc.y;
				aux.width=dimensiones_cara.width;
				aux.height=dimensiones_cara.height;
				rectangle(frame_capturado,Point(aux.x,aux.y),Point(aux.x + aux.width,aux.y+aux.height),Scalar(0,0,255),1,CV_AA);
				
				
				matchTemplate(frame_gray,template_nariz1,result_n1,CV_TM_CCOEFF_NORMED);
				//matchTemplate(hue,template_nariz2,result_n2,CV_TM_CCOEFF_NORMED);
				imshow("template3",template_nariz1);
				imshow("result_n1",result_n1);
				//imshow("result_n2",result_n2);
				img2=result_n1;
				//img2=result_n2;
				cvMinMaxLoc(&img2,&minVal_n,&maxVal_n,&minloc_n,&maxloc_n);
				aux_n.x=maxloc_n.x;
				aux_n.y=maxloc_n.y;
				aux_n.width=dimensiones_nariz.width;
				aux_n.height=dimensiones_nariz.height;
				rectangle(frame_capturado,Point(aux_n.x,aux_n.y),Point(aux_n.x + aux_n.width,aux_n.y+aux_n.height),Scalar(0,0,255),1,CV_AA);
				
				}

	/*			if( (almacena.get_faces().size()==0) ){

					if((i!=0) && (vector_frames.comprobar(i,marca)==1) ){

						if(aux.x<0){aux.x=0;}
						if(aux.y<0){aux.y=0;}
						if(aux.x+aux.width > frame_gray.cols){aux.width=frame_gray.cols;}
						if(aux.y+aux.height >frame_gray.rows){aux.height=frame_gray.rows;}
						mat_aux=frame_gray(aux);
						mat_aux=mat_aux(Range((dimensiones_cara.height)/4,(dimensiones_cara.height)*3/4),Range::all());
						nose.setROI(mat_aux);
						nose.Detect();
						almacena.set_noses(nose.getVector());
						aux2.assign(1,aux);
						almacena.set_faces(aux2);

						for(size_t w = 0; w < (almacena.get_faces()).size(); w++){

							if( (almacena.get_noses()).size() != 0) {
							
								Point2f p2((float)((almacena.get_noses())[w].x + 	((almacena.get_noses())[w].width)/2	), (float)((dimensiones_cara.height)/4 + (almacena.get_noses())[w].y + ((almacena.get_noses())[w].height)/2)); 
								kanade.set_points(p2,0,0);
								Point2f p2p((float)(almacena.get_faces()[w].x +	 (almacena.get_noses())[w].x + 	((almacena.get_noses())[w].width)/2	), (float)(almacena.get_faces()[w].y + (dimensiones_cara.height)/4 + (almacena.get_noses())[w].y + ((almacena.get_noses())[w].height)/2)); 
								line(frame_capturado,p2p,p2p,Scalar(255,0,0),3,8,0);
								p3=p2;
							}

							if( (almacena.get_noses()).size()==0){
								kanade.set_points(p3,0,0);
							}


							if( (i!=0) && ( (almacena.get_noses()).size() ==0) ){

								kanade.calcula_fujo_optico(frame_pregay,frame_gray);
								Point pnp(kanade.get_points(1,0).x+almacena.get_faces()[w].x,kanade.get_points(1,0).y+almacena.get_faces()[w].y);
								line(frame_capturado,pnp,pnp,Scalar(255,0,0),3,8,0);


							}

						}



						frame_capturado=draw.Dibujar(frame_capturado,almacena);
						retorno=clasificador.Clasifica(almacena,kanade,i);
						frame_clasificado.setmy_decision(retorno);
						frame_clasificado.setTime(marca);
						frame_clasificado.setdetect(0);
						vector_frames.addtovector(frame_clasificado);
						vector_frames.Decide(i);
						i++;
					
					}
					
					t_fps = ((double)cv::getTickCount() - t_fps) / cv::getTickFrequency();
					cout << "I am working at " << 1/t_fps << " FPS" << std::endl;
				}
				
		*/		

				

				//TRACKING
				if(i!=0  && (vector_frames.comprobar(i,marca)==1)){
					calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
					imshow("back",backproj);
					backproj &= mask;
					img=backproj;
					cvMeanShift(&img, trackWindow,cvTermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 15, 1 ),&track_comp);
					aux=track_comp.rect;
					rectangle(frame_capturado,Point(aux.x,aux.y),Point(aux.x + aux.width,aux.y+aux.height),Scalar(0,0,255),3,CV_AA);
				}
				
				

				/*
				if( (almacena.get_faces().size()==0) ){

					if((i!=0) && (vector_frames.comprobar(i,marca)==1) ){

						if(aux.x<0){aux.x=0;}
						if(aux.y<0){aux.y=0;}
						if(aux.x+aux.width > frame_gray.cols){aux.width=frame_gray.cols;}
						if(aux.y+aux.height >frame_gray.rows){aux.height=frame_gray.rows;}
						mat_aux=frame_gray(aux);
						dimensiones_cara=mat_aux.size();
						mat_aux=mat_aux(Range((dimensiones_cara.height)/4,(dimensiones_cara.height)*3/4),Range::all());
						nose.setROI(mat_aux);
						nose.Detect();
						almacena.set_noses(nose.getVector());
						aux2.assign(1,aux);
						almacena.set_faces(aux2);

						for(size_t w = 0; w < (almacena.get_faces()).size(); w++){

							if( (almacena.get_noses()).size() != 0) {
							
								Point2f p2((float)((almacena.get_noses())[w].x + 	((almacena.get_noses())[w].width)/2	), (float)((dimensiones_cara.height)/4 + (almacena.get_noses())[w].y + ((almacena.get_noses())[w].height)/2)); 
								kanade.set_points(p2,0,0);
								Point2f p2p((float)(almacena.get_faces()[w].x +	 (almacena.get_noses())[w].x + 	((almacena.get_noses())[w].width)/2	), (float)(almacena.get_faces()[w].y + (dimensiones_cara.height)/4 + (almacena.get_noses())[w].y + ((almacena.get_noses())[w].height)/2)); 
								line(frame_capturado,p2p,p2p,Scalar(255,0,0),3,8,0);
								p3=p2;
							}

							if( (almacena.get_noses()).size()==0){
								kanade.set_points(p3,0,0);
							}


							if( (i!=0) && ( (almacena.get_noses()).size() ==0) ){

								kanade.calcula_fujo_optico(frame_pregay,frame_gray);
								Point pnp(kanade.get_points(1,0).x+almacena.get_faces()[w].x,kanade.get_points(1,0).y+almacena.get_faces()[w].y);
								line(frame_capturado,pnp,pnp,Scalar(255,0,0),3,8,0);


							}

						}



						frame_capturado=draw.Dibujar(frame_capturado,almacena);
						retorno=clasificador.Clasifica(almacena,kanade,i);
						frame_clasificado.setmy_decision(retorno);
						frame_clasificado.setTime(marca);
						frame_clasificado.setdetect(0);
						vector_frames.addtovector(frame_clasificado);
						vector_frames.Decide(i);
						i++;
					
					}
					
					t_fps = ((double)cv::getTickCount() - t_fps) / cv::getTickFrequency();
					cout << "I am working at " << 1/t_fps << " FPS" << std::endl;
				}
				
				*/
				imshow("Aplicación",frame_capturado);


			}



			else

			{ printf(" --(!) No captured frame -- Break!"); break; }

			int c = waitKey(10);

			if( (char)c == 'c' ) { break; }

			frame_gray.copyTo(frame_pregay);







		}
	}
	cvReleaseCapture( &capture );
	face_detector.~FaceDetector();
	almacena.~Almacena();
	clasificador.~Clasificador();
	draw.~Draw();
	frame_clasificado.~FrameClasificado();
	vector_frames.~VectorFrames();
	kanade.~LucasKanade();
	nose.~NoseDetector();
	return 0;
}


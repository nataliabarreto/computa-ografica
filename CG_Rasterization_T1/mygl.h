#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include "math.h"
#include <vector>
#include <iostream>

class Vetor{
public:
	int x,y;
	uint8_t r, g, b, a;
	Vetor(int _x, int _y, uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a){
		 x = _x;
		 y = _y;
		 r = _r;
		 g = _g;
		 b = _b;
		 a = _a;
	}
	
};

void putPixel(Vetor xyRGBA){
	if(xyRGBA.x < 0 || xyRGBA.y <0) return;

	int offset = xyRGBA.x*4 + xyRGBA.y * IMAGE_WIDTH * 4;

	FBptr[offset + 0] = xyRGBA.r;
	FBptr[offset + 1] = xyRGBA.g;
	FBptr[offset + 2] = xyRGBA.b;
	FBptr[offset + 3] = xyRGBA.a;

}

void drawLine(Vetor V1, Vetor V2) {
	int dx = V2.x - V1.x;
	int dy = V2.y - V1.y;
	int d, incr_e, incr_ne, x ,y;
	x = V1.x;
	y = V1.y;
	//Interpolação
	double dist = sqrt(pow(dx,2)+ pow(dy,2));
	double difR = ((int)V2.r - (int)V1.r)/dist;
	double difG = ((int)V2.g - (int)V1.g)/dist;
	double difB = ((int)V2.b - (int)V1.b)/dist;
	double difA = ((int)V2.a - (int)V1.a)/dist;
	int i = 1;

	if(dx >= 0 && dy >= 0){
		if(abs(dx) >= abs(dy)){
			//1 octante , função do slide
			d = (2*dy) - dx;
			incr_e = 2 *dy;
			incr_ne = 2*(dy - dx);
			putPixel(Vetor(x,y,V1.r,V1.g,V1.b,V1.a));

			while (x < V2.x){
				if(d < 0){
					d += incr_e;
					x++;
				}else {
					d += incr_ne;
					x++;
					y++;
				}	
				putPixel(Vetor(x,y,V1.r + difR*i,V1.g + difG*i,V1.b +difB*i,V1.a + difA*i));
				i++;
			}
		}else{
			// 2 octante
			d = dy-2*dx;
      		incr_e = 2*(dy-dx);
			incr_ne = -2*dx;
			putPixel(Vetor(x,y,V1.r,V1.g,V1.b,V1.a));

			while (y < V2.y){
				if(d < 0){
					d += incr_e;
					x++;
					y++;
				}else {
					d += incr_ne;
					y++;
					
				}
			
				putPixel(Vetor(x,y,V1.r + difR*i,V1.g + difG*i,V1.b +difB*i,V1.a + difA*i));
				i++;
			}
		}
	} else if(dx <= 0 && dy >= 0) {
		if(abs(dx) <= abs(dy)){
			//3 octante
			d = -dy - 2*dx;
			incr_e = 2*(-dx);
			incr_ne = 2*(-dy-dx);
			putPixel(Vetor(x,y,V1.r,V1.g,V1.b,V1.a));

			while (y < V2.y){
				if(d < 0){
					d += incr_e;
					y++;
				}else {
					d += incr_ne;
					x--;
					y++;
				}
			
				putPixel(Vetor(x,y,V1.r + difR*i,V1.g + difG*i,V1.b +difB*i,V1.a + difA*i));
				i++;
			}
		}else{
			//4 octante
			d =  -2*dy - dx;
			incr_ne = 2*(-dy - dx);
			incr_e = 2*(-dy);
			putPixel(Vetor(x,y,V1.r,V1.g,V1.b,V1.a));

			
			while (x > V2.x){
			
				if(d < 0){
					d += incr_ne;
					x--;
					y++;
				}else {
					d += incr_e;
					x--;
				}
			
				putPixel(Vetor(x,y,V1.r + difR*i,V1.g + difG*i,V1.b +difB*i,V1.a + difA*i));
				i++;
			}
		}
	} else{	
		//Usando os outros 4 octantes, usei a função de uma forma reversa, espelhando os octantes para os 5,6,7,8
			drawLine(V2,V1);
	}
	
}
void drawTriangle(Vetor V1,Vetor V2, Vetor V3){
	drawLine(V1,V2);
	drawLine(V3,V1);
	drawLine(V2,V3);
}
#endif // _MYGL_H_


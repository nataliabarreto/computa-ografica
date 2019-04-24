 #ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include <cmath>
#include <iomanip>
#include <vector>

#include "objLoader.h"
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************

class Vector
{
public:

	unsigned int x, y, z;
	unsigned char r, g, b, a;


	Vector(unsigned int x, unsigned int y, unsigned int z, unsigned char r, unsigned char g, unsigned char b, unsigned char a){
		this->x = x;
		this->y = y;
		this->z = z;
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	Vector(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a){
		this->x = x;
		this->y = y;
		this->z = 0;
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	Vector(glm::vec4 v, unsigned char r, unsigned char g, unsigned char b, unsigned char a){
		x = v.x;
		y = v.y;
		z = v.z;
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
};

void putPixel( Vector xyRGBA){
	if(xyRGBA.x < 0 || xyRGBA.y <0 || xyRGBA.x >511 || xyRGBA.y>511) return;

	int offset = xyRGBA.x*4 + xyRGBA.y * IMAGE_WIDTH * 4;

	FBptr[offset + 0] = xyRGBA.r;
	FBptr[offset + 1] = xyRGBA.g;
	FBptr[offset + 2] = xyRGBA.b;
	FBptr[offset + 3] = xyRGBA.a;

}
void DrawLine( Vector V1, Vector V2) {
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
			putPixel(Vector(x,y,V1.r,V1.g,V1.b,V1.a));

			while (x < V2.x){
				if(d < 0){
					d += incr_e;
					x++;
				}else {
					d += incr_ne;
					x++;
					y++;
				}	
				putPixel(Vector(x,y,V1.r + difR*i,V1.g + difG*i,V1.b +difB*i,V1.a + difA*i));
				i++;
			}
		}else{
			// 2 octante
			d = dy-2*dx;
      		incr_e = 2*(dy-dx);
			incr_ne = -2*dx;
			putPixel(Vector(x,y,V1.r,V1.g,V1.b,V1.a));

			while (y < V2.y){
				if(d < 0){
					d += incr_e;
					x++;
					y++;
				}else {
					d += incr_ne;
					y++;
					
				}
			
				putPixel(Vector(x,y,V1.r + difR*i,V1.g + difG*i,V1.b +difB*i,V1.a + difA*i));
				i++;
			}
		}
	} else if(dx <= 0 && dy >= 0) {
		if(abs(dx) <= abs(dy)){
			//3 octante
			d = -dy - 2*dx;
			incr_e = 2*(-dx);
			incr_ne = 2*(-dy-dx);
			putPixel(Vector(x,y,V1.r,V1.g,V1.b,V1.a));

			while (y < V2.y){
				if(d < 0){
					d += incr_e;
					y++;
				}else {
					d += incr_ne;
					x--;
					y++;
				}
			
				putPixel(Vector(x,y,V1.r + difR*i,V1.g + difG*i,V1.b +difB*i,V1.a + difA*i));
				i++;
			}
		}else{
			//4 octante
			d =  -2*dy - dx;
			incr_ne = 2*(-dy - dx);
			incr_e = 2*(-dy);
			putPixel(Vector(x,y,V1.r,V1.g,V1.b,V1.a));

			
			while (x > V2.x){
			
				if(d < 0){
					d += incr_ne;
					x--;
					y++;
				}else {
					d += incr_e;
					x--;
				}
			
				putPixel(Vector(x,y,V1.r + difR*i,V1.g + difG*i,V1.b +difB*i,V1.a + difA*i));
				i++;
			}
		}
	} else{	
		//Usando os outros 4 octantes, usei a função de uma forma reversa, espelhando os octantes para os 5,6,7,8
			DrawLine(V2,V1);
	}
	
}
void DrawTriangle(Vector V1, Vector V2, Vector V3){
	DrawLine(V1,V2);
	DrawLine(V3,V1);
	DrawLine(V2,V3);
}

glm::mat4 scaleModel(const glm::vec3& scale = glm::vec3()){
	glm::mat4 scaleMatrix(scale.x,0,0,0,
    					  0,scale.y,0,0,
    					  0,0,scale.z,0,
    					  0,0,0,1);
	return scaleMatrix;
}

glm::mat4 rotModel(const glm::vec3& rot = glm::vec3()){
    glm::mat4 rotX(1,0		 ,0			 ,0,
    					 0,cos(rot.x),-sin(rot.x),0,
    					 0,sin(rot.x), cos(rot.x),0,
    					 0,0          ,0         ,1);
    glm::mat4 rotY(cos(rot.y) ,0,sin(rot.y),0,
    					 0          ,1,0         ,0,
    					 -sin(rot.y),0,cos(rot.y),0,
    					 0          ,0,0         ,1);
    glm::mat4 rotZ(cos(rot.z),-sin(rot.z),0        ,0,
    					 sin(rot.z),cos(rot.z) ,0        ,0,
    					 0         ,0         ,1         ,0,
    					 0         ,0         ,0         ,1);
    glm::mat4 rotMatrix = rotZ * rotY * rotX;
    return  rotMatrix;
}
glm::mat4 translationModel(const glm::vec3& translation = glm::vec3()){
    glm::mat4 translationMatrix(1,0,0,translation.x,
    					0,1,0,translation.y,
    					0,0,1,translation.z,
    					0,0,0,1);
   
    return translationMatrix;
}
//Transformação: Espaço do Objeto → Espaço do Universo
glm::mat4 getModel(const glm::mat4& translation = glm::mat4(),const glm::mat4& scale = glm::mat4(), const glm::mat4& rot = glm::mat4()){
    glm::mat4 matrixModel = translation*scale*rot;
    return  matrixModel;
}
//Transformação: Espaço do Universo → Espaço da Câmera
glm::mat4 getView(const glm::vec3& pos, const glm::vec3& lookat, const glm::vec3& up){
	glm::vec3 camera_dir = lookat - pos; 
	glm::vec3 z_camera = -(camera_dir) / glm::length(camera_dir); 
	glm::vec3 x_camera = glm::cross(up, z_camera) / glm::length(glm::cross(up, z_camera));
	glm::vec3 y_camera = glm::cross(z_camera, x_camera);


	glm::mat4 Bt(x_camera.x, x_camera.y, x_camera.z, 0, 
			     y_camera.x, y_camera.y, y_camera.z, 0, 
			     z_camera.x, z_camera.y, z_camera.z, 0, 
			     0		   , 0		   , 0		   , 1);
	glm::mat4 T(1, 0, 0, -pos.x, 
		        0, 1, 0, -pos.y, 
		        0, 0, 1, -pos.z, 
		        0, 0, 0,      1);
	glm::mat4 matrixView = Bt * T;
	return matrixView;	

}
//Transformação: Espaço da Câmera → Espaço Projetivo ou de Recorte
glm::mat4 getProjection(float d)
{
	glm::mat4 projection(1.0,0.0,0.0,0.0,
                		 0.0,1.0,0.0,0.0,
                		 0.0,0.0,1.0,d,
                		 0.0,0.0,-1/d,1);
	return projection;
}
glm::mat4 modelViewProjection(glm::mat4 Model,glm::mat4 View, glm::mat4 Projection){
	return Model*View*Projection;
}
//Transformação: Espaço Canônico → Espaço de Tela
//valores das escalas e translation incializados no main.cpp
glm::mat4 getViewport(glm::mat4 s1,glm::mat4 T, glm::mat4 s2){
	return s1*T*s2;
}
//Transformação: Espaço de Recorte → Espaço “Canônico”
glm::vec4 homogeneous(glm::vec4 matrix){
		matrix.x /= matrix.w;
		matrix.y /= matrix.w;
		matrix.z /= matrix.w;
		matrix.w /= matrix.w;
		return matrix;
}
		





#endif // _MYGL_H_


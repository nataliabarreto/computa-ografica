#include "main.h"
#include "mygl.h"
#include <cmath>
#include <vector>
#include "objLoader.h"
#include <complex>
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

void Clear(){
	memset(FBptr, 0, IMAGE_WIDTH * IMAGE_HEIGHT * 4);
}
objLoader *obj;
//-----------------------------------------------------------------------------
int ry = 0;
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************	
	Clear();
	ry++; // rotacao em y
	
	obj->load("monkey_head2.obj");

	std::vector<glm::vec4> vetores;

	glm::mat4 modelviewprojection = modelViewProjection(getProjection(5),
				  getView(glm::vec3(0,0,5),  glm::vec3(0,0,0), glm::vec3(0,1,0)),
				  getModel(translationModel(glm::vec3(0,0,0)),  rotModel(glm::vec3(0,0.01*ry,0)),  scaleModel(glm::vec3(0.6f,0.6f,0.6f) )));
	
	glm::mat4 s1 = scaleModel(glm::vec3(1,-1,1));
	glm::mat4 T = translationModel(glm::vec3(1,1,0));
	glm::mat4 s2 = scaleModel(glm::vec3(IMAGE_WIDTH/2.0,IMAGE_HEIGHT/2.0,1));

	
	glm::mat4 viewport=getViewport(s1,T,s2);

	for (int i = 0; i < obj->vertexCount; ++i)
	{	
		float x = obj->vertexList[i]->e[0],y = obj->vertexList[i]->e[1],z = obj->vertexList[i]->e[2] , w = 1;
		vetores.push_back(glm::vec4(x,y,z,w));

		vetores[i] = modelviewprojection* vetores[i];

		vetores[i] = homogeneous( vetores[i]);

		vetores[i] = vetores[i]*viewport;
		
	}

			
	
	for(unsigned int i=0; i<obj->faceCount; i++){
		if(	   vetores[obj->faceList[i]->vertex_index[0]].x>IMAGE_HEIGHT || vetores[obj->faceList[i]->vertex_index[0]].y>IMAGE_HEIGHT
			|| vetores[obj->faceList[i]->vertex_index[0]].x<0|| vetores[obj->faceList[i]->vertex_index[0]].y<0 
			|| vetores[obj->faceList[i]->vertex_index[1]].x>IMAGE_HEIGHT|| vetores[obj->faceList[i]->vertex_index[1]].y> IMAGE_HEIGHT
			|| vetores[obj->faceList[i]->vertex_index[1]].x<0|| vetores[obj->faceList[i]->vertex_index[1]].y<0 
			|| vetores[obj->faceList[i]->vertex_index[2]].x>IMAGE_HEIGHT|| vetores[obj->faceList[i]->vertex_index[2]].y> IMAGE_HEIGHT
			|| vetores[obj->faceList[i]->vertex_index[2]].x<0|| vetores[obj->faceList[i]->vertex_index[2]].y<0 )	{}	
		else {
			DrawTriangle(Vector( vetores[obj->faceList[i]->vertex_index[0]],255,255,255,255),Vector( vetores[obj->faceList[i]->vertex_index[1]], 255,255,255,255),
						 Vector( vetores[obj->faceList[i]->vertex_index[2]],255,255,255,255));
		}
	}
	
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	obj = new objLoader();
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}


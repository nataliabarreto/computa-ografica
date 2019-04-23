#include "main.h"

//-----------------------------------------------------------------------------
void MyGlDraw(void) {
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************
	putPixel(Vetor(256,256,255,255,255,255));
	/*drawLine( Vetor(256 , 256 ,255 , 0, 0, 255), Vetor(0 , 0, 0 , 0, 255, 255) );
	drawLine( Vetor(256 , 256 ,255 , 0, 0, 255), Vetor(128 , 0,0 , 0, 255, 255) );
	drawLine( Vetor(256 , 256 ,255 , 0, 0, 255), Vetor(256 , 0 ,0 , 0, 255, 255) );
	drawLine( Vetor(256 , 256	 ,255 , 0, 0, 255), Vetor(384 , 0,0 , 0, 255, 255) );
	drawLine( Vetor(256 , 256 ,255 , 0, 0, 255), Vetor(511 , 0,0 , 0, 255, 255) );

	drawLine( Vetor(256 , 256 ,255 , 0, 0, 255), Vetor(0 , 128,0 , 0, 255, 255) );
	drawLine( Vetor(256 , 256 ,255 , 0, 0, 255), Vetor(0 , 256 ,0 , 0, 255, 255)  );
	drawLine( Vetor(256 , 256	 ,255 , 0, 0, 255), Vetor(0 , 384,0 , 0, 255, 255)  );
	drawLine( Vetor(256 , 256 ,255 , 0, 0, 255), Vetor(0 , 511,0 , 0, 255, 255)  );
	
	drawLine( Vetor(256 , 256 ,255 , 0, 0, 255), Vetor(511 , 0,0 , 0, 255, 255)  );
	drawLine( Vetor(256 , 256 ,255 , 0, 0, 255), Vetor(511 , 128,0 , 0, 255, 255)  );
	drawLine( Vetor(256 , 256 ,255 , 0, 0, 255), Vetor(511 , 256 ,0 , 0, 255, 255)  );
	drawLine( Vetor(256 , 256	 ,255 , 0, 0, 255), Vetor(511 , 384,0 , 0, 255, 255)  );
	drawLine( Vetor(256 , 256 ,255 , 0, 0, 255), Vetor(511 , 511,0 , 0, 255, 255)  );
	
	drawLine( Vetor(256 , 256 ,255 , 0, 0, 255), Vetor(0 , 511,0 , 0, 255, 255)  );
	drawLine( Vetor(256 , 256 ,255 , 0, 0, 255), Vetor(128 , 511,0 , 0, 255, 255)  );
	drawLine( Vetor(256 , 256 ,255 , 0, 0, 255), Vetor(256 , 511 ,0 , 0, 255, 255)  );
	drawLine( Vetor(256 , 256	 ,255 , 0, 0, 255), Vetor(384 , 511,0 , 0, 255, 255)  );
	drawLine( Vetor(256 , 256 ,255 , 0, 0, 255), Vetor(511 , 511,0 , 0, 255, 255) );
	*/
	//drawTriangle(Vetor(128 , 384 ,255 , 0, 0, 255), Vetor(256 , 128,0 , 255, 0, 255),Vetor(384, 384 ,0 , 0, 255, 255));	
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv) {
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
#include "main.h"

//-----------------------------------------------------------------------------

void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************

    //Escreve um pixel vermelho na posição (0,0) da tela:
    /*
    FBptr[0] = 255;
    FBptr[1] = 0;
    FBptr[2] = 0;
    FBptr[3] = 255;

    //Escreve um pixel verde na posicao (1,0) da tela:

    FBptr[4] = 0;
    FBptr[5] = 255;
    FBptr[6] = 0;
    FBptr[7] = 255;

    //Escreve um pixel azul na posicao (1,1) da tela:

    FBptr[8] = 0;
    FBptr[9] = 0;
    FBptr[10] = 255;
    FBptr[11] = 255;*/

    /*for(unsigned int i = 0; i < 250; i++) {

        FBptr[4*i + 4*i*IMAGE_WIDTH + 0] = 255;
        FBptr[4*i + 4*i*IMAGE_WIDTH + 1] = 0;
        FBptr[4*i + 4*i*IMAGE_WIDTH + 2] = 255;
        FBptr[4*i + 4*i*IMAGE_WIDTH + 3] = 255;
    }*/


    //DrawTriangle(0,256,c0,256,0,c0,512,256,c0);
    //DrawTriangle(int x0, int y0, Color c0, int x1, int y1, Color c1, int x2, int y2, Color c2);

}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h

    Color c0;
    Color c1;
    Color c2;
    //c0.r = 255;

    c0.g = 255;
    c0.r = 0;
    c0.b = 255;
    c1.r = 0;
    c1.g = 255;
    c1.b = 0;
    c1.r = 0;
    c1.g = 0;
    c1.b = 255;

    //c0.a = 120;
    
    DrawTriangle(256,0,c0,0,256,c1,512,256,c0);
    /*Drawline(0,511,511,0,c0);
    Drawline(0, 481, 481, 0, c0);
    Drawline(0, 451, 451, 0, c0);*/
    

	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

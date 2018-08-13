#include "main.h"

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
    //*************************************************************************
    // Chame aqui as funções do mygl.h
    //*************************************************************************

    struct pixel P1 = {336, 30, 255, 0, 0, 255};
    struct pixel P2 = {196, 450, 0, 255, 0, 255};
    struct pixel P3 = {456, 450, 0, 0, 255, 255};
    struct pixel P4 = {70, 30, 255, 255, 0, 255};
    struct pixel P5 = {70, 430, 255, 0, 255, 255};
    struct pixel P6 = {270, 30, 0, 255, 255, 255};
/*
    drawTriangle(P1, P2, P3);
    drawTriangle(P4, P5, P6);*/

    /*pixel P1 = {256, 256, 50, 50, 50, 255};
    pixel P2 = {0, 0, 255, 0, 0, 255};
    pixel P3 = {256, 0, 0, 255, 0, 255};
    pixel P4 = {512, 0, 0, 0, 255, 255};
    pixel P5 = {512, 256, 242, 141, 19, 255};
    pixel P6 = {512, 512, 255, 0, 255, 255};
    pixel P7 = {256, 512, 255, 255, 0, 255};
    pixel P8 = {0, 512, 0, 255, 255, 255};
    pixel P9 = {0, 256, 199, 0, 255, 255};

    drawLine(P1, P2);
    drawLine(P1, P3);
    drawLine(P1, P4);
    drawLine(P1, P5);
    drawLine(P1, P6);
    drawLine(P1, P7);
    drawLine(P1, P8);
    drawLine(P1, P9);*/

    // R
	for(int i = 20; i<=75; i++){
		struct pixel P = {50, i, 255, 0, 0, 255};
		i = i + 3;
		putPixel(P);
	}
	for(int i = 50; i<=90; i++){
		struct pixel P = {i, 20, 255, 0, 0, 255};
		i = i+3;
		putPixel(P);
	}
	for(int i = 20; i<=40; i++){
		struct pixel P = {93, i, 255, 0, 0, 255};
		i = i + 3;
		putPixel(P);
	}
	for(int i = 69; i<=94; i++){
		struct pixel P = {i, 43, 255, 0, 0, 255};
		i = i+3;
		putPixel(P);
	}
	int x = 69;
	int y = 45;
	for(int i=0; i<9; i++){
		struct pixel P = {x, y, 255, 0, 0, 255};
		x+= 3;
		y+= 3;
		putPixel(P);
	}
	// FIM DE R

	// G
	for(int i = 20; i<=70; i++){
		struct pixel P = {130, i, 0, 255, 0, 255};
		i = i + 3;
		putPixel(P);
	}
	for(int i = 130; i<=170; i++){
		struct pixel P = {i, 20, 0, 255, 0, 255};
		i = i+3;
		putPixel(P);
	}
	for(int i = 134; i<=170; i++){
		struct pixel P = {i, 68, 0, 255, 0, 255};
		i = i+3;
		putPixel(P);
	}
	for(int i = 44; i<=68; i++){
		struct pixel P = {170, i, 0, 255, 0, 255};
		i = i + 3;
		putPixel(P);
	}
	for(int i = 150; i<=170; i++){
		struct pixel P = {i, 44, 0, 255, 0, 255};
		i = i+3;
		putPixel(P);
	}
	// FIM DE G

	// B
	for(int i = 20; i<=70; i++){
		struct pixel P = {210, i, 0, 0, 255, 255};
		i = i + 3;
		putPixel(P);
	}
	for(int i = 210; i<=250; i++){
		struct pixel P = {i, 20, 0, 0, 255, 255};
		i = i+3;
		putPixel(P);
	}
	for(int i = 210; i<=250; i++){
		struct pixel P = {i, 70, 0, 0, 255, 255};
		i = i+3;
		putPixel(P);
	}
	for(int i = 50; i<=70; i++){
		struct pixel P = {250, i, 0, 0, 255, 255};
		i = i + 3;
		putPixel(P);
	}
	for(int i = 20; i<=40; i++){
		struct pixel P = {250, i, 0, 0, 255, 255};
		i = i + 3;
		putPixel(P);
	}
	x = 245;
	y = 46;
	for(int i=0; i<3; i++){
		struct pixel P = {x, y, 0, 0, 255, 255};
		x+= 2;
		y-= 2;
		putPixel(P);
	}
	x = 245;
	y = 46;
	for(int i=0; i<3; i++){
		struct pixel P = {x, y, 0, 0, 255, 255};
		x+= 2;
		y+= 2;
		putPixel(P);
	}
	for(int i = 230; i<=244; i++){
		struct pixel P = {i, 46, 0, 0, 255, 255};
		i = i+3;
		putPixel(P);
	}
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
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

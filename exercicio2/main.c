//*****************************************************
//
// ExemploLinhas2D.cpp
// Um programa OpenGL simples que abre uma janela GLUT
// e faz o desenho de duas linhas
//
// Marcelo Cohen e Isabel H. Manssour
// Este c�digo acompanha o livro
// "OpenGL - Uma Abordagem Pr�tica e Objetiva"
//
//*****************************************************

#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void Desenha(){
    float ang;
    glClear(GL_COLOR_BUFFER_BIT);

	// Altera a cor do desenho para preta


	// Desenha um c�rculo de linhas

	glBegin(GL_QUAD_STRIP);
        glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-45.0f, 15.0f);
		glVertex2f(-45.0f,-15.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(-15.0f, 15.0f);
		glVertex2f(-15.0f,-15.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f( 15.0f, 15.0f);
		glVertex2f( 15.0f,-15.0f);

	glEnd();
	// Executa os comandos OpenGL
	glFlush();
}

// Fun��o callback chamada quando o tamanho da janela � alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Especifica as dimens�es da Viewport
	glViewport(0, 0, w, h);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de sele��o (esquerda, direita, inferior,
	// superior) mantendo a propor��o com a janela de visualiza��o
	if (w <= h)
		gluOrtho2D (-50.0f, 50.0f, -50.0f*h/w, 50.0f*h/w);
	else
		gluOrtho2D (-50.0f*w/h, 50.0f*w/h, -50.0f, 50.0f);
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// Programa Principal
int main(void)
{
	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(5,5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(600, 400);

	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Exemplo com GL_LINES");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a fun��o respons�vel por fazer as inicializa��es
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}

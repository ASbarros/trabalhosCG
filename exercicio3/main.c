//*****************************************************
//
// ExemploLinhas2D.cpp
// Um programa OpenGL simples que abre uma janela GLUT
// e faz o desenho de duas linhas
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro
// "OpenGL - Uma Abordagem Prática e Objetiva"
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


	// Desenha um círculo de linhas
	glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-25.0f,-20.0f);
		glColor3f(0.9f, 0.9f, 0.9f);
		glVertex2f(-25.0f, 20.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(20.0f, 20.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(20.0f,-20.0f);
	glEnd();

	// Altera a cor do desenho para cinza
	glLineWidth(5);
	glColor3f(0.3f, 1.0f, 0.3f);
	// Desenha uma seqüencia de triângulos
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(5.5f,  9.0f);
		glVertex2f(-35.0f,  9.0f);
		glVertex2f(-15.0f, 29.0f);
	glEnd();

	glColor3f(0.0f,0.0f,0.0f);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
        glVertex2d(5,9);
        glVertex2d(-35,9);
        glVertex2d(-15,29);
	glEnd();

	///-------------------------------------------------------
	glPointSize(9);
	glBegin(GL_POINTS);
        glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(20, 20);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2d(20, -20);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2d(-25, 20);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2d(-25, -20);
	glEnd();
	///------------------------------------------------------------------------------------------
	glLineWidth(3);
	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
		glVertex2f(20, 0);
		glVertex2d(5,-25);
		glVertex2d(35, -25);
	glEnd();
	///----------------------------------------------------------------------------------------------
	glColor3f(0.0f, 0.0f, 1.0f);
	glLineWidth(2);
    glBegin(GL_LINES);
        glVertex2d(-4,-6);
        glVertex2d(4,6);
    glEnd();
    glBegin(GL_LINES);
        glVertex2d(4,-6);
        glVertex2d(-4,6);
    glEnd();
    glBegin(GL_LINES);
        glVertex2d(-6,0);
        glVertex2d(6,0);
    glEnd();
    ///------------------------------------------------------------------------------------
    glColor3f(1.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2d(4,6);
        glVertex2d(6,0);
        glVertex2d(4,-6);
        glVertex2d(-4,-6);
        glVertex2d(-6,0);
        glVertex2d(-4,6);
    glEnd();

    ///-------------------------------------------------------------------------------------
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2d(-75,-50);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2d(-55,-30);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2d(-50,-50);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex2d(-30,-30);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex2d(-75,-50);
        glVertex2d(-50,-50);
        glVertex2d(-55,-30);
    glEnd();

    glBegin(GL_LINES);
        glVertex2d(-50,-50);
        glVertex2d(-30,-30);
        glVertex2d(-30,-30);
        glVertex2d(-55,-30);
    glEnd();

	// Executa os comandos OpenGL
	glFlush();
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção (esquerda, direita, inferior,
	// superior) mantendo a proporção com a janela de visualização
	if (w <= h)
		gluOrtho2D (-50.0f, 50.0f, -50.0f*h/w, 50.0f*h/w);
	else
		gluOrtho2D (-50.0f*w/h, 50.0f*w/h, -50.0f, 50.0f);
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// Programa Principal
int main(void)
{
	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(600, 400);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Exemplo com GL_LINES");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a função responsável por fazer as inicializações
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}

//*****************************************************
//
// ObjetoComTransformacoesHierarquicas.cpp
// Um programa OpenGL simples que abre uma janela GLUT,
// desenha e permite interagir com um objeto que é
// modelado através da utilização de transformações
// hierárquicas.
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro
// "OpenGL - Uma Abordagem Prática e Objetiva"
//
//*****************************************************

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

// Declaração de variáveis globais
GLfloat tx = 0;
GLfloat ang1 = 0, ang2 = -180;
GLfloat win = 25;
const GLfloat ESCALA_INICIAL = 1.3f;
GLfloat escalaAlterada = 0.0f;

// Função para desenhar um "braço" do objeto
void DesenhaBraco()
{
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
		glVertex2f(1.0,4.6);
		glVertex2f(1.0,-0.8);
		glVertex2f(-1.0,-0.8);
		glVertex2f(-1.0,4.6);
	glEnd();
	glPointSize(2);
	glBegin(GL_POINTS);
		glVertex2i(0,0);
	glEnd();
}

// Função para desenhar a base do objeto
void DesenhaBase()
{
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
		glVertex2f(1.8,1);
		glVertex2f(1.8,-1.5);
		glVertex2f(1.0,-1.5);
		glVertex2f(1.0,-1);
		glVertex2f(-1.0,-1);
		glVertex2f(-1.0,-1.5);
		glVertex2f(-1.8,-1.5);
		glVertex2f(-1.8,1);
	glEnd();
}

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Muda para o sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa a matriz de transformação corrente
	glLoadIdentity();

	// Limpa a janela de visualização com a cor
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Desenha um objeto modelado com transformações hierárquicas

	glPushMatrix();

	//desenha braço azul...
	glRotatef(ang2,0.0f,0.0f,1.0f);
	glTranslatef(0.4f,0.0f,0.0f);
	glColor3f(0.0f,0.0f,1.0f);
	DesenhaBraco();

	//desenha braço verde...
	glTranslatef(0.0f,3.5f,0.0f);
	glRotatef(ang1,0.0f,0.0f,1.0f);

	glPushMatrix();
	glScalef(ESCALA_INICIAL + escalaAlterada, ESCALA_INICIAL + escalaAlterada, 1.0f);
	glColor3f(0.0f,1.0f,0.0f);
	DesenhaBraco();
	glPopMatrix();

    glTranslatef(tx,5.0f,0.0f);

	glScalef(2.5f,2.3f,1.0f);
	glColor3f(1.0f,0.0f,0.0f);
	DesenhaBase();

	glPopMatrix();

	// Executa os comandos OpenGL
	glFlush();
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	GLsizei largura, altura;

	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as variáveis
	largura = w;
	altura = h;

	// Especifica as dimensões da Viewport
	glViewport(0, 0, largura, altura);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção (esquerda, direita, inferior,
	// superior) mantendo a proporção com a janela de visualização
	if (largura <= altura)
	{
		gluOrtho2D (-25.0f, 25.0f, -25.0f*altura/largura, 25.0f*altura/largura);
		win = 25.0f;
	}
	else
	{
		gluOrtho2D (-25.0f*largura/altura, 25.0f*largura/altura, -25.0f, 25.0f);
		win = 25.0f*largura/altura;
	}
}

// Função callback chamada para gerenciar eventos de teclas especiais(F1,PgDn,...)
void TeclasEspeciais(int key, int x, int y)
{
	// Rotaciona braco1
	if(key == GLUT_KEY_HOME)
		if (ang2 > -210)
            ang2-=5;
	if(key == GLUT_KEY_END)
        if (ang2 < -150)
            ang2+=5;

	// Rotaciona braco2
	if(key == GLUT_KEY_PAGE_UP)
        if (ang1 - 5 > -50)
            ang1-=5;
	if(key == GLUT_KEY_PAGE_DOWN)
        if (ang1 + 5 < 50)
            ang1+=5;
    if (key == GLUT_KEY_UP)
        if (escalaAlterada + 0.1f < 1.5f)
            escalaAlterada +=0.1f;
    if (key == GLUT_KEY_DOWN)
        if (escalaAlterada - 0.1f > -0.3)
            escalaAlterada -=0.1f;

	glutPostRedisplay();
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

	// Exibe mensagem que avisa como interagir
	printf(" Setas para esquerda e para direita movimentam a base (vermelha)");
	printf("\n Home e End rotacionam o braco 1 (verde)");
	printf("\n PageUP e PageDn rotacionam o braco 2 (azul)");
}

// Programa Principal
int main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(5,5);
	glutInitWindowSize(450,300);
	glutCreateWindow("Desenho de objeto modelado com transformações hierárquicas");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a função responsável por fazer as inicializações
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}

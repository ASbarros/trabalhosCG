//*****************************************************
//
// CasaComTransRotEsc.cpp
// Um programa OpenGL simples que abre uma janela GLUT,
// translada, rotaciona e troca a escala de um casa para
// depois desenha-la.
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro
// "OpenGL - Uma Abordagem Prática e Objetiva"
//
//*****************************************************

#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
GLfloat  zom, pamX,pamY ;
GLsizei largura, altura;
void quadrado()
{
    glBegin(GL_QUADS);
    glVertex2f(-10.0f,-10.0f);
    glVertex2f(-10.0f,  0.0f);
    glVertex2f( 10.0f,  0.0f);
    glVertex2f( 10.0f,-10.0f);
    glEnd();
}
// Função callback de redesenho da janela de visualização
void Desenha(void)
{

    glMatrixMode(GL_MODELVIEW);

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 0.0f);
    quadrado();
    glColor3f(1.0f, 0.0f, 0.0f);

    glPushMatrix();
    glTranslated(-35, 0, 0);
    quadrado();
    glPopMatrix();

    glColor3f(0.0f, 1.0f, 0.0f);

    glPushMatrix();
    glTranslatef(35,0,0);
    quadrado();
    glPopMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);


    glPushMatrix();
    glTranslatef(0,-35,0);
    quadrado();
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 0.0f);

    glPushMatrix();
    glTranslatef(0,0,35);
    quadrado();
    glPopMatrix();

    glColor3f(1.0f, 0.0f, 1.0f);

    glPushMatrix();
    glTranslatef(0,0,-35);
    quadrado();
    glPopMatrix();
    glColor3f(0.0f, 1.0f, 1.0f);


    glPushMatrix();
    glTranslatef(0,80,0);
    quadrado();
    glPopMatrix();

    glColor3f(0.5f, 0.5f, 0.5f);


    glPushMatrix();
    glTranslatef(0,-80,0);
    quadrado();
    glPopMatrix();

    glColor3f(0.3f, 0.9f, 0.4f);

    glPushMatrix();
    glTranslatef(80,0,0);
    quadrado();
    glPopMatrix();

    glColor3f(7.0f, 1.0f, 0.1f);

    glPushMatrix();
    glTranslatef(-80,0,0);
    quadrado();
    glPopMatrix();
    glColor3f(0.2f, 0.8f, 0.8f);


    glPushMatrix();
    glTranslatef(0,45,0);
    quadrado();
    glPopMatrix();
    glColor3f(0.9f, 1.0f, 0.4f);

    glPushMatrix();
    glTranslatef(40,45,0);
    quadrado();
    glPopMatrix();
    glColor3f(0.2f, 0.5f, 0.8f);

    glPushMatrix();
    glTranslatef(40,-45,0);
    quadrado();
    glPopMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);

    glPushMatrix();
    glTranslatef(-40,45,0);
    quadrado();
    glPopMatrix();
    glColor3f(0.6f, 0.6f, 0.6f);

    glPushMatrix();
    glTranslatef(-40,-45,0);
    quadrado();
    glPopMatrix();


    // Executa os comandos OpenGL
    glFlush();
}


// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{

    // Evita a divisao por zero
    if(h == 0)
        h = 1;

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
        gluOrtho2D (-100.0f + pamX+ zom, 100.0f+pamX- zom, -100.0f*altura/largura  + zom+pamY,  100.0f*altura/largura  - zom +pamY);
    else
        gluOrtho2D ((-100.0f*largura/altura)  + pamX+ zom, (100.0f*largura/altura)+pamX - zom, -100.0f+ zom+pamY, 100.0f- zom  +pamY  );

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
    zom = 0;
    pamX = 0;
    pamY = 0;
}

void TeclasEspeciais(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_PAGE_UP:
        zom +=10;
        break;
    case GLUT_KEY_PAGE_DOWN:
        zom -=10;
        break;
    case GLUT_KEY_RIGHT:
        pamX +=10;
        break;
    case GLUT_KEY_LEFT:
        pamX -= 10;
        break;
    case GLUT_KEY_DOWN:
        pamY +=10;
        break;
    case GLUT_KEY_UP:
        pamY -=10;
        break;

    }
    AlteraTamanhoJanela( largura, altura);
    Desenha();
}

// Programa Principal
int main(void)
{

    // Define do modo de operação da GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Especifica a posição inicial da janela GLUT
    glutInitWindowPosition(5,5);

    // Especifica o tamanho inicial em pixels da janela GLUT
    glutInitWindowSize(450,450);

    // Cria a janela passando como argumento o título da mesma
    glutCreateWindow("Desenho de uma casa com translação, rotação e escala");

    // Registra a função callback de redesenho da janela de visualização
    glutDisplayFunc(Desenha);


    // Registra a função callback de redimensionamento da janela de visualização
    glutReshapeFunc(AlteraTamanhoJanela);

    glutSpecialFunc(TeclasEspeciais);

    // Registra a função callback para tratamento das teclas ASCII
    glutKeyboardFunc (Teclado);


    // Chama a função responsável por fazer as inicializações
    Inicializa();

    // Inicia o processamento e aguarda interações do usuário
    glutMainLoop();

    return 0;
}

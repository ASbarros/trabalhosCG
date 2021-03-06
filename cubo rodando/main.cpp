//*****************************************************
//
// Exemplo3D.cpp
// Um programa OpenGL simples que abre uma janela GLUT
// e desenha um cubo para exemplificar a visualiza��o
// de objetos 3D utilizando a proje��o perspectiva.
//
// Marcelo Cohen e Isabel H. Manssour
// Este c�digo acompanha o livro
// "OpenGL - Uma Abordagem Pr�tica e Objetiva"
//
//*****************************************************

#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>



GLfloat fAspect;
GLfloat obsx,obsy,obsz;

void CuboColorido(GLfloat tam)
{

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    tam /= 2;

    glBegin(GL_QUADS);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f( tam, tam,-tam);
    glVertex3f(-tam, tam,-tam);
    glVertex3f(-tam, tam, tam);
    glVertex3f( tam, tam, tam);

    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f( tam,-tam, tam);
    glVertex3f(-tam,-tam, tam);
    glVertex3f(-tam,-tam,-tam);
    glVertex3f( tam,-tam,-tam);

    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f( tam, tam, tam);
    glVertex3f(-tam, tam, tam);
    glVertex3f(-tam,-tam, tam);
    glVertex3f( tam,-tam, tam);

    glColor3f(1.0f,1.0f,0.0f);
    glVertex3f( tam,-tam,-tam);
    glVertex3f(-tam,-tam,-tam);
    glVertex3f(-tam, tam,-tam);
    glVertex3f( tam, tam,-tam);

    glColor3f(1.0f,0.0f,1.0f);
    glVertex3f(-tam, tam, tam);
    glVertex3f(-tam, tam,-tam);
    glVertex3f(-tam,-tam,-tam);
    glVertex3f(-tam,-tam, tam);

    glColor3f(0.0f,1.0f,1.0f);
    glVertex3f( tam, tam,-tam);
    glVertex3f( tam, tam, tam);
    glVertex3f( tam,-tam, tam);
    glVertex3f( tam,-tam,-tam);

    glEnd();
}

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
    // Limpa a janela de visualiza��o com a cor
    // de fundo definida previamente
    glClear(GL_COLOR_BUFFER_BIT);


    CuboColorido(30);

    // Executa os comandos OpenGL
    glFlush();
}


// Fun��o usada para especificar o volume de visualiza��o
void EspecificaParametrosVisualizacao(void)
{
    // Especifica sistema de coordenadas de proje��o
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de proje��o
    glLoadIdentity();

    // Especifica a proje��o perspectiva(angulo,aspecto,zMin,zMax)
    gluPerspective(50,fAspect, 0.5, 200);

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();

    // Especifica posi��o do observador e do alvo
    gluLookAt(obsx, obsy, obsz, 0, 0, 0, 0, 1, 0);
}

// Fun��o callback chamada quando o tamanho da janela � alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Para previnir uma divis�o por zero
    if ( h == 0 )
        h = 1;

    // Especifica as dimens�es da viewport
    glViewport(0, 0, w, h);

    // Calcula a corre��o de aspecto
    fAspect = (GLfloat)w/(GLfloat)h;

    EspecificaParametrosVisualizacao();
}

void TeclasEspeciais(int key,int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_RIGHT:
        obsx++;
        Desenha();
        break;
    case GLUT_KEY_LEFT:
        obsx -= 10;
        Desenha();
        break;
    case GLUT_KEY_UP:
        obsy+=1;
        Desenha();
        break;
    case GLUT_KEY_DOWN:
        obsy--;
        Desenha();
        break;
    case GLUT_KEY_HOME:
        obsz--;
        Desenha();
        break;
    case GLUT_KEY_END:
        obsz++;
        Desenha();
        break;
    }
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
    obsx=20;
    obsy=40;
    obsz=100;
    // Define a cor de fundo da janela de visualiza��o como branca
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glLineWidth(2.0);
}

// Programa Principal
int main(void)
{
    // Define do modo de opera��o da GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Especifica a posi��o inicial da janela GLUT
    glutInitWindowPosition(5,5);

    // Especifica o tamanho inicial em pixels da janela GLUT
    glutInitWindowSize(450,450);

    // Cria a janela passando como argumento o t�tulo da mesma
    glutCreateWindow("Desenho de um cubo");

    // Registra a fun��o callback de redesenho da janela de visualiza��o
    glutDisplayFunc(Desenha);

    // Registra a fun��o callback de redimensionamento da janela de visualiza��o
    glutReshapeFunc(AlteraTamanhoJanela);

    // Registra a fun��o callback para tratamento das teclas ASCII
    glutKeyboardFunc (Teclado);

    // Chama a fun��o respons�vel por fazer as inicializa��es
    Inicializa();

    // registrando a funcao para as teclas especias
    glutSpecialFunc(TeclasEspeciais);

    // Inicia o processamento e aguarda intera��es do usu�rio
    glutMainLoop();

    return 0;
}

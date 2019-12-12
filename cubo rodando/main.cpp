//*****************************************************
//
// Exemplo3D.cpp
// Um programa OpenGL simples que abre uma janela GLUT
// e desenha um cubo para exemplificar a visualização
// de objetos 3D utilizando a projeção perspectiva.
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro
// "OpenGL - Uma Abordagem Prática e Objetiva"
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

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
    // Limpa a janela de visualização com a cor
    // de fundo definida previamente
    glClear(GL_COLOR_BUFFER_BIT);


    CuboColorido(30);

    // Executa os comandos OpenGL
    glFlush();
}


// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();

    // Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
    gluPerspective(50,fAspect, 0.5, 200);

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();

    // Especifica posição do observador e do alvo
    gluLookAt(obsx, obsy, obsz, 0, 0, 0, 0, 1, 0);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Para previnir uma divisão por zero
    if ( h == 0 )
        h = 1;

    // Especifica as dimensões da viewport
    glViewport(0, 0, w, h);

    // Calcula a correção de aspecto
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

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{
    obsx=20;
    obsy=40;
    obsz=100;
    // Define a cor de fundo da janela de visualização como branca
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glLineWidth(2.0);
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
    glutCreateWindow("Desenho de um cubo");

    // Registra a função callback de redesenho da janela de visualização
    glutDisplayFunc(Desenha);

    // Registra a função callback de redimensionamento da janela de visualização
    glutReshapeFunc(AlteraTamanhoJanela);

    // Registra a função callback para tratamento das teclas ASCII
    glutKeyboardFunc (Teclado);

    // Chama a função responsável por fazer as inicializações
    Inicializa();

    // registrando a funcao para as teclas especias
    glutSpecialFunc(TeclasEspeciais);

    // Inicia o processamento e aguarda interações do usuário
    glutMainLoop();

    return 0;
}

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
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

GLfloat fAspect;
float cameraX = 20,
      cameraY = 40,
      cameraZ = 100,
      tela = 1,
      fim = 0,
      inicio = 0;

GLsizei largura = 0,altura = 0;
GLfloat angulo;
// Variáveis que guardam a translação que será aplicada
// sobre a casinha
GLfloat Tx;
GLfloat Ty;

// Variáveis que guardam os valores mínimos de x e y da
// casinha
GLfloat minX, maxX;
GLfloat minY, maxY;

// Variáveis que guardam o tamanho do incremento nas
// direções x e y (número de pixels para se mover a
// cada intervalo de tempo)
GLfloat xStep;
GLfloat yStep;

// Variáveis que guardam a largura e altura da janela
GLfloat windowXmin, windowXmax;
GLfloat windowYmin, windowYmax;

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

    // Altera a cor do desenho para preto

    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glRotatef(angulo, 0,1,0);
    glTranslatef(Tx, Ty, 0.0f);
    // Função da GLUT para fazer o desenho de um cubo
    // com a cor corrente
    //glutWireCube(50);
    CuboColorido(30);
    glPopMatrix();

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

    if(tela == 0)
    {
        // Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
        gluPerspective(80, fAspect, 0.5+inicio, fim);
    }
    else
    {
        if (largura <= altura)
        {
            glOrtho (-60.0f, 60.0f, -60.0f*altura/largura, 60.0f*altura/largura,  0.5+inicio, 200+fim);
            windowXmin = -60.0f;
            windowXmax =  60.0f;
            windowYmin = -60.0f*altura/largura;
            windowYmax =  60.0f*altura/largura;
        }
        else
        {
            glOrtho (-60.0f*largura/altura, 60.0f*largura/altura, -60.0f, 60.0f,  0.5+inicio, 200+fim);
            windowXmin = -60.0f*largura/altura;
            windowXmax =  60.0f*largura/altura;
            windowYmin = -60.0f;
            windowYmax =  60.0f;
        }

    }

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();

    // Especifica posição do observador e do alvo
    gluLookAt(cameraX,cameraY,cameraZ, 0,0,0, 0,1,0);

    Desenha();

}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Para previnir uma divisão por zero
    if ( h == 0 )
        h = 1;

    altura = h;
    largura = w;
    // Especifica as dimensões da viewport
    glViewport(0, 0, w, h);

    // Calcula a correção de aspecto
    fAspect = (GLfloat)w/(GLfloat)h;

    EspecificaParametrosVisualizacao();
}

void Anima(int value)
{

    if( (Tx+maxX+xStep) > windowXmax || (Tx+minX+xStep) < windowXmin )
        xStep = -xStep;

    // Muda a direção quando chega na borda superior ou inferior
    if( (Ty+maxY+yStep) > windowYmax || (Ty+minY+yStep) < windowYmin )
        yStep = -yStep;

    // Move a casinha
    Tx += xStep;
    Ty += yStep;



    // Muda o angulo de rotação, e se chegar a 360, passa para zero
    angulo+=0.7;
    if( angulo >= 360.0 )
        angulo = 0.0f;

    // Redesenha o "teapot" em outra posição
    glutPostRedisplay();
    glutTimerFunc(41,Anima, 1);

}

void TeclasEspeciais(int key, int x, int y)
{


    switch (key)
    {
    case GLUT_KEY_UP:
        glRotatef(10, 0, 0, 1);
        break;
    case GLUT_KEY_DOWN:
        glRotatef(-10, 0, 0, 1);
        break;
    case GLUT_KEY_LEFT:
        glRotatef(-10, 0,1,0);
        break;
    case GLUT_KEY_RIGHT:
        glRotatef(10, 0, 1, 0);
        break;
    case GLUT_KEY_HOME:
        glRotatef(-10, 1, 0, 0);
        break;
    case GLUT_KEY_END:
        glRotatef(10, 1, 0, 0);
        break;
    case GLUT_KEY_F1:
        if(inicio > 1)
            inicio -= 10;
        EspecificaParametrosVisualizacao();
        break;
    case GLUT_KEY_F2:
        inicio += 10;
        EspecificaParametrosVisualizacao();
        break;
    case GLUT_KEY_F3:
        fim -=10;
        EspecificaParametrosVisualizacao();
        break;
    case GLUT_KEY_F4:
        fim +=10;
        EspecificaParametrosVisualizacao();
        break;
    }

    Desenha();
}


// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{

    switch(key)
    {
    case 27:
        exit(0);
        break;
    case 119: ///w
        cameraY +=1;
        EspecificaParametrosVisualizacao();
        break;
    case 115:  /// s
        cameraY -=1;
        EspecificaParametrosVisualizacao();
        break;
    case 97:  /// a
        cameraX -=1;
        EspecificaParametrosVisualizacao();
        break;
    case 100:  /// d
        cameraX +=1;
        EspecificaParametrosVisualizacao();
        break;
    case 113:  /// q
        cameraZ -=1;
        EspecificaParametrosVisualizacao();
        break;
    case 101:  /// e
        cameraZ +=1;
        EspecificaParametrosVisualizacao();
        break;
    case 120: /// prespectiva z
        tela = 0;
        EspecificaParametrosVisualizacao();
        break;
    case 122: /// ortografica x
        tela = 1;
        EspecificaParametrosVisualizacao();
        break;
    case 32:
        break;
    }

    Desenha();

}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{
    // Define a cor de fundo da janela de visualização como branca
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glLineWidth(2.0);
    angulo = 0.0f;

    xStep = yStep = 1.5f;
	Tx = Ty = 0.0f;
	minX = -30.0f;
	maxX =  30.0f;
	minY = -30.0f;
	maxY =  32.0f;
	windowXmin = windowYmin = -60.0f;
	windowXmax = windowYmax = 60.0f;
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


    // Registra a função callback para tratamento das teclas especiais
    glutSpecialFunc(TeclasEspeciais);

    // Registra a função callback de redesenho da janela de visualização
    glutDisplayFunc(Desenha);

    // Registra a função callback de redimensionamento da janela de visualização
    glutReshapeFunc(AlteraTamanhoJanela);

    glutTimerFunc(41, Anima, 1);

    // Registra a função callback para tratamento das teclas ASCII
    glutKeyboardFunc (Teclado);

    // Chama a função responsável por fazer as inicializações
    Inicializa();

    // Inicia o processamento e aguarda interações do usuário
    glutMainLoop();

    return 0;
}

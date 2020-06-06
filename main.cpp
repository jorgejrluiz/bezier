#include <iostream>
#include <GL/gl.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include<windows.h>
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>
#include <cmath>

/**************************************************************************************/
class Point;
void desenha(void);
Point *bezier(Point *p0, Point *p1, Point *p2, Point *p3, double t, Point *pFinal);
double interpolate(Point *f[], int xi, int n);
Point *hermite(Point *p0, Point *p1, Point *v0, Point *v1, double u, Point *pFinal);
int escolherPonto(int x, int y);
void MenuCor(int op);
void MenuCurvas(int op);
void MenuPrincipal(int op);
void CriaMenu();
void mouse(int botao, int estado, int mousex, int mousey);
void desenha(void);

GLfloat r, g, b;
int tipo_curva = -1;

/**************************************************************************************/

/**
*Classe que representa os pontos no grid
*/

class Point
{
public:
    double x;

public:
    double y;

public:
    /**
    * Construtor classe Point
    * @param  x  inteiro que representa a cordenada x
    * @param  y  inteiro que representa a cordenada y
    */
    Point(double x1, double y1)
    {
        x = x1;
        y = y1;
    }
};

Point *p0 = new Point(100, 200);
Point *p1 = new Point(250, 400);
Point *p2 = new Point(400, 400);
Point *p3 = new Point(550, 200);
Point *pFinal = new Point(100, 300);

/**
* Implementacao do algoritmo de Bezier que retorna o ponteiro pra classe ponto,
* que eh calculado pela expressao da curva de bezier
*
* @param  p0  ponteiro que representa o ponto 0
* @param  p1  ponteiro que representa o ponto 1
* @param  p2  ponteiro que representa o ponto 2
* @param  p3  ponteiro que representa o ponto 3
* @param  t valor double que representa
* @return      coordenadas do novo ponto
*/

// Implementação do algoritmo de Bezier para expressar uma curva
Point *bezier(Point *p0, Point *p1, Point *p2, Point *p3, double t)
{
    // Cálculo da coordenada x
    double x = pow(1 - t, 3) * p0->x +
               pow(1 - t, 2) * 3 * t * p1->x +
               (1 - t) * 3 * t * t * p2->x +
               t * t * t * p3->x;

    // Cálculo da coordenada y
    double y = pow(1 - t, 3) * p0->y +
               pow(1 - t, 2) * 3 * t * p1->y +
               (1 - t) * 3 * t * t * p2->y +
               t * t * t * p3->y;

    // Retorna o novo ponto
    return new Point(x, y);
}

/**
* Metodo de interpolacao
*
* @param  f  vetor de ponteiros
* @param  xi  inteiro
* @param  n  inteiro
* @return resultado da interpolacao
*/
double interpolate(Point *f[], int xi, int n)
{
    double result = 0; // Inicialia a variável de resultado

    for (int i = 0; i < n; i++)
    {
        // Computa termos individuais
        double term = f[i]->y;
        for (int j = 0; j < n; j++)
        {
            if (j != i)
            {
                term = term * (xi - f[j]->x) / double(f[i]->x - f[j]->x);
            }
        }
        // Adiciona o termo atual a variável resultado
        result += term;
    }
    return result;
}

/**
* Implementacao do algoritmo de Hermite que retorna o ponteiro pra classe ponto,
* que eh calculado pela expressao da curva de Hermite
*
* @param  p0  ponteiro que representa o ponto 0
* @param  p1  ponteiro que representa o ponto 1
* @param  v0  ponteiro que representa o ponto 2
* @param  v1  ponteiro que representa o ponto 3
* @param  u valor double que representa
* @return coordenadas do novo ponto
*/

// Implementação do algoritmo de Hermite para expressar uma curva
Point *hermite(Point *p0, Point *p1, Point *v0, Point *v1, double u)
{

    // Cálculo da coordenada x
    double x = p0->x * (2 * pow(u, 3) - 3 * pow(u, 2) + 1) + p1->x * (-2 * pow(u, 3) + 3 * pow(u, 2)) +
               v0->x * (pow(u, 3) - 2 * pow(u, 2) + u) + v1->x * (pow(u, 3) - pow(u, 2));

    // Cálculo da coordenada y
    double y = p0->y * (2 * pow(u, 3) - 3 * pow(u, 2) + 1) + p1->y * (-2 * pow(u, 3) + 3 * pow(u, 2)) +
               v0->y * (pow(u, 3) - 2 * pow(u, 2) + u) + v1->y * (pow(u, 3) - pow(u, 2));

    // Retorna o novo ponto
    return new Point(x, y);
}

/**
* Metodo para escolher ponto com base na distancia entre os pontos
* @param  x  inteiro que representa a cordenada x
* @param  y  inteiro que representa a cordenada y
* @return ponto a ser utilizado
*/
int escolherPonto(int x, int y)
{
    int distancia1, distancia2, distancia3, distancia4;
    distancia1 = sqrt(((x - p0->x) * (x - p0->x)) + ((y - p0->y) * (y - p0->y)));
    distancia2 = sqrt(((x - p1->x) * (x - p1->x)) + ((y - p1->y) * (y - p1->y)));
    distancia3 = sqrt(((x - p2->x) * (x - p2->x)) + ((y - p2->y) * (y - p2->y)));
    distancia4 = sqrt(((x - p3->x) * (x - p3->x)) + ((y - p3->y) * (y - p3->y)));

    if (distancia1 < distancia2)
    {
        if (distancia1 < distancia3)
        {
            if (distancia1 < distancia4)
                return 1;
            else
                return 4;
        }
        else
        {
            if (distancia3 < distancia4)
                return 3;
            else
                return 4;
        }
    }
    else
    {
        if (distancia2 < distancia3)
        {
            if (distancia2 < distancia4)
                return 2;
            else
                return 4;
        }
        else
        {
            if (distancia3 < distancia4)
                return 3;
            else
                return 4;
        }
    }
}

// Gerenciamento do menu com as opções de cores
void MenuCor(int op)
{
    switch (op)
    {
    case 0: //preto
        r = 0.0f;
        g = 0.0f;
        b = 0.0f;
        break;
    case 1: //verde
        r = 0.0f;
        g = 1.0f;
        b = 0.0f;
        break;
    case 2: //azul
        r = 0.0f;
        g = 0.0f;
        b = 1.0f;
        break;
    }
    glutPostRedisplay();
}

// Gerenciamento do menu de curvas parametricas
void MenuCurvas(int op)
{
    switch (op)
    {
    case 0:
        //Interpolada
        tipo_curva = 0;
        glutDisplayFunc(desenha);
        break;
    case 1:
        //Hermite
        tipo_curva = 1;
        glutDisplayFunc(desenha);
        break;
    case 2:
        //Bezier
        tipo_curva = 2;
        glutDisplayFunc(desenha);
        break;
    }
    glutPostRedisplay();
}

// Gerenciamento do menu principal
void MenuPrincipal(int op) {}

// Criacao do Menu
void CriaMenu()
{
    int menu, submenu1, submenu2;
    submenu1 = glutCreateMenu(MenuCor);
    glutAddMenuEntry("Preto", 0);
    glutAddMenuEntry("Verde", 1);
    glutAddMenuEntry("Azul", 2);

    submenu2 = glutCreateMenu(MenuCurvas);
    glutAddMenuEntry("Interpolada", 0);
    glutAddMenuEntry("Hermite", 1);
    glutAddMenuEntry("Bezier", 2);

    menu = glutCreateMenu(MenuPrincipal);
    glutAddSubMenu("tipo de curva", submenu2);
    glutAddSubMenu("Cor", submenu1);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/**
* Metodo para identificar posicao do mouse de acordo com o clique do botao esquerdo
* @param  botao  inteiro que representa qual botao do mouse foi apertado
* @param  estado  inteiro que representa estado do mouse
* @param  mousex  inteiro que representa posicao do cursor no eixo X
* @param  mousey  inteiro que representa posicao do cursor no eixo y
*/

void mouse(int botao, int estado, int mousex, int mousey)
{
    if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
    {
        int ponto = escolherPonto(mousex, 600 - mousey);
        switch (ponto)
        {
        case 1:
            p0->x = mousex;
            p0->y = 600 - mousey;
            break;
        case 2:
            p1->x = mousex;
            glEnd();
            p1->y = 600 - mousey;
            break;
        case 3:
            p2->x = mousex;
            p2->y = 600 - mousey;
            break;
        case 4:
            p3->x = mousex;
            p3->y = 600 - mousey;
            break;
        }
        glutPostRedisplay();
    }

    if (botao == GLUT_RIGHT_BUTTON)
        if (estado == GLUT_DOWN)
            CriaMenu();
    glutPostRedisplay();
}

void desenha(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //std::cout << pFinal->x;
    Point *f[] = {p0, p1, p2, p3};
    pFinal = new Point(p0->x, interpolate(f, p0->x, 4));
    glPointSize(5);

    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f); // muda a cor do ponto
    glVertex2f(p0->x, p0->y);
    glVertex2f(p1->x, p1->y);
    glVertex2f(p2->x, p2->y);
    glVertex2f(p3->x, p3->y);
    glEnd();
    glPointSize(2);

    if (tipo_curva == 0)
    { //CURVA INTERPOLADA
        for (double i = p0->x + 1; i < p3->x; i = i + 1)
        {
            glBegin(GL_POINTS);
            glColor3f(r, g, b);
            glVertex2f(pFinal->x, pFinal->y);
            pFinal = new Point(i, interpolate(f, i, 4));
            //std::cout << pFinal->x << "\t" << pFinal->y << "\n";
            glVertex2f(pFinal->x, pFinal->y);
            glEnd();
        }
    }
    else if (tipo_curva == 1)
    { //CURVA DE HERMITE
        for (double i = 0; i < 1.0; i += 0.01)
        {
            glBegin(GL_LINES);
            glColor3f(r, g, b);
            glVertex2f(pFinal->x, pFinal->y);
            pFinal = hermite(p0, p1, p2, p3, i);
            //std::cout << pFinal->x;
            glVertex2f(pFinal->x, pFinal->y);
            glEnd();
        }
    }
    else if (tipo_curva == 2)
    { //CURVA DE BEZIER
        for (double i = 0.01; i < 1; i = i + 0.01)
        {
            glBegin(GL_LINES);
            glColor3f(r, g, b);
            glVertex2f(pFinal->x, pFinal->y);
            pFinal = bezier(p0, p1, p2, p3, i);
            //std::cout << pFinal->x;
            glVertex2f(pFinal->x, pFinal->y);
            glEnd();
        }
    }
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("GRAPH TOOL - COMPUTACAO GRAFICA");
    glClearColor(1, 1, 1, 0); // cor do fundo GLfloat [red, green, blue, alpha]
    glClear(GL_COLOR_BUFFER_BIT);
    glutMouseFunc(mouse);
    glutMainLoop();
}

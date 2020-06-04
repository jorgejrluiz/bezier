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

/**
*Classe que representa os pontos no grid
*/

class Point {
    public: double x;
    public: double y;

    public:
    /**
    * Construtor classe Point
    * @param  x  inteiro que representa a cordenada x
    * @param  y  inteiro que representa a cordenada y
    */
    Point(double x1,double y1) {
        x = x1;
        y = y1;
    }
};

Point* p0 = new Point(100,200);
Point* p1 = new Point(250,400);
Point* p2 = new Point(400,400);
Point* p3 = new Point(550,200);
Point* pFinal = new Point(100,300);
bool mouseRight = true;

/**
* Implementacao do algoritmo de Bezier que retorna o ponteiro pra classe ponto,
* que eh calculado pela expressao da curva de bezier
*
* @param  p0  ponteiro que representa o ponto 0
* @param  p1  ponteiro que representa o ponto 1
* @param  p2  ponteiro que representa o ponto 2
* @param  p3  ponteiro que representa o ponto 3
* @param  t valor double que representa
* @param  pFinal  ponteiro que armazena o ponto final
* @return      coordenadas do novo ponto
*/

// Implementação do algoritmo de Bezier para expressar uma curva
Point* bezier(Point* p0, Point* p1, Point* p2, Point* p3,double t, Point* pFinal) {
    // Cálculo da coordenada x
    double x = pow(1-t,3) * p0->x +
               pow(1-t,2) * 3 * t * p1->x +
               (1-t) * 3 * t * t * p2->x +
               t * t * t * p3->x;

    // Cálculo da coordenada y
    double y = pow(1-t,3) * p0->y +
               pow(1-t,2) * 3 * t * p1->y +
               (1-t) * 3 * t * t * p2->y +
               t * t * t * p3->y;

    // Retorna o novo ponto
    return new Point(x,y);
}

/**
* Metodo de interpolacao
*
* @param  f  vetor de ponteiros
* @param  xi  inteiro
* @param  n  inteiro
* @return resultado da interpolacao
*/
double interpolate(Point* f[], int xi, int n) {
    double result = 0; // Inicialia a variável de resultado

    for (int i = 0; i < n; i++) {
        // Computa termos individuais
        double term = f[i]->y;
        for (int j=0 ;j < n; j++) {
            if (j!=i) {
                term = term*(xi - f[j]->x)/double(f[i]->x - f[j]->x);
            }
        }
        // Adiciona o termo atual a variável resultado
        result += term;
    }
    return result;
}

/**
* Metodo para escolher ponto com base na distancia entre os pontos
* @param  x  inteiro que representa a cordenada x
* @param  y  inteiro que representa a cordenada y
* @return ponto a ser utilizado
*/
int escolherPonto(int x,int y)
{
    int distancia1,distancia2,distancia3,distancia4;
    distancia1=sqrt(((x - p0->x)*(x - p0->x))+((y - p0->y)*(y - p0->y)));
    distancia2=sqrt(((x - p1->x)*(x - p1->x))+((y - p1->y)*(y - p1->y)));
    distancia3=sqrt(((x - p2->x)*(x - p2->x))+((y - p2->y)*(y - p2->y)));
    distancia4=sqrt(((x - p3->x)*(x - p3->x))+((y - p3->y)*(y - p3->y)));

    if(distancia1 < distancia2)
    {
        if(distancia1 < distancia3)
        {
            if(distancia1 < distancia4)
                return 1;
            else
                return 4;
        }
        else
        {
            if(distancia3 < distancia4)
                return 3;
            else
                return 4;
        }
    }
    else
    {
        if(distancia2 < distancia3)
        {
            if(distancia2 < distancia4)
                return 2;
            else
                return 4;
        }
        else
        {
            if(distancia3 < distancia4)
                return 3;
            else
                return 4;
        }
    }

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

    if(botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
    {
        int ponto = escolherPonto(mousex, 600-mousey);
        switch(ponto)
        {
        case 1:
            p0->x = mousex;
            p0->y = 600 - mousey;
            break;
        case 2:
            p1->x = mousex;glEnd();
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
    else if(botao == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN)
    {
        mouseRight = !mouseRight;
    }

}


int main(int argc, char *argv[]) {
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(10,10);
    glutCreateWindow("GRAPH TOOL - COMPUTACAO GRAFICA");
    glClearColor(0,0,1,0);
    glClear(GL_COLOR_BUFFER_BIT);

    glutDisplayFunc(desenha);
    glutMouseFunc(mouse);
    glutMainLoop();
}

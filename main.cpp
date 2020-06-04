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

class Point {
public: double x;
public: double y;

public:
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

// Implementação do algoritmo de Bézier para expressar uma curva
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


// Método de interpolação
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

int main(int argc, char *argv[]) {
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(10,10);
    glutCreateWindow("GRAPH TOOL - COMPUTAÇÃO GRÁFICA");
    glClearColor(0,0,1,0);
    glClear(GL_COLOR_BUFFER_BIT);

    glutDisplayFunc(desenha);
    glutMouseFunc(mouse);
    glutMainLoop();
}

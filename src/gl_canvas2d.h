/*
 * - Adicionado a estrutura colors_enum para dar nome as cores
 *
 * - Vector2  current_translate: Armazena a translação atual
 * - void relativeTranslate(Vector2  t): Aplica uma translação a partir da translacao atual,
 * isto é, current_translate += t; translate(current_translate)
 * - Vector2  mouse_pos e get_mouse_pos(): posição atual do mouse e respectivo getter.
 * - Vector2  mouse_displacement e get_mouse_displacement(): deslocamento atual do mouse e
 * respectivo getter.
 *
 * - static std::vector<Renderizable *> render_stack: Array de ponteiros para objetos renderizaveis
 * - CV_render():
 * Antiga função render. Percorre o vetor render_stack e para cada objeto renderizável chama a
 * função render_caller()
 *
 * - As callbacks de eventos do mouse e teclado são passadas para métodos estáticos de EventListener
 *
 * */
#ifndef __CANVAS_2D__H__
#define __CANVAS_2D__H__

#include <string>
#include <vector>
#include <functional>

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include "Vector2.h"

#define PI_2 6.28318530717
#define PI   3.14159265359
#define PXL_STR 10.f //Pixels por String
#define PXL_STR_H 10.f //Pixels por String em altura
#define Y_CANVAS_CRESCE_PARA_CIMA 1

extern int screenWidth, screenHeight;


typedef enum {
    black,
    gray,
    red,
    green,
    blue,
    cyan,
    magenta,
    yellow,
    orange,
    brown,
    olive,
    idk_1,
    idk_2,
    white,
    n_of_colors
} colors_enum;


void ConvertMouseCoord(int button, int state, int wheel, int direction, int x, int y);


class Renderizable;

class CV //classe Canvas2D
{
    friend void ConvertMouseCoord(int,int,int,int,int,int);

public:
    static std::vector<Renderizable *> render_stack;
    //Posições do Mouse
    static Vector2  get_mouse_pos();
    static Vector2  get_mouse_displacement();

    //funcoes para desenho de ponto e linha
    static void point(float x, float y); //coordeandas do ponto
    static void point(Vector2  pos); //coordeandas do ponto

    static void line( float x1, float y1, float x2, float y2 ); //coordenadas da linha x1, y1, x2, y2
    static void line(Vector2  p1, Vector2  p2 ); //coordenadas da linha (p1, p2)


    //desenha um retangulo alinhado nos eixos x e y
    static void rect( float x1, float y1, float x2, float y2 ); //coordenadas do retangulo x1, y1, x2, y2
    static void rect( Vector2  p1, Vector2  p2 ); //coordenadas do retangulo (p1, p2) - TO DO

    static void rectFill( float x1, float y1, float x2, float y2 ); //coordenadas do retangulo x1, y1, x2, y2
    static void rectFill( Vector2  p1, Vector2  p2 ); //coordenadas do retangulo (p1, p2)
    static void rectFill( Vector2  p1); //coordenadas do retangulo (p1, p2)

    //desenha um poligono CONVEXO. Para um retangulo, deve-se passar 4 vertices
    static void polygon(float vx[], float vy[], int n_elems);
    static void polygon(std::vector<std::tuple<Vector2 , Vector2 >> edges);
    static void polygonFill(float vx[], float vy[], int n_elems);
    static void polygonFill(std::vector<std::tuple<Vector2 , Vector2 >> edges);
    //centro e raio do circulo
    static void circle( float x, float y, float radius, int div );
    static void circle( Vector2  pos, float radius, int div );

    static void circleFill( float x, float y, float radius, int div );
    static void circleFill( Vector2  pos, float radius, int div );

    //especifica a cor de desenho e de limpeza de tela
    static void color(float r, float g, float b);
    static void color(int r, int g, int b);
    static void color(float r, float g, float b, float alpha);
    static void color(colors_enum index);

    static void clear(float r, float g, float b);

    //desenha texto na coordenada (x,y)
    static void text(float x, float y, const char *t);
    static void text(Vector2  pos, const char *t);  //varias funcoes ainda nao tem implementacao. Faca como exercicio
    static void text(Vector2  pos, int valor);      //varias funcoes ainda nao tem implementacao. Faca como exercicio
    static void text(Vector2  pos, float valor);    //varias funcoes
    static void text(Vector2  pos, std::string valor);    //varias funcoes
    // ainda nao tem implementacao. Faca como exercicio

    //coordenada de offset para desenho de objetos.
    static void translate(float x, float y);
    static void translate(Vector2 pos);
    static void relative_translate(float x, float y);


    static void relative_translate(Vector2 pos);

    //funcao de inicializacao da Canvas2D. Recebe a largura, altura, e um titulo para a janela
    static void init(int w, int h, const char *title);

    //funcao para executar a Canvas2D
    static void run();

private:
    static Vector2  current_translate;
    static Vector2 mouse_pos;
    static Vector2 mouse_displacement;
};

void CV_render();



#endif

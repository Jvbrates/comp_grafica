/**
*   Programa para ilustrar os elementos mais basicos do OpenGL e Glut.
*   - Apresenta os principais recursos do sistema de Janelas GLUT
*
*   Autor: Cesar Tadeu Pozzer
*   UFSM - 2020
*
*   pozzer@inf.ufsm.br
*   pozzer3@gmail.com
*
* Referencias GLUT: http://www.opengl.org/documentation/specs/glut/
*                   http://www.opengl.org/documentation/specs/glut/spec3/node1.html
**/


#include "gl_canvas2d.h"
#include "EventListener.h"
#include "cstring"
//#include <GL/glut.h>
std::vector<Renderizable * > CV::render_stack =
        std::vector<Renderizable *>();

//conjunto de cores predefinidas. Pode-se adicionar mais cores.
float Colors[14][3]=
{
    {0, 0, 0}, //Black
    {0.5, 0.5, 0.5}, //Gray
    {1, 0, 0}, //Red
    {0, 1, 0}, //Green
    {0, 0, 1}, //Blue
    {0, 1, 1}, //Cyan
    {1, 0, 1}, //Magenta
    {1, 1, 0}, //Yellow
    {1, 0.5, 0}, //Orange
    {0.5, 0, 0}, //Brown
    {0.5, 0.5, 0}, //Olive
    {0, 0.5, 0.5}, //
    {0.5, 0, 0.5}, //
    {1, 1, 1}, //white
};



//funcoes de CALLBACK da biblioteca Glut
void keyboard(int key);
void keyboardUp(int key);
void specialUp(int key);
void mouse(int bt, int st, int wheel, int direction, int x, int y);
void mouseWheelCB(int wheel, int direction, int x, int y);


Vector2<float> CV::mouse_pos {0,0};   // Jeito legal de declarar variável
Vector2<float> CV::mouse_displacement {0,0};
Vector2<float> CV::current_translate {0,0};


void CV::point(float x, float y)
{
   glBegin(GL_POINTS);
      glVertex2d(x, y);
   glEnd();
}

void CV::point(Vector2<float> p)
{
   glBegin(GL_POINTS);
      glVertex2d(p.x, p.y);
   glEnd();
}

void CV::line( float x1, float y1, float x2, float y2 )
{
   glBegin(GL_LINES);
      glVertex2d(x1, y1);
      glVertex2d(x2, y2);
   glEnd();
}


void CV::line(Vector2<float> p1, Vector2<float> p2) {
    glBegin(GL_LINES);
    glVertex2d(p1.x, p1.y);
    glVertex2d(p2.x, p2.y);
    glEnd();
}

void CV::rect( float x1, float y1, float x2, float y2 )
{
   glBegin(GL_LINE_LOOP);
      glVertex2d(x1, y1);
      glVertex2d(x1, y2);
      glVertex2d(x2, y2);
      glVertex2d(x2, y1);
   glEnd();
}

void CV::rectFill( float x1, float y1, float x2, float y2 )
{
   glBegin(GL_QUADS);
      glVertex2d(x1, y1);
      glVertex2d(x1, y2);
      glVertex2d(x2, y2);
      glVertex2d(x2, y1);
   glEnd();
}
void CV::rectFill( Vector2<float> p1, Vector2<float> p2 )
{
   glBegin(GL_QUADS);
      glVertex2d(p1.x, p1.y);
      glVertex2d(p1.x, p2.y);
      glVertex2d(p2.x, p2.y);
      glVertex2d(p2.x, p1.y);
   glEnd();
}

void CV::rectFill(Vector2<float> p2 )
{
    glBegin(GL_QUADS);
    glVertex2d(0, 0);
    glVertex2d(0, p2.y);
    glVertex2d(p2.x, p2.y);
    glVertex2d(p2.x, 0);
    glEnd();
}

void CV::polygon(float vx[], float vy[], int elems)
{
   int cont;
   glBegin(GL_LINE_LOOP);
      for(cont=0; cont<elems; cont++)
      {
         glVertex2d(vx[cont], vy[cont]);
      }
   glEnd();
}

void CV::polygonFill(float vx[], float vy[], int elems)
{
   int cont;
   glBegin(GL_POLYGON);
      for(cont=0; cont<elems; cont++)
      {
         glVertex2d(vx[cont], vy[cont]);
      }
   glEnd();

}


void CV::polygonFill(std::vector<std::tuple<Vector2<float>, Vector2<float>>> edges)
{
    glBegin(GL_POLYGON);
    for (const auto &item: edges)
    {
        glVertex2d(std::get<0>(item).x, std::get<0>(item).y);
    }
    glEnd();

}


void CV::polygon(std::vector<std::tuple<Vector2<float>, Vector2<float>>> edges)
{
    glBegin(GL_LINE_LOOP);
    for (const auto &item: edges)
    {
        glVertex2d(std::get<0>(item).x, std::get<0>(item).y);
    }
    glEnd();

}

//existem outras fontes de texto que podem ser usadas
//  GLUT_BITMAP_9_BY_15
//  GLUT_BITMAP_TIMES_ROMAN_10
//  etc. Para mais detalhes, acesse https://www.opengl.org/resources/libraries/glut/spec3/node76.html
//Vejam tambem a funcao glutStrokeWidth(GLUTstrokeFont font, int character)
//Para textos de qualidade, ver:
//  https://www.freetype.org/
//  http://ftgl.sourceforge.net/docs/html/ftgl-tutorial.html
void CV::text(float x, float y, const char *t)
{
    int tam = (int)strlen(t);
    for(int c=0; c < tam; c++)
    {
      glRasterPos2i(x + c*10, y);
      glutBitmapCharacter(GLUT_BITMAP_8_BY_13, t[c]);
    }
}

void CV::text(Vector2<float> pos, const char *t)
{
    int tam = (int)strlen(t);
    for(int c=0; c < tam; c++)
    {
        glRasterPos2i(pos.x + c*10, pos.y);
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, t[c]);
    }
}

void CV::clear(float r, float g, float b)
{
   glClearColor( r, g, b, 1 );
}

void CV::circle( float x, float y, float radius, int div )
{
   float ang = 0, x1, y1;
   float inc = PI_2/div;
   glBegin(GL_LINE_LOOP);
      for(int lado = 1; lado <= div; lado++) //GL_LINE_LOOP desenha um poligono fechado. Liga automaticamente o primeiro e ultimio vertices.
      {
         x1 = (cos(ang)*radius);
         y1 = (sin(ang)*radius);
         glVertex2d(x1+x, y1+y);
         ang+=inc;
      }
   glEnd();
}

void CV::circle( Vector2<float> pos, float radius, int div )
{
    float ang = 0, x1, y1;
    float inc = PI_2/div;
    glBegin(GL_LINE_LOOP);
    for(int lado = 1; lado <= div; lado++) //GL_LINE_LOOP desenha um poligono fechado. Liga automaticamente o primeiro e ultimio vertices.
    {
        x1 = (cos(ang)*radius);
        y1 = (sin(ang)*radius);
        glVertex2d(x1+pos.x, y1+pos.y);
        ang+=inc;
    }
    glEnd();
}


void CV::circleFill( float x, float y, float radius, int div )
{
    float ang = 0, x1, y1;
    float inc = PI_2/div;
    glBegin(GL_POLYGON);
    for(int lado = 1; lado <= div; lado++) //GL_POLYGON desenha um poligono CONVEXO preenchido.
    {
        x1 = (cos(ang)*radius);
        y1 = (sin(ang)*radius);
        glVertex2d(x1+x, y1+y);
        ang+=inc;
    }
    glEnd();
}

void CV::circleFill( Vector2<float> pos, float radius, int div )
{
   float ang = 0, x1, y1;
   float inc = PI_2/div;
   glBegin(GL_POLYGON);
      for(int lado = 1; lado <= div; lado++) //GL_POLYGON desenha um poligono CONVEXO preenchido.
      {
         x1 = (cos(ang)*radius);
         y1 = (sin(ang)*radius);
         glVertex2d(x1+pos.x, y1+pos.y);
         ang+=inc;
      }
   glEnd();
}



//coordenada de offset para desenho de objetos.
//nao armazena translacoes cumulativas.
void CV::translate(float offsetX, float offsetY)
{
    current_translate = {offsetX, offsetY};
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslated(offsetX, offsetY, 0);
}

void CV::relative_translate(float x_, float y_) {
    //TODO criar overload para +=
    current_translate = current_translate + Vector2<float>{x_,y_};
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(current_translate.x, current_translate.y, 0);
}

void CV::translate(Vector2<float> offset)
{
   current_translate = offset;
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslated(offset.x, offset.y, 0);
}

void CV::relative_translate(Vector2<float> move){
    current_translate = current_translate + move;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(current_translate.x, current_translate.y, 0);
}

void CV::color(float r, float g, float b)
{
   glColor3d(r, g, b);
}

void CV::color(int r, int g, int b)
{

    double f_r, f_g, f_b;

    f_r = ((double )r) / 255.;
    f_g = ((double )g) / 255.;
    f_b = ((double )b) / 255.;

    glColor3d(f_r,f_g,f_b);
}



void CV::color(colors_enum idx)
{
    glColor3fv(Colors[idx]);
}

void CV::color(float r, float g, float b, float alpha)
{
   glColor4d(r, g, b, alpha);
}

void special(int key, int , int )
{
   keyboard(key+100);
}

void specialUp(int key, int , int )
{
   keyboardUp(key+100);
}

void keyb(unsigned char key, int , int )
{
   keyboard(key);
}

void keybUp(unsigned char key, int , int )
{
   keyboardUp(key);
}

void mouseClick(int button, int state, int x, int y)
{
   ConvertMouseCoord(button, state, -2, -2, x, y);
}

void mouseWheelCB(int wheel, int direction, int x, int y)
{
   ConvertMouseCoord(-2, -2, wheel, direction, x, y);
}

void motion(int x, int y)
{
   ConvertMouseCoord(-2, -2, -2, -2, x, y);
}

void ConvertMouseCoord(int button, int state, int wheel, int direction, int x, int y)
{
#if Y_CANVAS_CRESCE_PARA_CIMA == TRUE
   y = screenHeight - y; //deve-se inverter a coordenada y do mouse se o y da canvas crescer para cima. O y do mouse sempre cresce para baixo.
#else
   //nao faz nada.
#endif

    CV::mouse_displacement = Vector2<float>(x,y) - CV::mouse_pos;
    CV::mouse_pos = Vector2<float>(x,y);
    CV::current_translate = Vector2<float>{0., 0.};

    mouse(button, state, wheel, direction, x, y);
}


//funcao chamada sempre que a tela for redimensionada.
void reshape (int w, int h)
{
   screenHeight = h; //atualiza as variaveis da main() com a nova dimensao da tela.
   screenWidth = w;

   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();

   //cria uma projecao ortografica com z entre (-1, 1).
#if Y_CANVAS_CRESCE_PARA_CIMA == TRUE
   //parametros: left, right, bottom, top
   gluOrtho2D (0.0, w, 0.0, h); //o eixo y cresce para cima.
#else
   //parametros: left, right, bottom, top
   gluOrtho2D (0.0, w, h, 0.0); //o eixo y cresce para baixo
#endif

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();
}

//definicao de valores para limpar buffers
void inicializa()
{
   glClearColor(1,1,1,1);
   glPolygonMode(GL_FRONT, GL_FILL);
}

void display (void)
{
   glClear(GL_COLOR_BUFFER_BIT );

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   CV_render();

   glFlush();
   glutSwapBuffers();
}


Vector2<float> CV::get_mouse_pos() {
    return CV::mouse_pos;
}

Vector2<float> CV::get_mouse_displacement() {
    return CV::mouse_displacement;
}


//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key)
{

    EventListener::key_press(key);

}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
    EventListener::key_up(key);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    if(button != -2) {        //Click
        if(button == GLUT_RIGHT_BUTTON){
            EventListener::mouse_right(state);
        } else if (button == GLUT_LEFT_BUTTON){
            EventListener::mouse_left(state);
        }

    } else if (wheel != -2) {  //Scroll
        EventListener::mouse_scroll(direction);
    }else { //Movimentação
        EventListener::mouse_move(CV::get_mouse_pos(),CV::get_mouse_displacement());
    }
}



////////////////////////////////////////////////////////////////////////////////////////
//  inicializa o OpenGL
////////////////////////////////////////////////////////////////////////////////////////
void CV::init(int w, int h, const char *title)
{
   int argc = 0;
   glutInit(&argc, NULL);

   screenHeight = h;
   screenWidth = w;

   //habilita MSAA
   glutSetOption(GLUT_MULTISAMPLE, 8);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
   //glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

   glutInitWindowSize (w, h);
   glutInitWindowPosition (50, 50);
   glutCreateWindow (title);

   inicializa();

   glutReshapeFunc(reshape);
   glutDisplayFunc(display);
   glutKeyboardFunc(keyb);
   glutKeyboardUpFunc(keybUp);
   glutSpecialUpFunc(specialUp);
   glutSpecialFunc(special);

   glutIdleFunc(display);
   glutMouseFunc(mouseClick);
   glutPassiveMotionFunc(motion);
   glutMotionFunc(motion);
   glutMouseWheelFunc(mouseWheelCB);

   printf("GL Version: %s", glGetString(GL_VERSION));
}

void CV::run()
{
   glutMainLoop();
}

void CV::text(Vector2<float> pos, std::string valor) {
    int tam = valor.size();
    for(int c=0; c < tam; c++)
    {
        glRasterPos2i(pos.x + c*10, pos.y);
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, valor[c]);
    }
}

void CV::rect(Vector2<float> p1, Vector2<float> p2) {

    float x1 = p1.x, x2 = p2.x, y1 = p1.y, y2 = p2.y;
    glBegin(GL_LINE_LOOP);
    glVertex2d(x1, y1);
    glVertex2d(x1, y2);
    glVertex2d(x2, y2);
    glVertex2d(x2, y1);
    glEnd();
}

/*
INSTRUÇÕES:
O programa inteiro é controlado por teclas:
SETA PARA CIMA/BAIXO: Move a câmera no eixo Z;
SETA PARA ESQUERDA/DIREOTA: Aumenta/Diminui RPM;
S/W: Rotaciona a câmera no eixo x;
A/D: Rotaciona a câmera no eixo y;
Q/E: Rotaciona a câmera no eixo Z;
R:   Alterna visualização 2D/3D;
K:   Alterna projeção ortográfica ou perspectiva;
1:   Alterna esconder/mostrar Engrenagem 1;
2:   Alterna esconder/mostrar Engrenagem 2;
3:   Alterna esconder/mostrar virabrequim;
4:   Alterna esconder/mostrar pistão;
5:   Alterna esconder/mostrar cilindro;


*/
// CPP Libraries
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

// Old Libraries
#include "gl_canvas2d.h"
#include "Frames.h"
#include "EventListener.h"
#include "TextBox.h"

// T4 Libraries
#include "Obj3D.h"
#include "Virabrequim.h"
#include "Gear.h"
#include "Cilindro.h"
#include "Pistao.h"
#include "Teclado.h"

using namespace std;

//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 700, screenHeight = 700;



float gear_ratio = 17./12.; // Sincronia entre engrenagens
float y_conn_pistao = 30.f; // Altura em que pistao se conecta com virabrequim
int points = 30;            // Numero de pontos utilizados para circulos
float pistao_arm = 90.f;    // Altura do braço do pistao
float cil_height = 100.f;   // Altura do cilindro
float dist_pratos = 35.f;   //Distância entre pratos do virabrequin
float RPM_fps = 0.f;
float main_rotatiom = 0.00;

//Declaração dos componentes
Gear G1 = Gear(80.f, 10.f, -1.75f);
Gear G2 = Gear(60.f, 10.f, 0.0);
Pistao P = Pistao(points, pistao_arm, 8.f, 20., 20., 5.);
Vector3 P_src_coord = Vector3(0.f,y_conn_pistao,0.f);
Virabrequim V = Virabrequim(points, 10.f, y_conn_pistao, dist_pratos, 7.f, 10.f, 5.f);
Cilindro C = Cilindro(20, 21.f, 25.f, cil_height);
Teclado T = Teclado();

void view2d()
{
    vector<Vector2> cilindro_src = {Vector2(-15.,0.), Vector2(-15.,-110.), Vector2(15.,-110.), Vector2(15.,0.)};
    vector<Vector2> pist_src = {Vector2(-10.,0.), Vector2(10.,0.), Vector2(10.,70.), Vector2(15.,70.),
                                Vector2(15.,90.),Vector2(-15.,90.),Vector2(-15.,70.),Vector2(-10.,70.)
                               }; //* pontos
    vector<Vector2> virb_pist = {Vector2(-15.,0.), Vector2(-15.,y_conn_pistao), Vector2(15.,y_conn_pistao), Vector2(15.,0.)};
    vector<Vector2> gear1 = vector<Vector2>();



    for(Vector2 &item: pist_src)
    {
        item.rotate(P.rotate_z);
        item += Vector2(P.coordinates.x, P.coordinates.y);
        item = item*2;
    }

    for(Vector2 &item: cilindro_src)
    {
        item.rotate(P.rotate_z);
        item += Vector2(C.coordinates.x, C.coordinates.y);
        item = item*2;
    }


    for(Vector2 &item: virb_pist)
    {
        item.rotate(V.rotate_z);
        item = item*2;
    }

    if(T.sw_g2){
    for(aresta_st aresta: G2.arestas[0])
    {
            G2.rotations();
            G2.translation();
        CV::line(Vector2(aresta.p1->modified_vec.x, aresta.p1->modified_vec.y) + Vector2(G2.coordinates.x, G2.coordinates.y),
                 Vector2(aresta.p2->modified_vec.x, aresta.p2->modified_vec.y) + Vector2(G2.coordinates.x, G2.coordinates.y));

    }
    }

    if(T.sw_g1){
    for(aresta_st aresta: G1.arestas[0])
    {
        G1.rotations();
        G1.translation();
        CV::line(Vector2(aresta.p1->modified_vec.x, aresta.p1->modified_vec.y),
                 Vector2(aresta.p2->modified_vec.x, aresta.p2->modified_vec.y));
    }
    }

    if(T.sw_cil){
    CV::color(yellow);
    CV::polygonFill(cilindro_src);
    }

    if(T.sw_pi){
    CV::color(gray);
    CV::polygon(pist_src);
    }

    if(T.sw_v){
    CV::color(red);
    CV::polygonFill(virb_pist);
    CV::color(green);
    CV::circleFill(Vector2(0.,0.), 10.f,points);
    CV::circleFill(Vector2(P.coordinates.x, P.coordinates.y)*2, 10.f,points);
    CV::circleFill(Vector2(C.coordinates.x, C.coordinates.y)*2, 10.f,points);
    }
}

string text_info()
{
    //TEXTOS
    stringstream txt;
    txt << fixed << setprecision(3) << "View: " ;
    if(T.sw_2d)
    {
        txt << "2D " << endl;
    }
    else
    {
        txt << ((T.sw_o==true)?"3D[Ortografica] ":"3D[Perspectiva] ") << endl;
    }


    txt << "Gear 1: " << ((T.sw_g1==true)?"ON ":"OFF") << endl;
    txt << "Gear 2: " << ((T.sw_g2==true)?"ON ":"OFF") << endl;
    txt << "Virabrequim: " << ((T.sw_v==true)?"ON ":"OFF") << endl;
    txt << "Pistao: " << ((T.sw_pi==true)?"ON ":"OFF") << endl;
    txt << "Cilindro: " << ((T.sw_cil==true)?"ON ":"OFF") << endl;
    txt << "RPM: " << (int)(T.RPM) << endl <<  "FPS: " << Frames::getFrames() << endl;


    return txt.str();

}

void CV_render()
{
    CV::translate(350.,300.);

    //TODA A MATEMÁTICA
    G1.rotate_z -= RPM_fps;
    G2.rotate_z += RPM_fps*gear_ratio;
    V.rotate_z -=  RPM_fps;
    P.coordinates = P_src_coord;
    P.coordinates.rotacionaZ(V.rotate_z);

    Vector2 p_v2 = Vector2(P.coordinates.x, P.coordinates.y);
    Vector2 c_v2 = Vector2(C.coordinates.x, C.coordinates.y);

    Vector2 aux = c_v2 - p_v2;
    float angle_p = Vector2::angle(Vector2(0., 1.), aux);

    P.rotate_z = angle_p*-1.;
    C.rotate_z = angle_p*-1;


    //RENDERIZAÇÃO
    if(!T.sw_2d)
    {

        //Renderização 3d dos compontentes
        if(T.sw_v) V.render(T.sw_o);
        if(T.sw_g1) G1.render(T.sw_o);
        if(T.sw_g2) G2.render(T.sw_o);
        if(T.sw_pi) P.render(T.sw_o);
        if(T.sw_cil) C.render(T.sw_o);

    }
    else
    {
        view2d(); //Renderização 2d
    }

    //Controle FPS e RPM
    Frames::updateFrames();
    //Variação em radianos a partir de RPM e fps
    float fps = Frames::getFrames();
    RPM_fps = (T.RPM*M_PI*2.)/(fps*60);

    TextBox Tbox = TextBox(text_info(), left_center, Vector2(0., 0.f));
    Tbox.setTextColor(green);
    Tbox.setBackground(black);

    //Tbox.resize();
    CV::translate(Vector2(20.,screenHeight - Tbox.getHeightText() -30.f));
    Tbox.render();
}


int main()
{
    // Interações de teclas
    EventListener::add_event(&T, en_keyboard_down);

    //Definir coordenada dos objetos/componentes
    G1.coordinates = Vector3(0.f,0.f,dist_pratos);
    G2.coordinates =  G1.coordinates + Vector3(125.f, 0.f, 0.f);
    V.coordinates = Vector3(0.f,0.f,0.f);
    P.coordinates = P_src_coord;
    C.coordinates = Vector3(0.f,cil_height+y_conn_pistao+20.f,0.f);

    CV::init(screenWidth, screenHeight, "T4_JOAO_VITOR_RATES");
    CV::run();
    return 0;
}

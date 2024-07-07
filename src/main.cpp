/*
    Lista de Instruções:
    O usuário interage  com a aplicação usando somente o mouse,
    para atirar use o botão esquerdo, para rotacionar o canhão mova o mouse;

    Quesitos Implementados:
    Além dos critérios básicos de avaliação, foram implementados.
    - Outros tipos de primitivas, além de quadrados (0.5 pontos).
    - Menu incial (0.5 pontos).
    - Criação de várias fases do jogo (até 1 ponto). Muda-se de fase quando
    todos os quadrados são removidos.

*/





#include "gl_canvas2d.h"
#include "Frames.h"
#include "GUI.h"
#include "EventListener.h"
#include <string>
#include <math.h>

#include "Obj3D.h"
#include "Virabrequim.h"
#include "Gear.h"
#include "Cilindro.h"
#include "Pistao.h"

#include "virabrequim2d.h"

#define _USE_MATH_DEFINES



using namespace std;








//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 505, screenHeight = 600;


Vector2 p1 = Vector2(0.,100.);
Vector2 p3 = Vector2(100.,0.);
float raio = 50;

double angle = 0.;


//virabrequim2d V = virabrequim2d(50, 0, 20, 0, 100, 16);



//FIXME Controle via FPS;
float main_rotatiom = 0.00;

/*
Não altere estes valores
*/

//Switches para mostrar ou não os componentes
bool sw_g1 = true;
bool sw_g2 = true;
bool sw_v = true;
bool sw_cil = true;
bool sw_axis = true;
bool sw_pi = true;


float gear_ratio = 17./12.;
float y_conn_pistao = 30.f;
int points = 20;
float pistao_arm = 90.f;
float cil_height = 100.f;
float main_rotation = 0.0000;
float dist_pratos = 35.f;
Gear G1 = Gear(80.f, 10.f, -1.75f);
Gear G2 = Gear(60.f, 10.f, 0.0);
Pistao P = Pistao(points, pistao_arm, 8.f, 20., 20., 5.);
Vector3 P_src_coord = Vector3(0.f,y_conn_pistao,0.f);
Virabrequim V = Virabrequim(points, 10.f, y_conn_pistao, dist_pratos, 7.f, 10.f, 5.f);
Cilindro C = Cilindro(20, 20.f, 25.f, cil_height);
float RPM = 10.f;
float RPM_fps = 0.f;


class Cardan:public Obj3D{
    public:
    Cardan(){
        rotate_old = false;
        float step = (M_PI*2 )/20.f;
    //Cilindro Eixo
        vector<shared_ptr<point3d_t>> tmp3 = vector<shared_ptr<point3d_t>>();
        vector<shared_ptr<point3d_t>> tmp4 = vector<shared_ptr<point3d_t>>();
        int points  = 20;
        for(int i = 0; i < points; i++)
        {
            tmp3.push_back(make_shared<point3d_t>(5.*cos(i*step),

                                                  -10.,
                                                  5*sin(i*step)));

            tmp4.push_back(make_shared<point3d_t>(5.*cos(i*step),

                                                  10.,
                                                  5.*sin(i*step)));

        }


        //Cilindro Suporte Pistão
        vector<shared_ptr<point3d_t>> tmp5 = vector<shared_ptr<point3d_t>>();
        vector<shared_ptr<point3d_t>> tmp6 = vector<shared_ptr<point3d_t>>();
        for(int i = 0; i < points; i++)
        {
            tmp5.push_back(make_shared<point3d_t>(-10.,
                                                  5.*cos(i*step),
                                                  5*sin(i*step)));

            tmp6.push_back(make_shared<point3d_t>(10.,
                                                  5.*cos(i*step),
                                                  5.*sin(i*step)));
        }



        //União de arestas e pontos


        this->arestas.push_back(Arestas::linear(tmp3, true));
        this->arestas.push_back(Arestas::linear(tmp4, true));
        this->arestas.push_back(Arestas::linear(tmp5, true));
        this->arestas.push_back(Arestas::linear(tmp6, true));
        this->arestas.push_back(Arestas::intercalado(tmp3, tmp4));
        this->arestas.push_back(Arestas::intercalado(tmp5, tmp6));

        for(auto item: tmp3)
        {
            this->points.push_back(item);
        }
        for(auto item: tmp4)
        {
            this->points.push_back(item);
        }
        for(auto item: tmp5)
        {
            this->points.push_back(item);
        }
        for(auto item: tmp6)
        {
            this->points.push_back(item);
        }



    }
};

Cardan Ca = Cardan();


void CV_render()
{
    CV::translate(200.,200.);

    //TODA A MATEMÁTICA

    Ca.rotate_z = RPM_fps;
    G1.rotate_z -= RPM_fps;
    G2.rotate_z += RPM_fps*gear_ratio;
    V.rotate_z -=  RPM_fps;
    P.coordinates = P_src_coord;
    P.coordinates.rotacionaZ(V.rotate_z);

    Vector2 p_v2 = Vector2(P.coordinates.x, P.coordinates.y);
    Vector2 c_v2 = Vector2(C.coordinates.x, C.coordinates.y);

    Vector2 aux = c_v2 - p_v2;
    //cout <<endl<< p_v2 << c_v2 << endl << aux << endl; exit(0);
    float angle_p = Vector2::angle(Vector2(0., 1.), aux);

    P.rotate_z = angle_p*-1.;
    C.rotate_z = angle_p*-1;





    if(sw_v) V.render();
    if(sw_g1) G1.render();
    if(sw_g2) G2.render();
    if(sw_pi) P.render();
    if(sw_cil) C.render();
    //Ca.render();


    //exit(0);


    Frames::updateFrames();

    //Variação em radianos a partir de RPM e fps
    float fps = Frames::getFrames();
    RPM_fps = (RPM*M_PI*2.)/(fps*60);
}


class Teclado: public EventClient
{

    bool key_press(int k) override
    {
        cout << "Key:" << k << endl;

        switch(k){

        case 49: sw_g1 = !sw_g1; break;
        case 50: sw_g2 = !sw_g2; break;
        case 51: sw_v = !sw_v; break;
        case 52: sw_pi = !sw_pi; break;
        case 53: sw_cil = !sw_cil; break;

        case 119: CV::rotate_x += 0.03; break;
        case 115: CV::rotate_x -= 0.03; break;
        case 97 : CV::rotate_y += 0.03; break;
        case 100: CV::rotate_y -= 0.03; break;
        case 113: CV::rotate_z += 0.03; break;
        case 101: CV::rotate_z -= 0.03; break;

        case 105: Ca.rotate_x -= 0.03; break;
        case 107: Ca.rotate_x += 0.03; break;
        case 106: Ca.rotate_y -= 0.03; break;
        case 108: Ca.rotate_y += 0.03; break;

        case 201: CV::camera_coord += Vector3(0.,0.,10); break;
        case 203: CV::camera_coord -= Vector3(0.,0.,10); break;

        case 200: RPM+=1.f; break;
        case 202: RPM-=1.f; break;


        }
        return false;
    }
};



int main()
{

    Teclado teclado = Teclado();

    EventListener::add_event(&teclado, en_keyboard_down);

    G1.coordinates = Vector3(0.f,0.f,dist_pratos);
    G2.coordinates =  G1.coordinates + Vector3(125.f, 0.f, 0.f);
    V.coordinates = Vector3(0.f,0.f,0.f);
    P.coordinates = P_src_coord;
    C.coordinates = Vector3(0.f,cil_height+y_conn_pistao+20.f,0.f);

    CV::camera_d = 400.f;
    CV::camera_coord = Vector3(0., 0., -200.);

    CV::init(screenWidth, screenHeight, "T4_JOAO_VITOR_RATES");
    CV::run();



    return 0;
}

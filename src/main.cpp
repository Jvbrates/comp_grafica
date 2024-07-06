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
#include "virabrequim2d.h"
#include "Obj3D.h"
#define _USE_MATH_DEFINES



using namespace std;

vector<shared_ptr<point3d_t>> gear_points(float external_ray, float z)
{

    vector<shared_ptr<point3d_t>> ret = vector<shared_ptr<point3d_t>>();

    float teeth = M_PI*2.;
    float deep_ray = 20.f;
    float arco = teeth/external_ray;
    float arco_in = teeth/(external_ray-deep_ray);

    int c = 0;
    bool swap = true;
    for(float i = 0.f; i <= M_PI*2;)
    {
        if(c++%2 == 0 )
        {
            swap = !swap;
        }
        else
        {
            swap = swap;
        }


        if(swap)
        {
            ret.push_back(make_shared<point3d_t>(
                              external_ray*cos(i),
                              external_ray*sin(i),
                              z)
                         );
            i+=arco;
        }
        else
        {
            ret.push_back(make_shared<point3d_t>(
                              (external_ray-deep_ray)*cos(i),
                              (external_ray-deep_ray)*sin(i),
                              z)
                         );
            i+=arco_in;
        }


    }

    return ret;
}



class Gear: public Obj3D
{
public:
    Gear(float external_ray, float z_value, float rotate_z_ = 0.f, float miolo = 5.0)
    {
        this->rotate_z = rotate_z_;

        vector<shared_ptr<point3d_t>> p1 = gear_points(external_ray, z_value/2.f);
        vector<shared_ptr<point3d_t>> p2 = gear_points(external_ray, z_value/-2.f);


        vector<aresta_st> m1 = Arestas::linear(p1, true);
        vector<aresta_st> m2 = Arestas::linear(p2, true);
        vector<aresta_st> m3 = Arestas::intercalado(p1, p2);

        for(auto p: p1)
        {
            points.push_back(p);
        }
        for(auto p: p2)
        {
            points.push_back(p);
        }

        arestas.push_back(m1);
        arestas.push_back(m2);
        arestas.push_back(m3);


        vector<shared_ptr<point3d_t>> tmp = vector<shared_ptr<point3d_t>>();
        vector<shared_ptr<point3d_t>> tmp1 = vector<shared_ptr<point3d_t>>();

        float step = (M_PI*2)/20.;
        for(int i = 0; i < 20; i++)
        {
            tmp.push_back(make_shared<point3d_t>(miolo*cos(i*step),
                                                 miolo*sin(i*step),
                                                 z_value/2.f
                                                ));

            tmp1.push_back(make_shared<point3d_t>(miolo*cos(i*step),
                                                  miolo*sin(i*step),
                                                  z_value/-2.f
                                                 ));

        }




        arestas.push_back(Arestas::linear(tmp, true));
        arestas.push_back(Arestas::linear(tmp1, true));

        arestas.push_back(Arestas::intercalado(tmp, tmp1));

        for(auto p: tmp)
        {
            points.push_back(p);
        }
        for(auto p: tmp1)
        {
            points.push_back(p);
        }


    }
};


class Virabrequim: public Obj3D
{

public:


    Virabrequim()
    {

        //Virabrequim

        int points = 20;
        float ray = 10.;
        float distance = 30.f;
        float dist_pratos = 30.f;
        float ray_x = 10.f;
        float depth = 10.;
        float cil_ray = 5.f;
        double step = (M_PI*2)/(double)points;


        vector<shared_ptr<point3d_t>> tmp = vector<shared_ptr<point3d_t>>();

        //PRATO 1
        for(int i = 0; i < points; i++)
        {

            if(sin(i*step)<.4)
            {
                this->points.push_back(make_shared<point3d_t>((ray+ray_x)*cos(i*step),
                                       ray*sin(i*step),
                                       depth/2. + dist_pratos/-2.));

                tmp.push_back(make_shared<point3d_t>((ray+ray_x)*cos(i*step),
                                                     ray*sin(i*step),
                                                     depth/-2. + dist_pratos/-2.));
            }
            else
            {
                this->points.push_back(make_shared<point3d_t>(ray*cos(i*step),
                                       ray*sin(i*step) + distance,
                                       depth/2. + dist_pratos/-2.));
                tmp.push_back(make_shared<point3d_t>(ray*cos(i*step),
                                                     ray*sin(i*step) + distance,
                                                     depth/-2. + dist_pratos/-2.));
            }

        }


        // PRATO 2
        vector<shared_ptr<point3d_t>> tmp1 = vector<shared_ptr<point3d_t>>();
        vector<shared_ptr<point3d_t>> tmp2 = vector<shared_ptr<point3d_t>>();
        for(int i = 0; i < points; i++)
        {

            if(sin(i*step)<.4)
            {
                tmp1.push_back(make_shared<point3d_t>((ray+ray_x)*cos(i*step),
                                                      ray*sin(i*step),
                                                      depth/2. + dist_pratos/2.));

                tmp2.push_back(make_shared<point3d_t>((ray+ray_x)*cos(i*step),
                                                      ray*sin(i*step),
                                                      depth/-2. + dist_pratos/2.));
            }
            else
            {
                tmp1.push_back(make_shared<point3d_t>(ray*cos(i*step),
                                                      ray*sin(i*step) + distance,
                                                      depth/2. + dist_pratos/2.));
                tmp2.push_back(make_shared<point3d_t>(ray*cos(i*step),
                                                      ray*sin(i*step) + distance,
                                                      depth/-2. + dist_pratos/2. ));
            }

        }


        //Cilindro Eixo
        vector<shared_ptr<point3d_t>> tmp3 = vector<shared_ptr<point3d_t>>();
        vector<shared_ptr<point3d_t>> tmp4 = vector<shared_ptr<point3d_t>>();
        for(int i = 0; i < points; i++)
        {
            tmp3.push_back(make_shared<point3d_t>(cil_ray*cos(i*step),
                                                  cil_ray*sin(i*step),
                                                  dist_pratos/-2. - depth));

            tmp4.push_back(make_shared<point3d_t>(cil_ray*cos(i*step),
                                                  cil_ray*sin(i*step),
                                                  dist_pratos/2. + depth));

        }


        //Cilindro Suporte Pistão
        vector<shared_ptr<point3d_t>> tmp5 = vector<shared_ptr<point3d_t>>();
        vector<shared_ptr<point3d_t>> tmp6 = vector<shared_ptr<point3d_t>>();
        for(int i = 0; i < points; i++)
        {
            tmp5.push_back(make_shared<point3d_t>(cil_ray*cos(i*step),
                                                  cil_ray*sin(i*step) + distance,
                                                  dist_pratos/-2.));

            tmp6.push_back(make_shared<point3d_t>(cil_ray*cos(i*step),
                                                  cil_ray*sin(i*step) + distance,
                                                  dist_pratos/2.));

        }



        //União de arestas e pontos

        this->arestas.push_back(Arestas::linear(this->points,true));
        this->arestas.push_back(Arestas::linear(tmp, true));
        this->arestas.push_back(Arestas::linear(tmp1, true));
        this->arestas.push_back(Arestas::linear(tmp2, true));
        this->arestas.push_back(Arestas::linear(tmp3, true));
        this->arestas.push_back(Arestas::linear(tmp4, true));
        this->arestas.push_back(Arestas::linear(tmp5, true));
        this->arestas.push_back(Arestas::linear(tmp6, true));
        this->arestas.push_back(Arestas::intercalado(this->points, tmp));
        this->arestas.push_back(Arestas::intercalado(tmp1, tmp2));
        this->arestas.push_back(Arestas::intercalado(tmp3, tmp4));
        this->arestas.push_back(Arestas::intercalado(tmp5, tmp6));

        for(auto item: tmp)
        {
            this->points.push_back(item);
        }
        for(auto item: tmp1)
        {
            this->points.push_back(item);
        }
        for(auto item: tmp2)
        {
            this->points.push_back(item);
        }
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

        /*

            this->points.push_back(make_shared<point3d_t>(-10.,-10.,-10.));
            this->points.push_back(make_shared<point3d_t>(-10.,-10.,10.));
            this->points.push_back(make_shared<point3d_t>(-10.,10.,10.));
            this->points.push_back(make_shared<point3d_t>(-10.,10.,-10.));

            this->arestas.push_back(Arestas::linear(this->points,true));


            vector<shared_ptr<point3d_t>> tmp = vector<shared_ptr<point3d_t>>();

            tmp.push_back(make_shared<point3d_t>(10.,-10.,-10.));
            tmp.push_back(make_shared<point3d_t>(10.,-10.,10.));
            tmp.push_back(make_shared<point3d_t>(10.,10.,10.));
            tmp.push_back(make_shared<point3d_t>(10.,10.,-10.));

            this->arestas.push_back(Arestas::linear(tmp,true));


            this->arestas.push_back(Arestas::intercalado(this->arestas[0],this->arestas[1], true));


            for(shared_ptr<point3d_t> p: tmp){
                this->points.push_back(p);
            }


            this->coordinates = Vector3(0, 0, 30);

            this->rotate_y =0.f;
        */

    }
};


class Pistao: public Obj3D
{
public:
    Pistao(int n_points, float arm_length, float arm_ray, float head_length, float head_ray, float z_displace)
    {

        // Haste
        float step = (M_PI*2)/(float)n_points;

        vector<shared_ptr<point3d_t>> tmp = vector<shared_ptr<point3d_t>>();
        vector<shared_ptr<point3d_t>> tmp2 = vector<shared_ptr<point3d_t>>();
        vector<shared_ptr<point3d_t>> tmp3 = vector<shared_ptr<point3d_t>>();
        vector<shared_ptr<point3d_t>> tmp4 = vector<shared_ptr<point3d_t>>();
        vector<shared_ptr<point3d_t>> tmp5 = vector<shared_ptr<point3d_t>>();

        for(int i = 0; i < n_points; i++)
        {
            tmp.push_back(make_shared<point3d_t>(
                              arm_ray*cos(i*step),
                              - z_displace,
                              arm_ray*sin(i*step)
                          ));

            tmp2.push_back(make_shared<point3d_t>(
                               arm_ray*cos(i*step),
                               arm_length - z_displace,
                               arm_ray*sin(i*step)
                           ));


            tmp3.push_back(make_shared<point3d_t>(
                               head_ray*cos(i*step),
                               arm_length - z_displace,
                               head_ray*sin(i*step)
                           ));

            tmp4.push_back(make_shared<point3d_t>(
                               head_ray*cos(i*step),
                               head_length + arm_length - z_displace,
                               head_ray*sin(i*step)
                           ));


            tmp5.push_back(make_shared<point3d_t>(
                               arm_ray*cos(i*step),
                               head_length + arm_length - z_displace,
                               arm_ray*sin(i*step)
                           ));
        }




        arestas.push_back(Arestas::linear(tmp, true));
        arestas.push_back(Arestas::linear(tmp2, true));
        arestas.push_back(Arestas::linear(tmp3, true));
        arestas.push_back(Arestas::linear(tmp4, true));
        arestas.push_back(Arestas::linear(tmp5, true));
        arestas.push_back(Arestas::intercalado(tmp, tmp2));
        arestas.push_back(Arestas::intercalado(tmp3, tmp4));
        arestas.push_back(Arestas::intercalado(tmp3, tmp2));
        arestas.push_back(Arestas::intercalado(tmp5, tmp4));

        for(auto p: tmp )
        {
            points.push_back(p);
        }
        for(auto p: tmp2)
        {
            points.push_back(p);
        }
        for(auto p: tmp3)
        {
            points.push_back(p);
        }
        for(auto p: tmp4)
        {
            points.push_back(p);
        }
        for(auto p: tmp5)
        {
            points.push_back(p);
        }

    }
};

class Cilindro: public Obj3D
{
public:
    Cilindro(int n_points, float internal_ray, float external_ray, float height)
    {
        float step = (M_PI*2)/(float)n_points;


        vector<shared_ptr<point3d_t>> tmp = vector<shared_ptr<point3d_t>>();
        vector<shared_ptr<point3d_t>> tmp2 = vector<shared_ptr<point3d_t>>();
        vector<shared_ptr<point3d_t>> tmp3 = vector<shared_ptr<point3d_t>>();
        vector<shared_ptr<point3d_t>> tmp4 = vector<shared_ptr<point3d_t>>();


        for(int i = 0; i < n_points; i++)
        {
            tmp.push_back(make_shared<point3d_t>(
                              internal_ray*cos(i*step),
                              internal_ray - external_ray,
                              internal_ray*sin(i*step)
                          ));

            tmp2.push_back(make_shared<point3d_t>(
                               internal_ray*cos(i*step),
                               - height,
                               internal_ray*sin(i*step)
                           ));


            tmp3.push_back(make_shared<point3d_t>(
                               external_ray*cos(i*step),
                               0,
                               external_ray*sin(i*step)
                           ));

            tmp4.push_back(make_shared<point3d_t>(
                               external_ray*cos(i*step),
                               - height,
                               external_ray*sin(i*step)
                           ));
        }


        shared_ptr<point3d_t> center = make_shared<point3d_t>(0.f,0.f,0.f);

        arestas.push_back(Arestas::linear(tmp, true));
        arestas.push_back(Arestas::linear(tmp2, true));
        arestas.push_back(Arestas::linear(tmp3, true));
        arestas.push_back(Arestas::linear(tmp4, true));
        arestas.push_back(Arestas::intercalado(tmp, tmp2));
        arestas.push_back(Arestas::intercalado(tmp3, tmp4));
        arestas.push_back(Arestas::central(tmp, center));
        arestas.push_back(Arestas::central(tmp3, center));



        for(auto p: tmp )
        {
            points.push_back(p);
        }
        for(auto p: tmp2)
        {
            points.push_back(p);
        }
        for(auto p: tmp3)
        {
            points.push_back(p);
        }
        for(auto p: tmp4)
        {
            points.push_back(p);
        }
        points.push_back(center);



    }
};
double  to_degres(double rad)
{
    return rad*180/M_PI;
}

//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 505, screenHeight = 600;

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa fun��o com poucas linhas de codigo.

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
bool sw_cil = false;
bool sw_axis = false;
bool sw_pi = false;


float gear_ratio = 17./12.;

Gear G1 = Gear(80.f, 10.f, -1.75f);
Gear G2 = Gear(60.f, 10.f, 0.0);
Pistao P = Pistao(20, 100.f, 20.f, 30., 50., 20.);
Virabrequim V = Virabrequim();
Cilindro C = Cilindro(20, 50.f, 60.f, 150.f);


void CV_render()
{

    CV::camera_d = 600.f;

    //main_rotatiom += 0.0001;

    G1.rotate_z += main_rotatiom;
    G2.rotate_z -= main_rotatiom*gear_ratio;
    V.rotate_z += main_rotatiom;

    G1.coordinates = Vector3(0.f,0.f,200.f);
    G2.coordinates =  G1.coordinates + Vector3(130.f, 0.f, 0.f);
    V.coordinates = Vector3(0.f,0.f,100.f);
    P.coordinates = Vector3(0.f,0.f,150.f);
    C.coordinates = Vector3(0.f,150.f,150.f);

    CV::translate(200.,200.);


    if(sw_v) V.render();
    if(sw_g1) G1.render();
    if(sw_g2) G2.render();
    if(sw_pi) P.render();
    if(sw_cil) C.render();


    //exit(0);

    if(false)
    {
        //CV::polygon(V.points);




        CV::translate(200.,200.);
        Frames::updateFrames();
        float fps = Frames::getFrames();

        //CV::text(Vector2(10.,10.),std::to_string(fps));

        Vector2 p2 = Vector2(raio*cos(angle), raio*sin(angle)) + p3;

        CV::color(red);
        CV::circle(p3, raio, 10);
        CV::color(green);
        CV::circle(p2, 10, 4);


        Vector2 p1_p3 = p3-p1;
        Vector2 p1_p2 = p2-p1;

        double c_angle = Vector2::angle(p1_p2, p1_p3);

        CV::color(blue);

        CV::line(Vector2(0.,0.),p1_p3);
        CV::color(red);

        Vector2 cil = p1_p3*1;
        cil.rotate(c_angle);

        CV::line(p1, p1+cil);

        double angle_pist =   M_PI + cil.getAngle() ;
        Vector2 pistao = Vector2(0.,20.);
        pistao.setAngle(angle_pist);

        CV::color(gray);
        CV::line(p2, p2+pistao);




        for (Renderizable *item: CV::render_stack)
        {

            //Movido para reduzir o custo de processamento
            if(item->visible == false)
            {
                continue;
            }

            CV::color(black);
            item->render_caller();
        }

    }


}


class Teclado: public EventClient
{

    bool key_press(int k) override
    {
        std::cout << "Key: " << k << std::endl;

        if(k == 120)
        {
            P.rotate_x -= 0.3;
            G2.rotate_x -= 0.3;
            V.rotate_x -= 0.3;
        }
        else if (k == 203)
        {
            CV::camera_d+=1;
        }
        else if (k == 121)
        {
            P.rotate_y += 0.3;
            G2.rotate_y += 0.3;
            V.rotate_y += 0.3;
        }
        else if (k == 122)
        {
            P.rotate_z -= 0.3;
            G2.rotate_z -= 0.3;
            V.rotate_z -= 0.3;

        }


        cout << G1.rotate_x << endl << G1.rotate_y << endl << G1.rotate_z << endl;




        return false;
    }
};



int main()
{


    //GUI I = GUI();

    //EventListener::captureEvent[en_mouse_left] = true;


    //CV::render_stack.push_back(&I);

    Teclado teclado = Teclado();

    EventListener::add_event(&teclado, en_keyboard_down);


    CV::init(screenWidth, screenHeight, "T3_JOAO_VITOR_RATES");
    CV::run();



    return 0;
}

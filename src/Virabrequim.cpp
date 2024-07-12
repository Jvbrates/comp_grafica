#include "Virabrequim.h"

Virabrequim::Virabrequim(int points, float ray, float distance, float dist_pratos, float ray_x, float depth, float cil_ray)
{

        //Virabrequim

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
                                                  dist_pratos/2));

            tmp4.push_back(make_shared<point3d_t>(cil_ray*cos(i*step),
                                                  cil_ray*sin(i*step),
                                                  dist_pratos/2. + depth*3.f));

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


    }


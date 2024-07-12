/*
Este código implementa uma classe `Obj3D` que realiza diversas transformações em
pontos tridimensionais, incluindo rotações, translações, projeções e
transformações de câmera, para posteriormente renderizá-los. A função `rotations`
aplica rotações nos pontos do objeto. Dependendo do valor do flag `rotate_old`, as
rotações são realizadas ou por rotação arbitrária ao redor dos eixos X, Y e Z ou
por multiplicação de matrizes de rotação. A função `translation` aplica uma
translação a todos os pontos, ajustando suas coordenadas com um vetor de
translação. A função `projection` aplica uma projeção perspectiva aos pontos,
calculando suas posições projetadas. A função `camera_transformation` ajusta as
coordenadas dos pontos de acordo com a posição da câmera e aplica rotações
adicionais conforme necessário. Finalmente, a função `render` chama todas essas
transformações e desenha as arestas entre os pontos, podendo optar entre uma
projeção ortográfica ou perspectiva, resetando os flags de projeção, rotação e
translação dos pontos ao final do processo.
*/

#ifndef OBJ3D_H
#define OBJ3D_H


#include <vector>
#include <memory>

#include "gl_canvas2d.h"
#include "Arestas.h"



using namespace std;

class Obj3D
{
    static shared_ptr<point3d_t> p_zero;
    friend class CV;
    friend void CV_render();
    friend void view2d();

    public:
        bool rotate_old = true;

        std::array<std::array<float, 3>, 3> matriz_rot = {{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    }};;


        Vector3 coordinates = Vector3(0., 0.,0.);

        aresta_t angle_x = aresta_st(p_zero, make_shared<point3d_t>(50., 0., 0.), red);
        aresta_t angle_y = aresta_st(p_zero, make_shared<point3d_t>(0., 50., 0.), green);
        aresta_t angle_z = aresta_st(p_zero, make_shared<point3d_t>(0., 0., 50.), blue);

        Vector3 angle_vector_y = Vector3(1., 0., 0.);
        Vector3 angle_vector_x = Vector3(0., 1., 0.);
        Vector3 angle_vector_z = Vector3(0., 0., 1.);

        double rotate_y = 0.0;
        double rotate_x = 0.0;
        double rotate_z = 0.0;

        vector<shared_ptr<point3d_t>> points;
        vector<vector<aresta_t>> arestas;




    protected:

    private:

        void rotations();
        void translation();
        void projection(float d);
        void camera_transformation();
        void render(bool ort);
};

#endif // OBJ3D_H

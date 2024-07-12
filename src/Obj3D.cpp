#include "Obj3D.h"

/*
Copia source para modified e aplica rotacoes
*/

shared_ptr<point3d_t> Obj3D::p_zero = make_shared<point3d_t>(0.,0.,0.);


void Obj3D::rotations()
{

    if(rotate_old)
    {

        Vector3 x_axis = Vector3(1.,0.,0.);
        Vector3 y_axis = Vector3(0.,1.,0.);
        Vector3 z_axis = Vector3(0.,0.,1.);
        for (auto &item : points)
        {
            item->modified_vec = item->source;

            if (!item->rotated)
            {
                item->modified_vec.rotateArbitrary(x_axis, rotate_x);
                item->modified_vec.rotateArbitrary(y_axis, rotate_y);
                item->modified_vec.rotateArbitrary(z_axis, rotate_z);
            }
        }
    }
    else
    {

        std::array<std::array<float, 3>, 3> Rx = {{
                {1, 0, 0},
                {0, cos(rotate_x), -sin(rotate_x)},
                {0, sin(rotate_x), cos(rotate_x)}
            }
        };

        std::array<std::array<float, 3>, 3> Ry = {{
                {cos(rotate_y), 0, sin(rotate_y)},
                {0, 1, 0},
                {-sin(rotate_y), 0, cos(rotate_y)}
            }
        };

        std::array<std::array<float, 3>, 3> Rz = {{
                {cos(rotate_z), -sin(rotate_z), 0},
                {sin(rotate_z), cos(rotate_z), 0},
                {0, 0, 1}
            }
        };

        std::array<std::array<float, 3>, 3> Rxy;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                Rxy[i][j] = 0;
                for (int k = 0; k < 3; ++k)
                {
                    Rxy[i][j] += Ry[i][k] * Rx[k][j];
                }
            }
        }

        std::array<std::array<float, 3>, 3> finalR;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                finalR[i][j] = 0;
                for (int k = 0; k < 3; ++k)
                {
                    finalR[i][j] += Rxy[i][k] * Rz[k][j];
                }
            }
        }

        // Atualizar a matriz de rotação acumulada multiplicando pela nova matriz de rotação
        std::array<std::array<float, 3>, 3> new_rotation_matrix;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                new_rotation_matrix[i][j] = 0;
                for (int k = 0; k < 3; ++k)
                {
                    new_rotation_matrix[i][j] += matriz_rot[i][k] * finalR[k][j];
                }
            }
        }

        matriz_rot = new_rotation_matrix;


        Vector3 x_axis(1.f, 0.f, 0.f);
        Vector3 y_axis(0.f, 1.f, 0.f);
        Vector3 z_axis(0.f, 0.f, 1.f);

        // Aplica as rotações aos pontos
        for (auto &item : points)
        {
            item->modified_vec = item->source;

            if (!item->rotated)
            {

                item->modified_vec = mmult(item->source, this->matriz_rot);

            }
        }

        rotate_x = 0.;
        rotate_z = 0.;
        rotate_y = 0.;

    }
}


void Obj3D::translation()
{

    for(auto &item : points)
    {
        if(!(item->translated))
        {

            (item->modified_vec)+=(this->coordinates);
            item->translated= true;



        }


    }

    //Angulos de apoio
    this->angle_x.p1->modified_vec +=  this->coordinates;
    this->angle_x.p2->modified_vec +=  this->coordinates;

    this->angle_y.p1->modified_vec +=  this->coordinates;
    this->angle_y.p2->modified_vec +=  this->coordinates;

    this->angle_z.p1->modified_vec +=  this->coordinates;
    this->angle_z.p2->modified_vec +=  this->coordinates;

}


void Obj3D::projection(float d)
{



    for(auto &item : points)
    {
        if(!(item->projected))
        {

            item->projZ(d);

            item->projected = true;

            // DEBUG( item->modified_vec << "-->" << item->projected_vec << endl)
        }
    }

}

//Aqui já terá rotacionado sobre si mesmo e sido transladado; Agora rotacionará sobre 0.
// e depois será trasnaldado para adaptar a camera
void Obj3D::camera_transformation()
{
    for (auto &point : points)
    {

        point->modified_vec.rotacionaX(CV::rotate_x);
        point->modified_vec.rotacionaY(CV::rotate_y);
        point->modified_vec.rotacionaZ(CV::rotate_z);

        point->camera_vec = point->modified_vec - CV::camera_coord;
    }
}


void Obj3D::render(bool ort)
{

    rotations();
    translation();


    camera_transformation();
    if(ort)
    {
        for(vector<aresta_t> &l_arestas: this->arestas)
        {
            for(aresta_st aresta: l_arestas)
            {
                CV::color(aresta.color);
                CV::line(Vector2(aresta.p1->camera_vec.x, aresta.p1->camera_vec.y),
                         Vector2(aresta.p2->camera_vec.x, aresta.p2->camera_vec.y));


                aresta.p1->projected = false;
                aresta.p2->rotated = false;
                aresta.p2->translated = false;
            }
        }

    }
    else
    {


        projection(CV::camera_d);

        for(vector<aresta_t> &l_arestas: this->arestas)
        {
            for(aresta_st aresta: l_arestas)
            {
                CV::color(aresta.color);
                CV::line(aresta.p1->projected_vec, aresta.p2->projected_vec);


                aresta.p1->projected = false;
                aresta.p2->rotated = false;
                aresta.p2->translated = false;
            }
        }

    }


}

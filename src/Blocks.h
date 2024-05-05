#ifndef BLOCKS_H
#define BLOCKS_H

#include "Conteiner.h"
#include "geometry/Polygon.h"
class Blocks
{
    public:
        Blocks();
        virtual ~Blocks();
        Conteiner poligonos;

        // Calcula a posição final do circulo, decrementa os blocos atingidos
        Vector2 moveCircle(Vector2 pos, Vector2 movement, float radius);

        // Desce uma linha de blocos
        void lineDown();
    protected:
        std::vector<std::shared_ptr<Polygon_>> selectByRectangle(Vector2 pos, Vector2 movement);

};

#endif // BLOCKS_H

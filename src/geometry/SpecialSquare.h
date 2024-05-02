#ifndef SPECIALSQUARE_H
#define SPECIALSQUARE_H

#include "Polygon.h"


class SpecialSquare : public Polygon_
{
    public:
        SpecialSquare(float size, Vector2 pos, float radius);
        void render() override;
        bool draw_collision = false;
    protected:
        std::vector<Vector2> drawPol;
    private:
};

#endif // SPECIALSQUARE_H

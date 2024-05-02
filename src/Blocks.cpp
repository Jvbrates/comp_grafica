#include "Blocks.h"
#include "geometry/SpecialSquare.h"
Blocks::Blocks()
{
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            poligonos.push(std::make_shared<SpecialSquare>(20., Vector2(20.*i, 20.*j), 5.));

        }
    }
}

Blocks::~Blocks()
{
    //dtor
}

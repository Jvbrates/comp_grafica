//
// Created by jvbrates on 4/22/24.
//

#ifndef COMP_GRAFICA_POLYGON_H
#define COMP_GRAFICA_POLYGON_H
#include "../Vector2.h"
#include "../Conteiner.h"

class Polygon: public Renderizable {
private:
    std::vector<Vector2> vertex;
    bool fill;
    colors_enum color = black;

public:
    explicit Polygon(std::vector<Vector2>);
    void render() override;
    void addVertex(Vector2 vertex);
    void setFill(bool f);
    void setColor(colors_enum color_);
    int  countEdge();
    std::vector<Vector2> getEdge(int i);
    std::vector<Vector2> *getVertex();
};

#endif //COMP_GRAFICA_POLYGON_H

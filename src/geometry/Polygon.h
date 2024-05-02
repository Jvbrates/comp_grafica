//
// Created by jvbrates on 4/22/24.
//

#ifndef COMP_GRAFICA_POLYGON_H
#define COMP_GRAFICA_POLYGON_H
#include "../Vector2.h"
#include "../Conteiner.h"

class Polygon_: public Renderizable {
protected:
    std::vector<Vector2> vertex;
    bool fill;
    colors_enum color = black;

public:
    explicit Polygon_(std::vector<Vector2>);
    explicit Polygon_();
    void render() override;
    void addVertex(Vector2 vertex);
    void addVertex(float x, float y);
    void setFill(bool f);
    void setColor(colors_enum color_);
    bool inside(Vector2 point);
    int  countEdge();
    std::vector<Vector2> getEdge(int i);
    std::vector<Vector2> *getVertex();
};

#endif //COMP_GRAFICA_POLYGON_H

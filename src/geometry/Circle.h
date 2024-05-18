//
// Created by jvbrates on 4/22/24.
//

#ifndef COMP_GRAFICA_CIRCLE_H
#define COMP_GRAFICA_CIRCLE_H

#include "../gl_canvas2d.h"
#include "../Renderizable.h"

class Circle: public Renderizable {
protected:
        float ray;
        bool fill = false;
        unsigned int vertex;
        colors_enum color = black;
    public:
        Circle(float ray_, unsigned int vertex_, colors_enum color_, bool filled);

        float getRay() const;

        void setRay(float ray);

        bool isFill() const;

        void setFill(bool fill);

        colors_enum getColor() const;

        void setColor(colors_enum color);

        void render() override;

    };


#endif //COMP_GRAFICA_CIRCLE_H

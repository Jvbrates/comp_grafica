//
// Created by jvbrates on 4/1/24.
//

#ifndef COMP_GRAFICA_HHSTOGRAM_H
#define COMP_GRAFICA_HHSTOGRAM_H

#include "gl_canvas2d.h"
#include <memory>
#include "ImageManagement.h"


class HistogramRender : public Renderizable{

private:

    uint min, max;
    float avg;
    enum_colors color;
    std::vector<float> normalized = std::vector<float>(0);

public:
    void render() override;
    HistogramRender(std::shared_ptr<color_data_t> color_channel, enum_colors colors);
    void reset(std::shared_ptr<color_data_t> color_channel, enum_colors colors);
};


#endif //COMP_GRAFICA_HHSTOGRAM_H

//
// Created by jvbrates on 4/1/24.
//

#include "Histogram.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>

HistogramRender::HistogramRender(std::shared_ptr<color_data_t> color_channel, enum_colors colors){
    this->size = {320.,172.};
    this->reset(color_channel, colors);
}

void HistogramRender::render() {

    CV::color(yellow);
    CV::rectFill({0.,0.}, {320.,172.});

//Contraste Fundo
    colors_enum  cor;
    if(color == en_bluescale) {
        cor = orange;
    } else if (color == en_greenscale){
        cor = red;
    } else if (color == en_redscale){
        cor = green;
    } else {
        cor = white;
    }

    CV::color(cor);

    CV::rectFill({31.5,17.}, {287.5,167.});

    if(!normalized.empty()) {


        for (int pos = 0; pos < normalized.size(); pos++) {

            if(color == en_bluescale) {
                CV::color(0, 0, (int) pos);
            } else if (color == en_greenscale){
                CV::color(0, (int) pos, 0);
            } else if (color == en_redscale){
                CV::color((int) pos, 0, 0);
            } else {
                CV::color(0,0,0);
            }


            CV::line(pos+32.5, 167, pos + 32.5, normalized[pos]);

        }

        if(color == en_bluescale) {
            cor = blue;
        } else if (color == en_greenscale){
            cor = green;
        } else if (color == en_redscale){
            cor = red;
        } else {
            cor = black;
        }
        CV::color(cor);
        CV::line(32.5, 167 - (float) avg / (float) max * 150.,
                 287.5,  167 - (float) avg / (float) max * 150.);

        CV::color(black);


    }

    CV::color(black);
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << avg;
    std::string text = "avg: "+ stream.str() + " max: " + std::to_string(max) + " min: "+std::to_string(min) ;
    CV::text({0.,12.}, text);


}

void HistogramRender::reset(std::shared_ptr<color_data_t> color_channel, enum_colors colors) {

    this->color = colors;

    this->normalized.clear();
    max = min = avg = 0;


    if(color_channel) {
        this->max = *(std::max_element(color_channel->histogram.vector.begin(), color_channel->histogram.vector.end()));
        this->min = *(std::min_element(color_channel->histogram.vector.begin(), color_channel->histogram.vector.end()));

        this->avg = 0;
        int avg_denominador = 0;

        for (const auto &item: color_channel->histogram.vector) {
            if (item) {
                avg += (float) item;
                avg_denominador++;
            }

            normalized.push_back(167 - (float) item / (float) max * 150.);
        }

        avg /= avg_denominador;
    }

}

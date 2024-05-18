#include "Game.h"
#include "Frames.h"
#include <iostream>

game_state_t Game::getState(){
    return this->state;
}

Game::Game(char level[]): blocks(level)
{


    cannon = Polygon_();
    cannon.addVertex(-10., -10.);
    cannon.addVertex(10., -10.);
    cannon.addVertex(10., 30.);
    cannon.addVertex(-10., 30.);

    cannon.setFill(true);

    cannon.setRelativePos(100., 10.);


}

void Game::operator()(char level[], int power)
{

    blocks(level);
    this->power = power;


    cannon.setRelativePos(100.,10.);
}






Game::Game(): blocks()
{
    cannon = Polygon_();
    cannon.addVertex(-10., -10.);
    cannon.addVertex(10., -10.);
    cannon.addVertex(10., 30.);
    cannon.addVertex(-10., 30.);

    cannon.setFill(true);


};

bool Game::win(){

    return (blocks.linhas_carregadas >= blocks.total_linhas &&
    blocks.poligonos.elements.size() == 1);
}

bool Game::lose(){

    //O primeiro elemento é a grade, o segundo é o poligono mais baixo;

    if(blocks.poligonos.elements.size() > 1){
        std::shared_ptr<Polygon_> lowest = std::dynamic_pointer_cast<Polygon_>(blocks.poligonos.elements[1]);
        return (lowest->getVertex()[0].y+ lowest->getAbsolutePos().y < 0.);
    }


    return false;
}


void Game::testeFim(){
    if(win()){
        state = en_win;
    } else if (lose()){
        state = en_lose;
    } else {
        state = mirando;
    }
}

void Game::transAtiraMira(){
    cannon.setRelativePos(last_pos_bullet);


    auto count = blocks.poligonos.elements.size();

    if(count > 1){
        blocks.loadLine();
    } else {
        while(blocks.poligonos.elements.size() <= 1
              && blocks.linhas_carregadas < blocks.total_linhas){
                blocks.loadLine();
              }
    }


    //lineDown(50.);
    state = teste_fim;
}

void Game::render() {

    auto tmp = std::vector<Vector2>();
    //Temporaruamente sem controle de FPS


    CV::color(red);
    CV::circleFill(bullet0, 5, 16);

    switch(state){
        case atirando:
            stateAtirando();
        break;

        case transicao_atira_mira:
            transAtiraMira();
        break;

        case teste_fim:
            testeFim();
            break;
        case en_lose:
            break;
            std::cout << "Perdeu" << std::endl;
        case en_win:
            std::cout << "Win" << std::endl;
            break;

    }
}

void Game::stateAtirando(){
    if(ammo){

        if(bullets.empty() || Vector2::distance(cannon.getAbsolutePos(), bullets[bullets.size()-1].pos) > db_bullets){
            auto tmpvec = mov.cpy();
            tmpvec.setAngle(cannon_angle.getAngle());
            bullets.emplace_back(bullet{cannon.getAbsolutePos() + cannon_angle, tmpvec});
            ammo--;
        }
    } else if(state == atirando && this->bullets.empty()){
        state = transicao_atira_mira;
        return;
    }



    std::vector<bullet>::iterator start = bullets.begin();
    for(auto it = start; it != bullets.end();){
        auto tmp = it;
        it++;


        data_moveCircle dt = blocks.moveCircle(tmp->pos, tmp->mov/Frames::getFrames()*mod_speed, 25, nullptr);

        if(dt.pos_final.y < 10.){

            last_pos_bullet = tmp->pos;
            it = bullets.erase(tmp);
        }else {
            tmp->pos = dt.pos_final;
            tmp->mov.setAngle(dt.reflex.getAngle());

            CV::color(red);
            CV::circle(tmp->pos, 10, 10);

        }
    }

}


void Game::lineDown(float down){
    this->blocks.poligonos.setRelativePos(Vector2(0, -down) + blocks.poligonos.getAbsolutePos());
};

bool Game::mouse_move(Vector2 pos, Vector2 desl){  //Rotação do canhão
    if(cannon_rotate && !ammo && state == mirando){
        Vector2 c_mouse = pos - cannon.getAbsolutePos();

        double diff_angle = c_mouse.getAngle() - cannon_angle.getAngle();

        cannon_angle.setAngle(cannon_angle.getAngle() + diff_angle);
        cannon.rotate(diff_angle);
    }


    return false;
}

bool Game::mouse_left(int state){



    std::cout << "Click em GAME: " << this->state << std::endl;
    if(this->state != mirando){
        return false;
    }
    if(!state){
        this->state = atirando;
        this->ammo = this->power++;
    }

    return true;
}

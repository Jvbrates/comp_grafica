/*
 * EventListener: Faz a administração dos eventos de teclado e mouse
 *
 * enum enum_event:tipo enumerate que define cada um dos evemtos possíveis
 *
 * std::vector<std::map<int, EventClient *>> EventMatrix: Matriz que possuí uma linha para cada evento,
 * as colunas representam pointeiros para EventClient(explicado abaixo) associada com um ID;
 *
 * add_event(EventClient *client, enum_event event): Adiciona um EventClient a EventMatrix na linha de
 * evento correspondente e define seu ID;
 *
 * demais funções: São callbacks das funções correspondentes do GLUT. Quando uma função destas é
 * chamada a linha correspondente ao evento é percorrida em EventMatrix então para cada EventClient
 * é chamada a função correspondente ao evento, estas funções são booleanas. Caso uma delas retorne
 * true e a flag correspondente(captureEvent) também true a linha deixa de ser percorrida.
 *
 * captureEvent: Vetor de booleanos referente a flag acima
 *
 *
 *
 * EventClient: Usada para comunicar-se com EventListener, não é usada diretamente; Feita para ser herdada
 * - int events_id[num_of_events]: Quando é adicionada para receber um evento de EventListener recebe um id, ao ser
 * destruida excluí sua propria entrada na tabela de eventos (através de EventListener::removeEvent),
 * assim evitando dinâmicamente um SEGFAULT.
 *
 * */

//
// Created by jvbrates on 3/14/24.
//

#ifndef SRC_EVENTLISTENER_H
#define SRC_EVENTLISTENER_H

#include <map>
#include <vector>
#include <iostream>
#include <functional>
#include "Vector2.h"


typedef enum {
    en_keyboard_down,
    en_keyboard_up,
    en_mouse_left,
    en_mouse_right,
    en_mouse_scroll,
    en_mouse_move,
    num_of_events

} enum_event;


class EventClient {


protected:
    int events_id[num_of_events] = {-1};

    friend class EventListener;

public:

    ~EventClient();

    virtual bool mouse_right(int) {
        //std::cout  << "Está função deveria ser sobrescrita";
        return false;
    }

    virtual bool mouse_left(int) {
        //std::cout  << "Está função deveria ser sobrescrita";
        return false;
    }

    virtual bool mouse_scroll(int) {
        //std::cout  << "Está função deveria ser sobrescrita";
        return false;
    }

    virtual bool mouse_move(Vector2<float> pos, Vector2<float> desloc) {
        //std::cout  << "Está função deveria ser sobrescrita";
        return false;
    }

    virtual bool key_press(int) {
        //std::cout  << "Está função deveria ser sobrescrita";
        return false;
    }

    virtual bool key_up(int) {
        //std::cout  << "Está função deveria ser sobrescrita";
        return false;
    }


};


class EventListener {
private:
    static std::vector<std::map<int, EventClient *>> EventMatrix;

public:

    static std::vector<bool> captureEvent;

    static void add_event(EventClient *client, enum_event event);

    static void removeEvent(int id, enum_event event);

    static void key_press(int);

    static void key_up(int);

    static void mouse_right(int);

    static void mouse_left(int);

    static void mouse_scroll(int);

    static void mouse_move(Vector2<float>, Vector2<float>);


};


#endif //SRC_EVENTLISTENER_H

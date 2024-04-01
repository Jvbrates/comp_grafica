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
        std::cout << "Está função deveria ser sobrescrita";
        return false;
    }

    virtual bool mouse_left(int) {
        std::cout << "Está função deveria ser sobrescrita";
        return false;
    }

    virtual bool mouse_scroll(int) {
        std::cout << "Está função deveria ser sobrescrita";
        return false;
    }

    virtual bool mouse_move(Vector2<float> pos, Vector2<float> desloc) {
        std::cout << "Está função deveria ser sobrescrita";
        return false;
    }

    virtual bool key_press(int) {
        std::cout << "Está função deveria ser sobrescrita";
        return false;
    }

    virtual bool key_up(int) {
        std::cout << "Está função deveria ser sobrescrita";
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

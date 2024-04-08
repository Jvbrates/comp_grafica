

//
// Created by jvbrates on 3/14/24.
//

#include "EventListener.h"

std::vector<bool> EventListener::captureEvent = std::vector<bool>
        (num_of_events, false);

std::vector<std::map<int, EventClient*> >  EventListener::EventMatrix =
        std::vector<std::map<int, EventClient *>>(num_of_events);

// Adicionar funcoes para receber eventos

EventClient::~EventClient(){
    int acm = 0;
    for (const auto &item: events_id){

        if (item != -1){
            EventListener::removeEvent(item, (enum_event)acm++);
        }
    }
}


void EventListener::removeEvent(int id, enum_event event) {
    auto a  = EventListener::EventMatrix[event];
    a.erase(id);

}

void EventListener::add_event(EventClient *client, enum_event event){
    static int id_acm[num_of_events];

    switch (event) {
        case en_mouse_right:
        case en_mouse_move:
        case en_mouse_left:
        case en_mouse_scroll:
        case en_keyboard_up:
        case en_keyboard_down: {
            EventListener::EventMatrix[event][id_acm[event]] = client;
            client->events_id[event] = id_acm[event]++;
            break;
        }

        default:
            //std::cout  << "Evento não definido";
            throw;

    }


}

 void EventListener::key_press(int caractere){

     for (const  auto item: EventListener::EventMatrix[en_keyboard_down]){
        bool stop = item.second->key_press(caractere);

        if(stop && EventListener::captureEvent[en_keyboard_down]){
            break;
        }
    }
}
void EventListener::key_up(int caractere){
    for (const  auto item: EventListener::EventMatrix[en_keyboard_up]){
        bool stop = item.second->key_up(caractere);

        if(stop && EventListener::captureEvent[en_keyboard_up]){
            break;
        }
    }
}

void EventListener::mouse_right(int state) {
    for (const  auto item: EventListener::EventMatrix[en_mouse_right]){
        bool stop = item.second->mouse_right(state);

        if(stop && EventListener::captureEvent[en_mouse_right]){
            break;
        }
    }
}

void EventListener::mouse_left(int state) {
    for (const  auto item: EventListener::EventMatrix[en_mouse_left]){
        bool stop = item.second->mouse_left(state);

        if(stop && EventListener::captureEvent[en_mouse_left]){
            break;
        }
    }
}

void EventListener::mouse_move(Vector2<float> pos, Vector2<float> disp) {
    for (const  auto item: EventListener::EventMatrix[en_mouse_move]){
        bool stop = item.second->mouse_move(pos, disp);

        if(stop && EventListener::captureEvent[en_mouse_move]){
            break;
        }
    }
}

void EventListener::mouse_scroll(int direction) {
    for (const  auto item: EventListener::EventMatrix[en_mouse_scroll]){
        bool stop = item.second->mouse_scroll(direction);

        if(stop && EventListener::captureEvent[en_mouse_scroll]){
            break;
        }
    }
}

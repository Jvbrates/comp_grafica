#include "Frames.h"

struct alarm
{
    std::shared_ptr<bool> value = std::make_shared<bool>(false);
    clock_t expire_at;

    alarm(clock_t t): expire_at(t) {};
    alarm(clock_t t, std::shared_ptr<bool> v):value(v),expire_at(t) {};


};

std::vector<alarm_t> Frames::alarms = std::vector<alarm_t>();

//Incialização
clock_t Frames::t1 = clock();
clock_t Frames::t2 = Frames::t1;
long Frames::cont_frames = 0;
float Frames::fps_old = 20.f;
float Frames::fps = 0.f;

void Frames::updateAlarms(clock_t time)
{
    for(auto i = Frames::alarms.begin(); i != Frames::alarms.end();)
    {
        if(i->expire_at <= time)
        {
            *(i->value) = true;
            i = Frames::alarms.erase(i);
        }
        else
        {
            break;
        }
    }
}

float Frames::getFrames()
{
    return Frames::fps_old;
}

float Frames::updateFrames()
{
    double tempo;

    t2 = clock();

    Frames::updateAlarms(t2);

    tempo  = (double)(t2 - t1);  //milisegundos
    cont_frames++;
    //apos UPDATE_RATE milisegundos, atualiza o framerate
    if( tempo > UPDATE_RATE )
    {
        t1 = t2;
        fps = cont_frames / (tempo/CLOCKS_PER_SEC);
        cont_frames = 0;
        fps_old = fps;

        return fps;
    }
    //se nao foi decorrido UPDATE_RATE milisegundos, retorna a taxa antiga
    return fps_old;
}

std::shared_ptr<bool> Frames::makeAlarm(clock_t t)
{
    auto new_alarm = alarm_t(clock() + t);

    Frames::alarms.push_back(new_alarm);

    return new_alarm.value;
};


void Frames::makeAlarm(clock_t t, std::shared_ptr<bool> v)
{
    auto new_alarm = alarm_t(clock() + t, v);

    Frames::alarms.push_back(new_alarm);

};

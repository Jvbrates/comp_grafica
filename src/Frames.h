
#ifndef _FRAMES_H___
#define _FRAMES_H___

/*
    Mantêm o calculo do FPS e implementa "alarmes"
    "alarmes": Após determinado tempo, torna uma variável booleana compartilhada true;
*/


#include <time.h>
#include <vector>
#include <memory>
#include <iostream>

#define UPDATE_RATE 30   //milisegundos
#define SECOND 1000   //1 segundo


typedef struct alarm alarm_t;

class Frames
{

    private:
        static clock_t t1;
        static clock_t t2;
        static long cont_frames;
        static float   fps, fps_old;
        static std::vector<alarm_t> alarms ;
        static void updateAlarms(clock_t t);

    public:
        static float updateFrames();
        static void makeAlarm(clock_t t, std::shared_ptr<bool> v);
        static float getFrames();
        static std::shared_ptr<bool> makeAlarm(clock_t t);

};

#endif

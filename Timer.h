#ifndef GET_TIMER_H
#define GET_TIMER_H
#include <SDL.h>
class Timer{
public :
    Timer();
    ~Timer();


    void start();
    void stop();
    void paused();
    void unpaused();

    int get_tick();

    bool is_started();
    bool is_paused();

private:
    int start_run;
    int pause_run;


    bool is_paused_;
    bool is_started_;

};
#endif // GET_TIMER_H

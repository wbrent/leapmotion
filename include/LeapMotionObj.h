#ifndef LEAP_H
#define LEAP_H
#include "Leap.h"
#endif

#ifndef DISPATCHER_H
#define DISPATCHER_H
#include "Dispatcher.h"
#endif

class LeapMotionObj
{

public:

    LeapMotionObj();
    ~LeapMotionObj();

    Dispatcher m_dispatcher;
    Leap::Controller m_controller;

};

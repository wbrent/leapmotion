#ifndef LEAP_MOTION_OBJ_H
#define LEAP_MOTION_OBJ_H

#include "Leap.h"

#include "Dispatcher.h"

class LeapMotionObj
{

public:

    LeapMotionObj();
    ~LeapMotionObj();

    Dispatcher m_dispatcher;
    Leap::Controller m_controller;

};

#endif // LEAP_MOTION_OBJ_H

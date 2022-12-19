#ifndef PD_H
#define PD_H
#include "m_pd.h"
#endif

#ifndef LEAP_H
#define LEAP_H
#include "Leap.h"
#endif

class Dispatcher : public Leap::Listener
{

public:

    Leap::Frame frame;

    void onInit (const Leap::Controller&);
    void onConnect (const Leap::Controller&);
    void onDisconnect (const Leap::Controller&);
    void onExit (const Leap::Controller&);
    void onFrame (const Leap::Controller&);

};

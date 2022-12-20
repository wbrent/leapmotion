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

    virtual void onInit (const Leap::Controller&);
    virtual void onConnect (const Leap::Controller&);
    virtual void onDisconnect (const Leap::Controller&);
    virtual void onExit (const Leap::Controller&);
    virtual void onFrame (const Leap::Controller&);

};

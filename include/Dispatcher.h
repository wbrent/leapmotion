#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "m_pd.h"
#include "Leap.h"

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

#endif

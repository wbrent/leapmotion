#include "Dispatcher.h"

void Dispatcher::onInit (const Leap::Controller& controller)
{
    post ("Leap Motion Controller: Initialized");
}

void Dispatcher::onConnect (const Leap::Controller& controller)
{
    post ("Leap Motion Controller: Connected");
}

void Dispatcher::onDisconnect (const Leap::Controller& controller)
{
    post ("Leap Motion Controller: Disconnected");
}

void Dispatcher::onExit (const Leap::Controller& controller)
{
    post ("Leap Motion Controller: Exited");
}

void Dispatcher::onFrame (const Leap::Controller& controller)
{
    frame = controller.frame();
}

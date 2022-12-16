#include "Dispatcher.h"

void Dispatcher::onInit (const Leap::Controller& controller)
{
    post ("LEAP device: Initialized");
    isConnected = false;
}

void Dispatcher::onConnect (const Leap::Controller& controller)
{
    post ("LEAP device: Connected");
    isConnected = true;
}

void Dispatcher::onDisconnect (const Leap::Controller& controller)
{
    post ("LEAP device: Disconnected");
    isConnected = false;
}

void Dispatcher::onExit (const Leap::Controller& controller)
{
    post ("LEAP device: Exited");
}

void Dispatcher::onFrame (const Leap::Controller& controller)
{
    frame = controller.frame();
}

#include "Dispatcher.h"

void Dispatcher::onInit (const Leap::Controller& controller)
{
    post ("Leap Motion Listener: Initialized");
}

void Dispatcher::onServiceConnect (const Leap::Controller& controller)
{
    post ("Leap Motion Service: Connected");

    // we attempted to set the policy POLICY_BACKGROUND_FRAMES in the LeapMotionObj constructor. once we actually connect to LEAP service, we should check that the policy change was successful.
    if (controller.isPolicySet(Leap::Controller::POLICY_BACKGROUND_FRAMES))
        post ("Leap Motion POLICY_BACKGROUND_FRAMES set successfully");
    else
        post ("\nLeap Motion POLICY_BACKGROUND_FRAMES failed. Is \"Allow Background Apps\" activated in LEAP general settings?\n");
}

void Dispatcher::onServiceChange (const Leap::Controller& controller)
{
    post ("Leap Motion Service: Changed");
}

void Dispatcher::onServiceDisconnect (const Leap::Controller& controller)
{
    post ("Leap Motion Service: Disconnected");
}

void Dispatcher::onConnect (const Leap::Controller& controller)
{
    Leap::DeviceList deviceList = controller.devices();
    int numDevices = deviceList.count();

    for (int d = 0; d < numDevices; d++)
        post ("Leap Motion %s", deviceList[d].toString().c_str());
}

void Dispatcher::onDisconnect (const Leap::Controller& controller)
{
    Leap::DeviceList deviceList = controller.devices();
    int numDevices = deviceList.count();

    for (int d = 0; d < numDevices; d++)
        post ("Leap Motion %s", deviceList[d].toString().c_str());
}

void Dispatcher::onExit (const Leap::Controller& controller)
{
    post ("Leap Motion Controller: Exited");
}

void Dispatcher::onFocusGained (const Leap::Controller& controller)
{
    post ("Leap Motion Controller: Focus gained");
}

void Dispatcher::onFocusLost (const Leap::Controller& controller)
{
    post ("Leap Motion Controller: Focus lost");
}

void Dispatcher::onFrame (const Leap::Controller& controller)
{
    frame = controller.frame();
}

#include "LeapMotionObj.h"

LeapMotionObj::LeapMotionObj()
{
    // on some Windows systems, application focus awareness can fail. this policy allows LEAP tracking data to flow to Pd even if Pd is not the foreground application. note that "Allow Background Apps" must be enabled in LEAP general settings for this to work.
    m_controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
    m_controller.addListener (m_dispatcher);
}

LeapMotionObj::~LeapMotionObj()
{
    m_controller.removeListener (m_dispatcher);
}

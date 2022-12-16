#include "LeapMotionObj.h"

LeapMotionObj::LeapMotionObj()
{
    m_controller.addListener (m_dispatcher);
}

LeapMotionObj::~LeapMotionObj()
{
    m_controller.removeListener (m_dispatcher);
}

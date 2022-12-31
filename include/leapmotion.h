// this project is built against Leap SDK 2.3.1+31549, and should be linked with the same version of libLeap.so, libLeap.dylib, or leap.lib

#ifndef LEAPMOTION_H
#define LEAPMOTION_H

#include "m_pd.h"
#include "Leap.h"

#include "LeapMotionObj.h"
#include "Dispatcher.h"

#define PD_LEAPMOTION_VERSION "version 0.2.3"
#define PD_LEAPMOTION_RELEASE_DATE "Dec 2022"

static t_class* leapmotion_class;

typedef struct _leapmotion
{
    t_object x_obj;
    t_symbol* x_objSymbol;
    LeapMotionObj* x_leapMotionObjPtr;
    int64_t x_timeStampReference;

    uint8_t x_iBoxNormalize;
    uint8_t x_gestureCountFlag;

    uint8_t x_handsArmCenterFlag;
    uint8_t x_handsArmDirectionFlag;
    uint8_t x_handsArmElbowPositionFlag;
    uint8_t x_handsArmWristPositionFlag;
    uint8_t x_handsArmWidthFlag;
    uint8_t x_handsTypeFlag;
    uint8_t x_handsSphereRadiusFlag;
    uint8_t x_handsSphereCenterFlag;
    uint8_t x_handsDirectionFlag;
    uint8_t x_handsPalmNormalFlag;
    uint8_t x_handsPalmPositionFlag;
    uint8_t x_handsStabilizedPalmPositionFlag;
    uint8_t x_handsPalmVelocityFlag;
    uint8_t x_handsPalmWidthFlag;
    uint8_t x_handsFingerCountFlag;
    uint8_t x_handsToolCountFlag;
    uint8_t x_handsGrabStrengthFlag;
    uint8_t x_handsPinchStrengthFlag;
    uint8_t x_handsTimeVisibleFlag;

    uint8_t x_fingersTypeFlag;
    uint8_t x_fingersDirectionFlag;
    uint8_t x_fingersPositionFlag;
    uint8_t x_fingersVelocityFlag;
    uint8_t x_fingersSizeFlag;
    uint8_t x_fingersIsExtendedFlag;

    uint8_t x_toolsDirectionFlag;
    uint8_t x_toolsPositionFlag;
    uint8_t x_toolsVelocityFlag;
    uint8_t x_toolsSizeFlag;

    uint8_t x_generalFlag;

    t_outlet* x_outletGeneral;
    t_outlet* x_outletHandsFingersTools;
    t_outlet* x_outletGesture;
} t_leapmotion;


// object setup functions
static void* leapmotion_new (t_symbol* s, int argc, t_atom* argv);
static void leapmotion_free (t_leapmotion* x);
extern "C" {void leapmotion_setup (void);}
// since some pure C libraries are not written with explicit C++ support, the C++ compiler will not be able to find the leapmotion setup function unless we forward declare the function as extern "C"


// set methods: general
static void leapmotionSetGeneralFlag (t_leapmotion* x, t_float state);

// set methods: interaction box normalization
static void leapmotionSetInteractionBoxNormalize (t_leapmotion* x, t_float state);

// set methods: hands
static void leapmotionSetHandsArmCenterFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsArmDirectionFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsArmElbowPositionFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsArmWristPositionFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsArmWidthFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsTypeFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsSphereRadiusFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsSphereCenterFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsDirectionFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsPalmNormalFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsPalmPositionFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsStabilizedPalmPositionFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsPalmVelocityFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsPalmWidthFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsFingerCountFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsToolCountFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsGrabStrengthFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsPinchStrengthFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsTimeVisibleFlag (t_leapmotion* x, t_float state);

// set methods: fingers
static void leapmotionSetFingerTypeFlag (t_leapmotion* x, t_float state);
static void leapmotionSetFingerDirectionFlag (t_leapmotion* x, t_float state);
static void leapmotionSetFingerPositionFlag (t_leapmotion* x, t_float state);
static void leapmotionSetFingerVelocityFlag (t_leapmotion* x, t_float state);
static void leapmotionSetFingerSizeFlag (t_leapmotion* x, t_float state);
static void leapmotionSetFingerIsExtendedFlag (t_leapmotion* x, t_float state);

// set methods: tools
static void leapmotionSetToolsDirectionFlag (t_leapmotion* x, t_float state);
static void leapmotionSetToolsPositionFlag (t_leapmotion* x, t_float state);
static void leapmotionSetToolsVelocityFlag (t_leapmotion* x, t_float state);
static void leapmotionSetToolsSizeFlag (t_leapmotion* x, t_float state);

// set methods: gestures
static void leapmotionSetGestureCountFlag (t_leapmotion* x, t_float state);
static void leapmotionSetGestureFlags (t_leapmotion* x, t_symbol* s, int argc, t_atom* argv);
static void leapmotionSetGestureConfig (t_leapmotion* x, t_symbol* key, t_float value);

// post object info
static void leapmotionInfo (t_leapmotion* x);

// reset the timestamp
static void leapmotionResetTimeStamp (t_leapmotion* x);

// poll LEAP device
static void leapmotionPoll (t_leapmotion* x);

// sub-routinese to extract data from a Leap::Frame
static void leapmotionProcessGestures (t_leapmotion* x, Leap::Frame frame);
static void leapmotionProcessArm (t_leapmotion* x, int handIdx, Leap::Hand hand, Leap::InteractionBox interactionBox);
static void leapmotionProcessHands (t_leapmotion* x, Leap::Frame frame);
static void leapmotionProcessFingers (t_leapmotion* x, int handIdx, Leap::FingerList fingerList, Leap::InteractionBox interactionBox);
static void leapmotionProcessTools (t_leapmotion* x, Leap::Frame frame);
static void leapmotionProcessGeneral (t_leapmotion* x, Leap::Frame frame);

#endif // LEAPMOTION_H

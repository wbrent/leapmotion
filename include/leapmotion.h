// this project is built against LeapDeveloperKit_2.3.1+31549_mac, and requires the same version of libLeap.dylib

#ifndef PD_H
#define PD_H
#include "m_pd.h"
#endif

#ifndef LEAP_H
#define LEAP_H
#include "Leap.h"
#endif

#ifndef DISPATCHER_H
#define DISPATCHER_H
#include "Dispatcher.h"
#endif

#ifndef LEAP_MOTION_OBJ_H
#define LEAP_MOTION_OBJ_H
#include "LeapMotionObj.h"
#endif

#define PDLEAPMOTION_VERSION "version 0.2.0"

static t_class* leapmotion_class;

typedef struct _leapmotion
{
    t_object x_obj;
    t_symbol* x_objSymbol;
    LeapMotionObj* x_leapMotionObjPtr;

    t_float x_handsTypeFlag;
    t_float x_handsSphereRadiusFlag;
    t_float x_handsSphereCenterFlag;
    t_float x_handsDirectionFlag;
    t_float x_handsPalmNormalFlag;
    t_float x_handsPalmPositionFlag;
    t_float x_handsPalmVelocityFlag;
    t_float x_handsFingerCountFlag;
    t_float x_handsToolCountFlag;

    t_float x_fingersDirectionFlag;
    t_float x_fingersPositionFlag;
    t_float x_fingersVelocityFlag;
    t_float x_fingersSizeFlag;

    t_float x_toolsDirectionFlag;
    t_float x_toolsPositionFlag;
    t_float x_toolsVelocityFlag;
    t_float x_toolsSizeFlag;

    t_float x_generalFlag;

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

// set methods: hands
static void leapmotionSetHandsTypeFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsSphereRadiusFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsSphereCenterFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsDirectionFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsPalmNormalFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsPalmPositionFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsPalmVelocityFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsFingerCountFlag (t_leapmotion* x, t_float state);
static void leapmotionSetHandsToolCountFlag (t_leapmotion* x, t_float state);

// set methods: fingers
static void leapmotionSetFingersDirectionFlag (t_leapmotion* x, t_float state);
static void leapmotionSetFingersPositionFlag (t_leapmotion* x, t_float state);
static void leapmotionSetFingersVelocityFlag (t_leapmotion* x, t_float state);
static void leapmotionSetFingersSizeFlag (t_leapmotion* x, t_float state);

// set methods: tools
static void leapmotionSetToolsDirectionFlag (t_leapmotion* x, t_float state);
static void leapmotionSetToolsPositionFlag (t_leapmotion* x, t_float state);
static void leapmotionSetToolsVelocityFlag (t_leapmotion* x, t_float state);
static void leapmotionSetToolsSizeFlag (t_leapmotion* x, t_float state);

// set methods: gestures
static void leapmotionSetGestureFlags (t_leapmotion* x, t_symbol* s, int argc, t_atom* argv);

// post object info
static void leapmotionInfo (t_leapmotion* x);

// poll LEAP device
static void leapmotionPoll (t_leapmotion* x);

// sub-routinese to extract data from a Leap::Frame
static void leapmotionProcessGestures(t_leapmotion* x, Leap::Frame frame);
static void leapmotionProcessHands(t_leapmotion* x, Leap::Frame frame);
static void leapmotionProcessFingers(t_leapmotion* x, Leap::Frame frame, int handIdx, Leap::FingerList fingerList);
static void leapmotionProcessTools(t_leapmotion* x, Leap::Frame frame);
static void leapmotionProcessGeneral(t_leapmotion* x, Leap::Frame frame);

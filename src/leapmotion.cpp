#include "leapmotion.h"

// constructor
static void* leapmotion_new (t_symbol* s, int argc, t_atom* argv)
{
    t_leapmotion* x = (t_leapmotion*) pd_new (leapmotion_class);

    x->x_outletGeneral = outlet_new (&x->x_obj, &s_list);
  	x->x_outletHandsFingersTools = outlet_new (&x->x_obj, &s_list);
  	x->x_outletGesture = outlet_new (&x->x_obj, &s_list);

    x->x_objSymbol = s;

    // create the LeapMotionObj instance and store a pointer to it
    x->x_leapMotionObjPtr = new LeapMotionObj;

    x->x_generalFlag = 1.0;

    x->x_handsSphereRadiusFlag = 0.0;
    x->x_handsSphereCenterFlag = 0.0;
    x->x_handsDirectionFlag = 0.0;
    x->x_handsPalmNormalFlag = 0.0;
    x->x_handsPalmPositionFlag = 1.0;
    x->x_handsPalmVelocityFlag = 0.0;
    x->x_handsFingerCountFlag = 0.0;
    x->x_handsToolCountFlag = 0.0;

    x->x_fingersDirectionFlag = 0.0;
    x->x_fingersPositionFlag = 0.0;
    x->x_fingersVelocityFlag = 0.0;
    x->x_fingersSizeFlag = 0.0;

    x->x_toolsDirectionFlag = 0.0;
    x->x_toolsPositionFlag = 0.0;
    x->x_toolsVelocityFlag = 0.0;
    x->x_toolsSizeFlag = 0.0;

    post ("\n****************");
    post ("[leapmotion] for Pd %s", PDLEAPMOTION_VERSION);
    post ("Based on version 0.1 by Chikashi Miyama");
    post ("Updated by William Brent (Dec 2022)");
    post ("****************\n");

    return (void*) x;
}

// destructor
static void leapmotion_free (t_leapmotion* x)
{
    // must delete the LeapMotionObj we created in _new()
    delete x->x_leapMotionObjPtr;
}

// object initialization
void leapmotion_setup (void)
{
    // call class_new to get a pointer to this object
    leapmotion_class = (t_class*) class_new (
        gensym ("leapmotion"),
        (t_newmethod) leapmotion_new, // new method
        (t_method) leapmotion_free, // free method
        sizeof (t_leapmotion),
        CLASS_DEFAULT,
        A_GIMME,
        0
    );


    // info
    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionInfo,
        gensym ("info"),
        A_NULL
    );


    // poll
    class_addbang (
        leapmotion_class,
        (t_method) leapmotionPoll
    );


    // set meethods
    // general
    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetGeneralFlag,
        gensym ("general"),
        A_DEFFLOAT,
        A_NULL
    );


    // hands
    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsSphereRadiusFlag,
        gensym ("hands_sphere_radius"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsSphereCenterFlag,
        gensym ("hands_sphere_center"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsDirectionFlag,
        gensym ("hands_direction"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsPalmNormalFlag,
        gensym ("hands_palm_normal"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsPalmPositionFlag,
        gensym ("hands_palm_position"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsPalmVelocityFlag,
        gensym ("hands_palm_velocity"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsFingerCountFlag,
        gensym ("hands_finger_count"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsToolCountFlag,
        gensym ("hands_tool_count"),
        A_DEFFLOAT,
        A_NULL
    );


    // fingers
    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetFingersDirectionFlag,
        gensym ("fingers_direction"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetFingersPositionFlag,
        gensym ("fingers_position"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetFingersVelocityFlag,
        gensym ("fingers_velocity"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetFingersSizeFlag,
        gensym ("fingers_size"),
        A_DEFFLOAT,
        A_NULL
    );


    // tools
    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetToolsDirectionFlag,
        gensym ("tools_direction"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetToolsPositionFlag,
        gensym ("tools_position"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetToolsVelocityFlag,
        gensym ("tools_velocity"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetToolsSizeFlag,
        gensym ("tools_size"),
        A_DEFFLOAT,
        A_NULL
    );


    // gestures
    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetGestureFlags,
        gensym ("gestures"),
        A_GIMME,
        A_NULL
    );
}


// set methods: general
static void leapmotionSetGeneralFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_generalFlag = state;
}


// set methods: hands
static void leapmotionSetHandsSphereRadiusFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_handsSphereRadiusFlag = state;
}

static void leapmotionSetHandsSphereCenterFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_handsSphereCenterFlag = state;
}

static void leapmotionSetHandsDirectionFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_handsDirectionFlag = state;
}

static void leapmotionSetHandsPalmNormalFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_handsPalmNormalFlag = state;
}

static void leapmotionSetHandsPalmPositionFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_handsPalmPositionFlag = state;
}

static void leapmotionSetHandsPalmVelocityFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_handsPalmVelocityFlag = state;
}

static void leapmotionSetHandsFingerCountFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_handsFingerCountFlag = state;
}

static void leapmotionSetHandsToolCountFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_handsToolCountFlag = state;
}

// set methods: fingers
static void leapmotionSetFingersDirectionFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_fingersDirectionFlag = state;
}

static void leapmotionSetFingersPositionFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_fingersPositionFlag = state;
}

static void leapmotionSetFingersVelocityFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_fingersVelocityFlag = state;
}

static void leapmotionSetFingersSizeFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_fingersSizeFlag = state;
}

// set methods: tools
static void leapmotionSetToolsDirectionFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_toolsDirectionFlag = state;
}

static void leapmotionSetToolsPositionFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_toolsPositionFlag = state;
}

static void leapmotionSetToolsVelocityFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_toolsVelocityFlag = state;
}

static void leapmotionSetToolsSizeFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_toolsSizeFlag = state;
}


// set methods: gestures
static void leapmotionSetGestureFlags (t_leapmotion* x, t_symbol* s, int argc, t_atom* argv)
{
    if (argc > 2)
    {
        pd_error (x, "[%s]: too many arguments passed to gestures method", x->x_objSymbol->s_name);
        return;
    }
    else if (argc < 2)
    {
        pd_error (x, "[%s]: too few arguments passed to gestures method", x->x_objSymbol->s_name);
        return;
    }
    else
    {
        if ((argv[0].a_type != A_SYMBOL) || (argv[1].a_type != A_FLOAT))
        {
            pd_error (x, "[%s]: wrong argument types passed to gestures method", x->x_objSymbol->s_name);
            return;
        }

        const char* type = argv[0].a_w.w_symbol->s_name;
        t_float state = argv[1].a_w.w_float;

        state = (state < 0.0) ? 0.0 : state;
        state = (state > 1.0) ? 1.0 : state;

        if (! strcmp (type, "TYPE_CIRCLE"))
        {
            if (state)
                x->x_leapMotionObjPtr->m_controller.enableGesture (Leap::Gesture::TYPE_CIRCLE, true);
            else
                x->x_leapMotionObjPtr->m_controller.enableGesture (Leap::Gesture::TYPE_CIRCLE, false);
        }

        if (! strcmp (type, "TYPE_SWIPE"))
        {
            if (state)
                x->x_leapMotionObjPtr->m_controller.enableGesture (Leap::Gesture::TYPE_SWIPE, true);
            else
                x->x_leapMotionObjPtr->m_controller.enableGesture (Leap::Gesture::TYPE_SWIPE, false);
        }

        if (! strcmp (type, "TYPE_KEY_TAP"))
        {
            if (state)
                x->x_leapMotionObjPtr->m_controller.enableGesture (Leap::Gesture::TYPE_KEY_TAP, true);
            else
                x->x_leapMotionObjPtr->m_controller.enableGesture (Leap::Gesture::TYPE_KEY_TAP, false);
        }

        if (! strcmp (type, "TYPE_SCREEN_TAP"))
        {
            if (state)
                x->x_leapMotionObjPtr->m_controller.enableGesture (Leap::Gesture::TYPE_SCREEN_TAP, true);
            else
                x->x_leapMotionObjPtr->m_controller.enableGesture (Leap::Gesture::TYPE_SCREEN_TAP, false);
        }
    }
}


// info method
static void leapmotionInfo (t_leapmotion* x)
{
    post ("\n\n[leapmotion] %s\n", PDLEAPMOTION_VERSION);

    post ("general: %1.0f\n", x->x_generalFlag);

    post ("hands_sphere_radius: %1.0f", x->x_handsSphereRadiusFlag);
    post ("hands_sphere_center: %1.0f", x->x_handsSphereCenterFlag);
    post ("hands_direction: %1.0f", x->x_handsDirectionFlag);
    post ("hands_palm_normal: %1.0f", x->x_handsPalmNormalFlag);
    post ("hands_palm_position: %1.0f", x->x_handsPalmPositionFlag);
    post ("hands_palm_velocity: %1.0f", x->x_handsPalmVelocityFlag);
    post ("hands_tool_count: %1.0f", x->x_handsToolCountFlag);
    post ("hands_finger_count: %1.0f\n", x->x_handsFingerCountFlag);

    post ("fingers_direction: %1.0f", x->x_fingersDirectionFlag);
    post ("fingers_position: %1.0f", x->x_fingersPositionFlag);
    post ("fingers_velocity: %1.0f", x->x_fingersVelocityFlag);
    post ("fingers_size: %1.0f\n", x->x_fingersSizeFlag);

    post ("tools_direction: %1.0f", x->x_toolsDirectionFlag);
    post ("tools_position: %1.0f", x->x_toolsPositionFlag);
    post ("tools_velocity: %1.0f", x->x_toolsVelocityFlag);
    post ("tools_size: %1.0f\n", x->x_toolsSizeFlag);

    // need to post state as an integer based on isGestureEnabled return type
    post ("gestures/TYPE_CIRCLE: %i", x->x_leapMotionObjPtr->m_controller.isGestureEnabled (Leap::Gesture::TYPE_CIRCLE));
    post ("gestures/TYPE_SWIPE: %i", x->x_leapMotionObjPtr->m_controller.isGestureEnabled (Leap::Gesture::TYPE_SWIPE));
    post ("gestures/TYPE_KEY_TAP: %i", x->x_leapMotionObjPtr->m_controller.isGestureEnabled (Leap::Gesture::TYPE_KEY_TAP));
    post ("gestures/TYPE_SCREEN_TAP: %i\n\n", x->x_leapMotionObjPtr->m_controller.isGestureEnabled (Leap::Gesture::TYPE_SCREEN_TAP));
}


// poll method
static void leapmotionPoll (t_leapmotion* x)
{
    Leap::Frame frame;
    Dispatcher dispatcher;
    int numHandsPerFrame, numFingersPerFrame, numToolsPerFrame, numGesturesPerFrame;
    int numGestureCountAtoms = 2;
    t_atom gestureCountInfo[numGestureCountAtoms];

    dispatcher = x->x_leapMotionObjPtr->m_dispatcher;

    if (! dispatcher.isConnected)
    {
        pd_error(x, "[%s]: no LEAP device connected!", x->x_objSymbol->s_name);
        return;
    }

    frame = dispatcher.frame;

    numHandsPerFrame = frame.hands().count();
    // from LeapSDK/docs/cpp/devguide/Leap_Pointables.html: "As of version 2.0 of the Leap Motion SDK, all five fingers are are always present in the list of fingers for a hand."
    // therefore, Leap::FingerList.count() will not work as it did in the previous SDK. can use Leap::Finger.isExtended() to determine which ones are actually out.
    numFingersPerFrame = frame.fingers().count();
    // TODO: perhaps remove the general frame finger count entirely? it doesn't really provide any new information since each hand will always have a finger count of 5. can use the hand finger count to actually check whether each finger in the list isExtended().
    numToolsPerFrame = frame.tools().count();
    numGesturesPerFrame = frame.gestures().count();

    SETSYMBOL (&gestureCountInfo[0], gensym ("count"));
    SETFLOAT (&gestureCountInfo[1], (t_float) numGesturesPerFrame);
    outlet_list(x->x_outletGesture, 0, numGestureCountAtoms, &gestureCountInfo[0]);

    // gestures
    for (int gestureIdx = 0; gestureIdx < numGesturesPerFrame; gestureIdx++)
    {
        Leap::Gesture gesture;
        gesture = frame.gestures()[gestureIdx];

        int numAtoms = 3;
        t_atom gestureTypeInfo[numAtoms];
        t_atom gestureStateInfo[numAtoms];
        t_atom gestureDurationInfo[numAtoms];
        t_atom gestureIdInfo[numAtoms];

        SETFLOAT (&gestureTypeInfo[0], gestureIdx);
        SETSYMBOL (&gestureTypeInfo[1], gensym ("type"));

        switch (gesture.type())
        {
            case Leap::Gesture::TYPE_INVALID:
                SETSYMBOL (&gestureTypeInfo[2], gensym ("TYPE_INVALID"));
                break;
            case Leap::Gesture::TYPE_SWIPE:
                SETSYMBOL (&gestureTypeInfo[2], gensym ("TYPE_SWIPE"));
                break;
            case Leap::Gesture::TYPE_CIRCLE:
                SETSYMBOL (&gestureTypeInfo[2], gensym ("TYPE_CIRCLE"));
                break;
            case Leap::Gesture::TYPE_SCREEN_TAP:
                SETSYMBOL (&gestureTypeInfo[2], gensym ("TYPE_SCREEN_TAP"));
                break;
            case Leap::Gesture::TYPE_KEY_TAP:
                SETSYMBOL (&gestureTypeInfo[2], gensym ("TYPE_KEY_TAP"));
                break;
        }

        outlet_list(x->x_outletGesture, 0, numAtoms, &gestureTypeInfo[0]);

        //state
        SETFLOAT (&gestureStateInfo[0], gestureIdx);
        SETSYMBOL (&gestureStateInfo[1], gensym ("state"));

        switch(gesture.state())
        {
            case Leap::Gesture::STATE_INVALID:
                SETSYMBOL (&gestureStateInfo[2], gensym ("STATE_INVALID"));
                break;
            case Leap::Gesture::STATE_START:
                SETSYMBOL (&gestureStateInfo[2], gensym ("TYPE_START"));
                break;
            case Leap::Gesture::STATE_UPDATE:
                SETSYMBOL (&gestureStateInfo[2], gensym ("STATE_UPDATE"));
                break;
            case Leap::Gesture::STATE_STOP:
                SETSYMBOL (&gestureStateInfo[2], gensym ("TYPE_STOP"));
                break;
        }

        outlet_list(x->x_outletGesture, 0, numAtoms, &gestureStateInfo[0]);

        SETFLOAT (&gestureDurationInfo[0], gestureIdx);
        SETSYMBOL (&gestureDurationInfo[1], gensym ("duration"));
        SETFLOAT (&gestureDurationInfo[2], gesture.duration());

        outlet_list(x->x_outletGesture, 0, numAtoms, &gestureDurationInfo[0]);

        SETFLOAT (&gestureIdInfo[0], gestureIdx);
        SETSYMBOL (&gestureIdInfo[1], gensym ("id"));
        SETFLOAT (&gestureIdInfo[2], gesture.id());

        outlet_list(x->x_outletGesture, 0, numAtoms, &gestureIdInfo[0]);
    }

    // hands and fingers
    for (int handIdx = 0; handIdx < numHandsPerFrame; handIdx++)
    {
        int numAtoms = 5;
        t_atom handInfo[numAtoms];

        Leap::Hand hand;
        int numFingersPerHand, numToolsPerHand;

        hand = frame.hands()[handIdx];
        // from LeapSDK/docs/cpp/devguide/Leap_Pointables.html: "As of version 2.0 of the Leap Motion SDK, all five fingers are are always present in the list of fingers for a hand."
        // therefore, Leap::FingerList.count() will not work as it did in the previous SDK. can use Leap::Finger.isExtended() to determine which ones are actually out.
        numFingersPerHand = hand.fingers().count();
        numToolsPerHand = hand.tools().count();

        // sphere radius
        if (x->x_handsSphereRadiusFlag)
        {
            // sphere radius
            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("sphere_radius"));
            SETFLOAT (&handInfo[2], hand.sphereRadius());

            outlet_anything(x->x_outletHandsFingersTools, gensym ("hand"), 3, handInfo);
        }

        // sphere center
        if (x->x_handsSphereCenterFlag)
        {
            // sphere center
            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("sphere_center"));
            SETFLOAT (&handInfo[2], hand.sphereCenter().x);
            SETFLOAT (&handInfo[3], hand.sphereCenter().y);
            SETFLOAT (&handInfo[4], hand.sphereCenter().z);

            outlet_anything(x->x_outletHandsFingersTools, gensym ("hand"), numAtoms, handInfo);
        }

        // direction
        if (x->x_handsDirectionFlag)
        {
            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("direction"));
            SETFLOAT (&handInfo[2], hand.direction().x);
            SETFLOAT (&handInfo[3], hand.direction().y);
            SETFLOAT (&handInfo[4], hand.direction().z);

            outlet_anything(x->x_outletHandsFingersTools, gensym ("hand"), numAtoms, handInfo);
        }

        // palm normal
        if (x->x_handsPalmNormalFlag)
        {
            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("palm_normal"));
            SETFLOAT (&handInfo[2], hand.palmNormal().x);
            SETFLOAT (&handInfo[3], hand.palmNormal().y);
            SETFLOAT (&handInfo[4], hand.palmNormal().z);

            outlet_anything(x->x_outletHandsFingersTools, gensym ("hand"), numAtoms, handInfo);
        }

        // palm position
        if (x->x_handsPalmPositionFlag)
        {
            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("palm_position"));
            SETFLOAT (&handInfo[2], hand.palmPosition().x);
            SETFLOAT (&handInfo[3], hand.palmPosition().y);
            SETFLOAT (&handInfo[4], hand.palmPosition().z);

            outlet_anything(x->x_outletHandsFingersTools, gensym ("hand"), numAtoms, handInfo);
        }

        // palm velocity
        if (x->x_handsPalmVelocityFlag)
        {
            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("palm_velocity"));
            SETFLOAT (&handInfo[2], hand.palmVelocity().x);
            SETFLOAT (&handInfo[3], hand.palmVelocity().y);
            SETFLOAT (&handInfo[4], hand.palmVelocity().z);

            outlet_anything(x->x_outletHandsFingersTools, gensym ("hand"), numAtoms, handInfo);
        }

        // finger count
        if (x->x_handsFingerCountFlag)
        {
            int fingerCount = 0;

            for (int fingerIdx = 0; fingerIdx < numFingersPerHand; fingerIdx++)
            {
                Leap::Finger finger;
                finger = hand.fingers()[fingerIdx];

                fingerCount += finger.isExtended();
            }

            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("finger_count"));
            SETFLOAT (&handInfo[2], fingerCount);

            outlet_anything(x->x_outletHandsFingersTools, gensym ("hand"), 3, handInfo);
        }

        // tool count
        if (x->x_handsToolCountFlag)
        {
            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("tool_count"));
            SETFLOAT (&handInfo[2], numToolsPerHand);

            outlet_anything(x->x_outletHandsFingersTools, gensym ("hand"), 3, handInfo);
        }

        // fingers per hand
        for (int fingerIdx = 0; fingerIdx < numFingersPerHand; fingerIdx++)
        {
            Leap::Finger finger;
            finger = hand.fingers()[fingerIdx];
            int numFingerAtoms = 7;
            t_atom fingerInfo[numFingerAtoms];

            if (x->x_fingersDirectionFlag)
            {
                SETFLOAT (&fingerInfo[0], handIdx);
                SETSYMBOL (&fingerInfo[1], gensym ("fingers"));
                // use Leap::Finger.type() to get stable finger indices where 0 is the thumb, and 4 is the pinky
                SETFLOAT (&fingerInfo[2], finger.type());
                SETSYMBOL (&fingerInfo[3], gensym ("direction"));
                SETFLOAT (&fingerInfo[4], finger.direction().x);
                SETFLOAT (&fingerInfo[5], finger.direction().y);
                SETFLOAT (&fingerInfo[6], finger.direction().z);

                outlet_anything(x->x_outletHandsFingersTools, gensym ("hand"), numFingerAtoms, fingerInfo);
            }

            if (x->x_fingersPositionFlag)
            {
                SETFLOAT (&fingerInfo[0], handIdx);
                SETSYMBOL (&fingerInfo[1], gensym ("fingers"));
                SETFLOAT (&fingerInfo[2], fingerIdx);
                SETSYMBOL (&fingerInfo[3], gensym ("position"));
                SETFLOAT (&fingerInfo[4], finger.tipPosition().x);
                SETFLOAT (&fingerInfo[5], finger.tipPosition().y);
                SETFLOAT (&fingerInfo[6], finger.tipPosition().z);

                outlet_anything(x->x_outletHandsFingersTools, gensym ("hand"), numFingerAtoms, fingerInfo);
            }

            if (x->x_fingersVelocityFlag)
            {
                SETFLOAT (&fingerInfo[0], handIdx);
                SETSYMBOL (&fingerInfo[1], gensym ("fingers"));
                SETFLOAT (&fingerInfo[2], fingerIdx);
                SETSYMBOL (&fingerInfo[3], gensym ("velocity"));
                SETFLOAT (&fingerInfo[4], finger.tipVelocity().x);
                SETFLOAT (&fingerInfo[5], finger.tipVelocity().y);
                SETFLOAT (&fingerInfo[6], finger.tipVelocity().z);

                outlet_anything(x->x_outletHandsFingersTools, gensym ("hand"), numFingerAtoms, fingerInfo);
            }

            if (x->x_fingersSizeFlag)
            {
                SETFLOAT (&fingerInfo[0], handIdx);
                SETSYMBOL (&fingerInfo[1], gensym ("fingers"));
                SETFLOAT (&fingerInfo[2], fingerIdx);
                SETSYMBOL (&fingerInfo[3], gensym ("size"));
                SETFLOAT (&fingerInfo[4], finger.width());
                SETFLOAT (&fingerInfo[5], finger.length());

                outlet_anything(x->x_outletHandsFingersTools, gensym ("hand"), numFingerAtoms - 1, fingerInfo);
            }
        }
    }

    // tools per frame
    for (int toolIdx = 0; toolIdx < numToolsPerFrame; toolIdx++)
    {
        int numAtoms = 5;
        t_atom toolInfo[numAtoms];

        Leap::Tool tool;
        tool = frame.tools()[toolIdx];

        if (x->x_toolsDirectionFlag)
        {
            SETFLOAT (&toolInfo[0], toolIdx);
            SETSYMBOL (&toolInfo[1], gensym ("direction"));
            SETFLOAT (&toolInfo[2], tool.direction().x);
            SETFLOAT (&toolInfo[3], tool.direction().y);
            SETFLOAT (&toolInfo[4], tool.direction().z);

            outlet_anything(x->x_outletHandsFingersTools, gensym ("tool"), numAtoms, toolInfo);
        }

        if (x->x_toolsPositionFlag)
        {
            SETFLOAT (&toolInfo[0], toolIdx);
            SETSYMBOL (&toolInfo[1], gensym ("position"));
            SETFLOAT (&toolInfo[2], tool.tipPosition().x);
            SETFLOAT (&toolInfo[3], tool.tipPosition().y);
            SETFLOAT (&toolInfo[4], tool.tipPosition().z);

            outlet_anything(x->x_outletHandsFingersTools, gensym ("tool"), numAtoms, toolInfo);
        }

        if (x->x_toolsVelocityFlag)
        {
            SETFLOAT (&toolInfo[0], toolIdx);
            SETSYMBOL (&toolInfo[1], gensym ("velocity"));
            SETFLOAT (&toolInfo[2], tool.tipVelocity().x);
            SETFLOAT (&toolInfo[3], tool.tipVelocity().y);
            SETFLOAT (&toolInfo[4], tool.tipVelocity().z);

            outlet_anything(x->x_outletHandsFingersTools, gensym ("tool"), numAtoms, toolInfo);
        }

        if (x->x_toolsSizeFlag)
        {
            SETFLOAT (&toolInfo[0], toolIdx);
            SETSYMBOL (&toolInfo[1], gensym ("size"));
            SETFLOAT (&toolInfo[2], tool.width());
            SETFLOAT (&toolInfo[3], tool.length());

            outlet_anything(x->x_outletHandsFingersTools, gensym ("tool"), numAtoms - 1, toolInfo);
        }
    }

    // general
    if (x->x_generalFlag)
    {
        int numAtoms = 6;
        t_atom generalInfo[numAtoms];

        SETFLOAT (&generalInfo[0], (t_float) frame.id());
        SETFLOAT (&generalInfo[1], (t_float) frame.timestamp());
        SETFLOAT (&generalInfo[2], (t_float) numHandsPerFrame);
        SETFLOAT (&generalInfo[3], (t_float) numFingersPerFrame);
        SETFLOAT (&generalInfo[4], (t_float) numToolsPerFrame);
        SETFLOAT (&generalInfo[5], (t_float) numGesturesPerFrame);

        outlet_list(x->x_outletGeneral, 0, numAtoms, &generalInfo[0]);
    }
}

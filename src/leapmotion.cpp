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
    x->x_timeStampReference = 0;

    x->x_iBoxNormalize = 0;

    x->x_gestureCountFlag = 0;

    x->x_handsArmCenterFlag = 0;
    x->x_handsArmDirectionFlag = 0;
    x->x_handsArmElbowPositionFlag = 0;
    x->x_handsArmWristPositionFlag = 0;
    x->x_handsArmWidthFlag = 0;
    x->x_handsTypeFlag = 0;
    x->x_handsSphereRadiusFlag = 0;
    x->x_handsSphereCenterFlag = 0;
    x->x_handsDirectionFlag = 0;
    x->x_handsPalmNormalFlag = 0;
    x->x_handsPalmPositionFlag = 1;
    x->x_handsStabilizedPalmPositionFlag = 0;
    x->x_handsPalmVelocityFlag = 0;
    x->x_handsPalmWidthFlag = 0;
    x->x_handsFingerCountFlag = 0;
    x->x_handsToolCountFlag = 0;
    x->x_handsGrabStrengthFlag = 0;
    x->x_handsPinchStrengthFlag = 0;
    x->x_handsTimeVisibleFlag = 0;

    x->x_fingersTypeFlag = 0;
    x->x_fingersDirectionFlag = 0;
    x->x_fingersPositionFlag = 0;
    x->x_fingersVelocityFlag = 0;
    x->x_fingersSizeFlag = 0;
    x->x_fingersIsExtendedFlag = 0;

    x->x_toolsDirectionFlag = 0;
    x->x_toolsPositionFlag = 0;
    x->x_toolsVelocityFlag = 0;
    x->x_toolsSizeFlag = 0;

    x->x_generalFlag = 1;

    post ("\n****************");
    post ("[leapmotion] for Pd %s", PD_LEAPMOTION_VERSION);
    post ("Forked from version 0.1 by Chikashi Miyama");
    post ("Updated by William Brent (%s)", PD_LEAPMOTION_RELEASE_DATE);
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
        A_NULL
    );


    // info
    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionInfo,
        gensym ("info"),
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionResetTimeStamp,
        gensym ("timestamp_reset"),
        A_NULL
    );


    // poll
    class_addbang (
        leapmotion_class,
        (t_method) leapmotionPoll
    );


    // set methods
    // interaction box normalization
    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetInteractionBoxNormalize,
        gensym ("ibox_normalize"),
        A_DEFFLOAT,
        A_NULL
    );

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
        (t_method) leapmotionSetHandsArmCenterFlag,
        gensym ("arm_center"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsArmDirectionFlag,
        gensym ("arm_direction"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsArmElbowPositionFlag,
        gensym ("arm_elbow_position"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsArmWristPositionFlag,
        gensym ("arm_wrist_position"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsArmWidthFlag,
        gensym ("arm_width"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsTypeFlag,
        gensym ("hand_type"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsSphereRadiusFlag,
        gensym ("hand_sphere_radius"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsSphereCenterFlag,
        gensym ("hand_sphere_center"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsDirectionFlag,
        gensym ("hand_direction"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsPalmNormalFlag,
        gensym ("hand_palm_normal"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsPalmPositionFlag,
        gensym ("hand_palm_position"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsStabilizedPalmPositionFlag,
        gensym ("hand_stabilized_palm_position"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsPalmVelocityFlag,
        gensym ("hand_palm_velocity"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsPalmWidthFlag,
        gensym ("hand_palm_width"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsFingerCountFlag,
        gensym ("hand_finger_count"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsToolCountFlag,
        gensym ("hand_tool_count"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsGrabStrengthFlag,
        gensym ("hand_grab_strength"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsPinchStrengthFlag,
        gensym ("hand_pinch_strength"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetHandsTimeVisibleFlag,
        gensym ("hand_time_visible"),
        A_DEFFLOAT,
        A_NULL
    );


    // fingers
    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetFingerTypeFlag,
        gensym ("finger_type"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetFingerDirectionFlag,
        gensym ("finger_direction"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetFingerPositionFlag,
        gensym ("finger_position"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetFingerVelocityFlag,
        gensym ("finger_velocity"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetFingerSizeFlag,
        gensym ("finger_size"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetFingerIsExtendedFlag,
        gensym ("finger_is_extended"),
        A_DEFFLOAT,
        A_NULL
    );


    // tools
    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetToolsDirectionFlag,
        gensym ("tool_direction"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetToolsPositionFlag,
        gensym ("tool_position"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetToolsVelocityFlag,
        gensym ("tool_velocity"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetToolsSizeFlag,
        gensym ("tool_size"),
        A_DEFFLOAT,
        A_NULL
    );


    // gestures
    // gesture count
    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetGestureCountFlag,
        gensym ("gesture_count"),
        A_DEFFLOAT,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetGestureFlags,
        gensym ("gesture_enable"),
        A_GIMME,
        A_NULL
    );

    class_addmethod (
        leapmotion_class,
        (t_method) leapmotionSetGestureConfig,
        gensym ("gesture_config"),
        A_SYMBOL,
        A_DEFFLOAT,
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

// set methods: interaction box normalization
void leapmotionSetInteractionBoxNormalize (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_iBoxNormalize = state;
}

// set methods: hands
static void leapmotionSetHandsArmCenterFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_handsArmCenterFlag = state;
}

static void leapmotionSetHandsArmDirectionFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_handsArmDirectionFlag = state;
}

static void leapmotionSetHandsArmElbowPositionFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_handsArmElbowPositionFlag = state;
}

static void leapmotionSetHandsArmWristPositionFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_handsArmWristPositionFlag = state;
}

static void leapmotionSetHandsArmWidthFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_handsArmWidthFlag = state;
}

static void leapmotionSetHandsTypeFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_handsTypeFlag = state;
}

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

static void leapmotionSetHandsStabilizedPalmPositionFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_handsStabilizedPalmPositionFlag = state;
}

static void leapmotionSetHandsPalmVelocityFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_handsPalmVelocityFlag = state;
}

static void leapmotionSetHandsPalmWidthFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_handsPalmWidthFlag = state;
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

static void leapmotionSetHandsGrabStrengthFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_handsGrabStrengthFlag = state;
}

static void leapmotionSetHandsPinchStrengthFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_handsPinchStrengthFlag = state;
}

static void leapmotionSetHandsTimeVisibleFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_handsTimeVisibleFlag = state;
}


// set methods: fingers
static void leapmotionSetFingerTypeFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_fingersTypeFlag = state;
}

static void leapmotionSetFingerDirectionFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_fingersDirectionFlag = state;
}

static void leapmotionSetFingerPositionFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_fingersPositionFlag = state;
}

static void leapmotionSetFingerVelocityFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_fingersVelocityFlag = state;
}

static void leapmotionSetFingerSizeFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_fingersSizeFlag = state;
}

static void leapmotionSetFingerIsExtendedFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_fingersIsExtendedFlag = state;
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
// count
static void leapmotionSetGestureCountFlag (t_leapmotion* x, t_float state)
{
    state = (state < 0.0) ? 0.0 : state;
    state = (state > 1.0) ? 1.0 : state;

    x->x_gestureCountFlag = state;
}

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

        if (! strcmp (type, "circle"))
        {
            if (state)
                x->x_leapMotionObjPtr->m_controller.enableGesture (Leap::Gesture::TYPE_CIRCLE, true);
            else
                x->x_leapMotionObjPtr->m_controller.enableGesture (Leap::Gesture::TYPE_CIRCLE, false);
        }

        if (! strcmp (type, "swipe"))
        {
            if (state)
                x->x_leapMotionObjPtr->m_controller.enableGesture (Leap::Gesture::TYPE_SWIPE, true);
            else
                x->x_leapMotionObjPtr->m_controller.enableGesture (Leap::Gesture::TYPE_SWIPE, false);
        }

        if (! strcmp (type, "key_tap"))
        {
            if (state)
                x->x_leapMotionObjPtr->m_controller.enableGesture (Leap::Gesture::TYPE_KEY_TAP, true);
            else
                x->x_leapMotionObjPtr->m_controller.enableGesture (Leap::Gesture::TYPE_KEY_TAP, false);
        }

        if (! strcmp (type, "screen_tap"))
        {
            if (state)
                x->x_leapMotionObjPtr->m_controller.enableGesture (Leap::Gesture::TYPE_SCREEN_TAP, true);
            else
                x->x_leapMotionObjPtr->m_controller.enableGesture (Leap::Gesture::TYPE_SCREEN_TAP, false);
        }
    }
}

static void leapmotionSetGestureConfig (t_leapmotion* x, t_symbol* key, t_float value)
{
    if (! strcmp (key->s_name, "circle_min_radius"))
        x->x_leapMotionObjPtr->m_controller.config().setFloat("Gesture.Circle.MinRadius", value);
    else if (! strcmp (key->s_name, "circle_min_arc"))
        x->x_leapMotionObjPtr->m_controller.config().setFloat("Gesture.Circle.MinArc", value);
    else if (! strcmp (key->s_name, "swipe_min_length"))
        x->x_leapMotionObjPtr->m_controller.config().setFloat("Gesture.Swipe.MinLength", value);
    else if (! strcmp (key->s_name, "swipe_min_velocity"))
        x->x_leapMotionObjPtr->m_controller.config().setFloat("Gesture.Swipe.MinVelocity", value);
    else if (! strcmp (key->s_name, "key_tap_min_down_velocity"))
        x->x_leapMotionObjPtr->m_controller.config().setFloat("Gesture.KeyTap.MinDownVelocity", value);
    else if (! strcmp (key->s_name, "key_tap_history_seconds"))
        x->x_leapMotionObjPtr->m_controller.config().setFloat("Gesture.KeyTap.HistorySeconds", value);
    else if (! strcmp (key->s_name, "key_tap_min_distance"))
        x->x_leapMotionObjPtr->m_controller.config().setFloat("Gesture.KeyTap.MinDistance", value);
    else if (! strcmp (key->s_name, "screen_tap_min_forward_velocity"))
        x->x_leapMotionObjPtr->m_controller.config().setFloat("Gesture.ScreenTap.MinForwardVelocity", value);
    else if (! strcmp (key->s_name, "screen_tap_history_seconds"))
        x->x_leapMotionObjPtr->m_controller.config().setFloat("Gesture.ScreenTap.HistorySeconds", value);
    else if (! strcmp (key->s_name, "screen_tap_min_distance"))
        x->x_leapMotionObjPtr->m_controller.config().setFloat("Gesture.ScreenTap.MinDistance", value);
    else
        pd_error (x, "[%s]: Unknown Gesture configuration parameter: %s", x->x_objSymbol->s_name, key->s_name);

    // must save for the change to take effect
    x->x_leapMotionObjPtr->m_controller.config().save();
}


// info method
static void leapmotionInfo (t_leapmotion* x)
{
    Leap::Frame frame = x->x_leapMotionObjPtr->m_dispatcher.frame;
    Leap::InteractionBox interactionBox = frame.interactionBox();
    Leap::DeviceList deviceList = x->x_leapMotionObjPtr->m_controller.devices();
    int numDevices = deviceList.count();

    post ("\n\n******** [leapmotion] %s", PD_LEAPMOTION_VERSION);
    post ("****");
    post ("**** Connected devices:");
    for (int d = 0; d < numDevices; d++)
        post ("Leap Motion %s", deviceList[d].toString().c_str());

    post ("\n**** Interaction box:");
    post ("Center & dimensions of %s", interactionBox.toString().c_str());
    post ("ibox_normalize: %i\n", x->x_iBoxNormalize);

    post ("\n**** Flag states:");
    post ("general: %i\n", x->x_generalFlag);

    post ("arm_center: %i", x->x_handsArmCenterFlag);
    post ("arm_direction: %i", x->x_handsArmDirectionFlag);
    post ("arm_elbow_position: %i", x->x_handsArmElbowPositionFlag);
    post ("arm_wrist_position: %i", x->x_handsArmWristPositionFlag);
    post ("arm_width: %i\n", x->x_handsArmWidthFlag);

    post ("hand_type: %i", x->x_handsTypeFlag);
    post ("hand_sphere_radius: %i", x->x_handsSphereRadiusFlag);
    post ("hand_sphere_center: %i", x->x_handsSphereCenterFlag);
    post ("hand_direction: %i", x->x_handsDirectionFlag);
    post ("hand_palm_normal: %i", x->x_handsPalmNormalFlag);
    post ("hand_palm_position: %i", x->x_handsPalmPositionFlag);
    post ("hand_stabilized_palm_position: %i", x->x_handsStabilizedPalmPositionFlag);
    post ("hand_palm_velocity: %i", x->x_handsPalmVelocityFlag);
    post ("hand_palm_width: %i", x->x_handsPalmWidthFlag);
    post ("hand_tool_count: %i", x->x_handsToolCountFlag);
    post ("hand_finger_count: %i", x->x_handsFingerCountFlag);
    post ("hand_grab_strength: %i", x->x_handsGrabStrengthFlag);
    post ("hand_pinch_strength: %i", x->x_handsPinchStrengthFlag);
    post ("hand_time_visible: %i\n", x->x_handsTimeVisibleFlag);

    post ("finger_type: %i", x->x_fingersTypeFlag);
    post ("finger_direction: %i", x->x_fingersDirectionFlag);
    post ("finger_position: %i", x->x_fingersPositionFlag);
    post ("finger_velocity: %i", x->x_fingersVelocityFlag);
    post ("finger_size: %i", x->x_fingersSizeFlag);
    post ("finger_is_extended: %i\n", x->x_fingersIsExtendedFlag);

    post ("tool_direction: %i", x->x_toolsDirectionFlag);
    post ("tool_position: %i", x->x_toolsPositionFlag);
    post ("tool_velocity: %i", x->x_toolsVelocityFlag);
    post ("tool_size: %i\n", x->x_toolsSizeFlag);

    post ("gesture_count: %i", x->x_gestureCountFlag);

    post ("gesture_circle: %i", x->x_leapMotionObjPtr->m_controller.isGestureEnabled (Leap::Gesture::TYPE_CIRCLE));
    post ("gesture_swipe: %i", x->x_leapMotionObjPtr->m_controller.isGestureEnabled (Leap::Gesture::TYPE_SWIPE));
    post ("gesture_key_tap: %i", x->x_leapMotionObjPtr->m_controller.isGestureEnabled (Leap::Gesture::TYPE_KEY_TAP));
    post ("gesture_screen_tap: %i\n", x->x_leapMotionObjPtr->m_controller.isGestureEnabled (Leap::Gesture::TYPE_SCREEN_TAP));

    post ("**** Gesture configuration:");
    post ("Gesture.Circle.MinRadius: %0.2f mm", x->x_leapMotionObjPtr->m_controller.config().getFloat("Gesture.Circle.MinRadius"));
    post ("Gesture.Circle.MinArc: %0.2f radians\n", x->x_leapMotionObjPtr->m_controller.config().getFloat("Gesture.Circle.MinArc"));
    post ("Gesture.Swipe.MinLength: %0.2f mm", x->x_leapMotionObjPtr->m_controller.config().getFloat("Gesture.Swipe.MinLength"));
    post ("Gesture.Swipe.MinVelocity: %0.2f mm/s\n", x->x_leapMotionObjPtr->m_controller.config().getFloat("Gesture.Swipe.MinVelocity"));
    post ("Gesture.KeyTap.MinDownVelocity: %0.2f mm/s", x->x_leapMotionObjPtr->m_controller.config().getFloat("Gesture.KeyTap.MinDownVelocity"));
    post ("Gesture.KeyTap.HistorySeconds: %0.2f s", x->x_leapMotionObjPtr->m_controller.config().getFloat("Gesture.KeyTap.HistorySeconds"));
    post ("Gesture.KeyTap.MinDistance: %0.2f mm\n", x->x_leapMotionObjPtr->m_controller.config().getFloat("Gesture.KeyTap.MinDistance"));
    post ("Gesture.ScreenTap.MinForwardVelocity: %0.2f mm/s", x->x_leapMotionObjPtr->m_controller.config().getFloat("Gesture.ScreenTap.MinForwardVelocity"));
    post ("Gesture.ScreenTap.HistorySeconds: %0.2f s", x->x_leapMotionObjPtr->m_controller.config().getFloat("Gesture.ScreenTap.HistorySeconds"));
    post ("Gesture.ScreenTap.MinDistance: %0.2f mm\n\n", x->x_leapMotionObjPtr->m_controller.config().getFloat("Gesture.ScreenTap.MinDistance"));
}

// reset the time stamp
static void leapmotionResetTimeStamp (t_leapmotion* x)
{
    x->x_timeStampReference = x->x_leapMotionObjPtr->m_dispatcher.frame.timestamp();
}

// poll method
static void leapmotionPoll (t_leapmotion* x)
{
    Leap::Frame frame;

    if (! x->x_leapMotionObjPtr->m_controller.isConnected())
    {
        pd_error(x, "[%s]: No Leap Motion Controller connected!", x->x_objSymbol->s_name);
        return;
    }

    // get the current frame from the dispatcher
    frame = x->x_leapMotionObjPtr->m_dispatcher.frame;

    //// output data in right to left order from outlets
    //
    // gestures
    if (frame.gestures().count() > 0)
        leapmotionProcessGestures (x, frame);

    // hands and fingers
    if (frame.hands().count() > 0)
        leapmotionProcessHands (x, frame);

    // tools
    if (frame.tools().count() > 0)
        leapmotionProcessTools (x, frame);

    // general
    if (x->x_generalFlag)
        leapmotionProcessGeneral (x, frame);
}

// process gesture data
static void leapmotionProcessGestures (t_leapmotion* x, Leap::Frame frame)
{
    Leap::GestureList gestureList = frame.gestures();
    int numGesturesPerFrame = gestureList.count();
    Leap::InteractionBox interactionBox = frame.interactionBox();

    if (x->x_gestureCountFlag)
    {
        t_atom gestureCount[1];

        SETFLOAT (&gestureCount[0], (t_float) numGesturesPerFrame);
        outlet_anything (x->x_outletGesture, gensym ("count"), 1, gestureCount);
    }

    for (int gestureIdx = 0; gestureIdx < numGesturesPerFrame; gestureIdx++)
    {
        Leap::Gesture gesture = gestureList[gestureIdx];
        // cast the gesture to specific types for data output below
        Leap::CircleGesture circleGesture = gesture;
        Leap::SwipeGesture swipeGesture = gesture;
        Leap::KeyTapGesture keyTapGesture = gesture;
        Leap::ScreenTapGesture screenTapGesture = gesture;
        Leap::Vector point;

        int numGestureInfoAtoms = 3;
        t_atom gestureInfo[numGestureInfoAtoms];

        int numGestureDataAtoms = 7;
        t_atom gestureData[numGestureDataAtoms];

        // id
        SETFLOAT (&gestureInfo[0], gestureIdx);
        SETSYMBOL (&gestureInfo[1], gensym ("id"));
        SETFLOAT (&gestureInfo[2], gesture.id());

        outlet_list (x->x_outletGesture, 0, numGestureInfoAtoms, gestureInfo);

        //state
        SETFLOAT (&gestureInfo[0], gestureIdx);
        SETSYMBOL (&gestureInfo[1], gensym ("state"));

        switch(gesture.state())
        {
            case Leap::Gesture::STATE_INVALID:
                SETSYMBOL (&gestureInfo[2], gensym ("invalid"));
                break;
            case Leap::Gesture::STATE_START:
                SETSYMBOL (&gestureInfo[2], gensym ("start"));
                break;
            case Leap::Gesture::STATE_UPDATE:
                SETSYMBOL (&gestureInfo[2], gensym ("update"));
                break;
            case Leap::Gesture::STATE_STOP:
                SETSYMBOL (&gestureInfo[2], gensym ("stop"));
                break;
        }

        outlet_list (x->x_outletGesture, 0, numGestureInfoAtoms, gestureInfo);

        // duration
        SETFLOAT (&gestureInfo[0], gestureIdx);
        SETSYMBOL (&gestureInfo[1], gensym ("duration"));
        SETFLOAT (&gestureInfo[2], gesture.durationSeconds());

        outlet_list (x->x_outletGesture, 0, numGestureInfoAtoms, gestureInfo);

        // additional gesture-specific data
        SETFLOAT (&gestureData[0], gestureIdx);
        SETSYMBOL (&gestureData[1], gensym ("data"));

        switch (gesture.type())
        {
            case Leap::Gesture::TYPE_INVALID:
                break;

            case Leap::Gesture::TYPE_CIRCLE:
                SETSYMBOL (&gestureData[2], gensym ("circle"));

                if (x->x_iBoxNormalize)
                    point = interactionBox.normalizePoint(circleGesture.center(), false);
                else
                    point = circleGesture.center();

                SETSYMBOL (&gestureData[3], gensym ("center"));
                SETFLOAT (&gestureData[4], point.x);
                SETFLOAT (&gestureData[5], point.y);
                SETFLOAT (&gestureData[6], point.z);
                outlet_list (x->x_outletGesture, 0, numGestureDataAtoms, gestureData);

                SETSYMBOL (&gestureData[3], gensym ("radius"));
                SETFLOAT (&gestureData[4], circleGesture.radius());
                outlet_list (x->x_outletGesture, 0, numGestureDataAtoms - 2, gestureData);

                SETSYMBOL (&gestureData[3], gensym ("progress"));
                SETFLOAT (&gestureData[4], circleGesture.progress());
                outlet_list (x->x_outletGesture, 0, numGestureDataAtoms - 2, gestureData);
                break;

            case Leap::Gesture::TYPE_SWIPE:
                SETSYMBOL (&gestureData[2], gensym ("swipe"));

                if (x->x_iBoxNormalize)
                    point = interactionBox.normalizePoint(swipeGesture.startPosition(), false);
                else
                    point = swipeGesture.startPosition();

                SETSYMBOL (&gestureData[3], gensym ("start_position"));
                SETFLOAT (&gestureData[4], point.x);
                SETFLOAT (&gestureData[5], point.y);
                SETFLOAT (&gestureData[6], point.z);
                outlet_list (x->x_outletGesture, 0, numGestureDataAtoms, gestureData);

                SETSYMBOL (&gestureData[3], gensym ("direction"));
                SETFLOAT (&gestureData[4], swipeGesture.direction().x);
                SETFLOAT (&gestureData[5], swipeGesture.direction().y);
                SETFLOAT (&gestureData[6], swipeGesture.direction().z);
                outlet_list (x->x_outletGesture, 0, numGestureDataAtoms, gestureData);

                SETSYMBOL (&gestureData[3], gensym ("speed"));
                SETFLOAT (&gestureData[4], swipeGesture.speed());
                outlet_list (x->x_outletGesture, 0, numGestureDataAtoms - 2, gestureData);

                if (x->x_iBoxNormalize)
                    point = interactionBox.normalizePoint(swipeGesture.position(), false);
                else
                    point = swipeGesture.position();

                SETSYMBOL (&gestureData[3], gensym ("position"));
                SETFLOAT (&gestureData[4], point.x);
                SETFLOAT (&gestureData[5], point.y);
                SETFLOAT (&gestureData[6], point.z);
                outlet_list (x->x_outletGesture, 0, numGestureDataAtoms, gestureData);
                break;

            case Leap::Gesture::TYPE_KEY_TAP:
                SETSYMBOL (&gestureData[2], gensym ("key_tap"));

                SETSYMBOL (&gestureData[3], gensym ("direction"));
                SETFLOAT (&gestureData[4], keyTapGesture.direction().x);
                SETFLOAT (&gestureData[5], keyTapGesture.direction().y);
                SETFLOAT (&gestureData[6], keyTapGesture.direction().z);
                outlet_list (x->x_outletGesture, 0, numGestureDataAtoms, gestureData);

                if (x->x_iBoxNormalize)
                    point = interactionBox.normalizePoint(keyTapGesture.position(), false);
                else
                    point = keyTapGesture.position();

                SETSYMBOL (&gestureData[3], gensym ("position"));
                SETFLOAT (&gestureData[4], point.x);
                SETFLOAT (&gestureData[5], point.y);
                SETFLOAT (&gestureData[6], point.z);
                outlet_list (x->x_outletGesture, 0, numGestureDataAtoms, gestureData);

                SETSYMBOL (&gestureData[3], gensym ("progress"));
                SETFLOAT (&gestureData[4], keyTapGesture.progress());
                outlet_list (x->x_outletGesture, 0, numGestureDataAtoms - 2, gestureData);
                break;

            case Leap::Gesture::TYPE_SCREEN_TAP:
                SETSYMBOL (&gestureData[2], gensym ("screen_tap"));

                SETSYMBOL (&gestureData[3], gensym ("direction"));
                SETFLOAT (&gestureData[4], screenTapGesture.direction().x);
                SETFLOAT (&gestureData[5], screenTapGesture.direction().y);
                SETFLOAT (&gestureData[6], screenTapGesture.direction().z);
                outlet_list (x->x_outletGesture, 0, numGestureDataAtoms, gestureData);

                if (x->x_iBoxNormalize)
                    point = interactionBox.normalizePoint(screenTapGesture.position(), false);
                else
                    point = screenTapGesture.position();

                SETSYMBOL (&gestureData[3], gensym ("position"));
                SETFLOAT (&gestureData[4], point.x);
                SETFLOAT (&gestureData[5], point.y);
                SETFLOAT (&gestureData[6], point.z);
                outlet_list (x->x_outletGesture, 0, numGestureDataAtoms, gestureData);

                SETSYMBOL (&gestureData[3], gensym ("progress"));
                SETFLOAT (&gestureData[4], screenTapGesture.progress());
                outlet_list (x->x_outletGesture, 0, numGestureDataAtoms - 2, gestureData);
                break;
        }
    }
}

// process hand data
static void leapmotionProcessHands (t_leapmotion* x, Leap::Frame frame)
{
    Leap::HandList handList = frame.hands();
    Leap::InteractionBox interactionBox = frame.interactionBox();

    for (int handIdx = 0; handIdx < handList.count(); handIdx++)
    {
        int numFingersPerHand, numToolsPerHand;
        int numHandInfoAtoms = 6;
        t_atom handInfo[numHandInfoAtoms];

        Leap::Hand hand = handList[handIdx];
        Leap::FingerList fingerList = hand.fingers();
        Leap::ToolList toolList = hand.tools();
        Leap::Vector point;

        // from LeapSDK/docs/cpp/devguide/Leap_Pointables.html: "As of version 2.0 of the Leap Motion SDK, all five fingers are are always present in the list of fingers for a hand."
        // therefore, Leap::FingerList.count() will not work as it did in the previous SDK. can use Leap::Finger.isExtended() to determine which ones are actually out.
        numFingersPerHand = fingerList.count();
        numToolsPerHand = toolList.count();

        // process arm per hand
        leapmotionProcessArm (x, handIdx, hand, interactionBox);

        if (x->x_handsTypeFlag)
        {
            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("type"));

            if (hand.isValid())
            {
                if (hand.isLeft())
                    SETSYMBOL (&handInfo[2], gensym ("left"));
                else if (hand.isRight())
                    SETSYMBOL (&handInfo[2], gensym ("right"));
            }
            else
                SETSYMBOL (&handInfo[2], gensym ("invalid"));

            outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numHandInfoAtoms - 3, handInfo);
        }

        // sphere radius
        if (x->x_handsSphereRadiusFlag)
        {
            // sphere radius
            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("sphere"));
            SETSYMBOL (&handInfo[2], gensym ("radius"));
            SETFLOAT (&handInfo[3], hand.sphereRadius());

            outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numHandInfoAtoms - 2, handInfo);
        }

        // sphere center
        if (x->x_handsSphereCenterFlag)
        {
            if (x->x_iBoxNormalize)
                point = interactionBox.normalizePoint(hand.sphereCenter(), false);
            else
                point = hand.sphereCenter();

            // sphere center
            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("sphere"));
            SETSYMBOL (&handInfo[2], gensym ("center"));
            SETFLOAT (&handInfo[3], point.x);
            SETFLOAT (&handInfo[4], point.y);
            SETFLOAT (&handInfo[5], point.z);

            outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numHandInfoAtoms, handInfo);
        }

        // direction
        if (x->x_handsDirectionFlag)
        {
            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("direction"));
            SETFLOAT (&handInfo[2], hand.direction().x);
            SETFLOAT (&handInfo[3], hand.direction().y);
            SETFLOAT (&handInfo[4], hand.direction().z);

            outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numHandInfoAtoms - 1, handInfo);
        }

        // palm normal
        if (x->x_handsPalmNormalFlag)
        {
            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("palm"));
            SETSYMBOL (&handInfo[2], gensym ("normal"));
            SETFLOAT (&handInfo[3], hand.palmNormal().x);
            SETFLOAT (&handInfo[4], hand.palmNormal().y);
            SETFLOAT (&handInfo[5], hand.palmNormal().z);

            outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numHandInfoAtoms, handInfo);
        }

        // palm position
        if (x->x_handsPalmPositionFlag)
        {
            if (x->x_iBoxNormalize)
                point = interactionBox.normalizePoint(hand.palmPosition(), false);
            else
                point = hand.palmPosition();

            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("palm"));
            SETSYMBOL (&handInfo[2], gensym ("position"));
            SETFLOAT (&handInfo[3], point.x);
            SETFLOAT (&handInfo[4], point.y);
            SETFLOAT (&handInfo[5], point.z);

            outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numHandInfoAtoms, handInfo);
        }

        // stabilized palm position
        if (x->x_handsStabilizedPalmPositionFlag)
        {
            if (x->x_iBoxNormalize)
                point = interactionBox.normalizePoint(hand.stabilizedPalmPosition(), false);
            else
                point = hand.stabilizedPalmPosition();

            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("palm"));
            SETSYMBOL (&handInfo[2], gensym ("stabilized_position"));
            SETFLOAT (&handInfo[3], point.x);
            SETFLOAT (&handInfo[4], point.y);
            SETFLOAT (&handInfo[5], point.z);

            outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numHandInfoAtoms, handInfo);
        }

        // palm velocity
        if (x->x_handsPalmVelocityFlag)
        {
            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("palm"));
            SETSYMBOL (&handInfo[2], gensym ("velocity"));
            SETFLOAT (&handInfo[3], hand.palmVelocity().x);
            SETFLOAT (&handInfo[4], hand.palmVelocity().y);
            SETFLOAT (&handInfo[5], hand.palmVelocity().z);

            outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numHandInfoAtoms, handInfo);
        }

        // palm width
        if (x->x_handsPalmWidthFlag)
        {
            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("palm"));
            SETSYMBOL (&handInfo[2], gensym ("width"));
            SETFLOAT (&handInfo[3], hand.palmWidth());

            outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numHandInfoAtoms - 2, handInfo);
        }

        // finger count
        if (x->x_handsFingerCountFlag)
        {
            int fingerCount = 0;

            for (int fingerIdx = 0; fingerIdx < numFingersPerHand; fingerIdx++)
            {
                Leap::Finger finger = fingerList[fingerIdx];
                fingerCount += finger.isExtended();
            }

            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("finger_count"));
            SETFLOAT (&handInfo[2], fingerCount);

            outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numHandInfoAtoms - 3, handInfo);
        }

        // tool count
        if (x->x_handsToolCountFlag)
        {
            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("tool_count"));
            SETFLOAT (&handInfo[2], numToolsPerHand);

            outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numHandInfoAtoms - 3, handInfo);
        }

        // grab strength
        if (x->x_handsGrabStrengthFlag)
        {
            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("grab_strength"));
            SETFLOAT (&handInfo[2], hand.grabStrength());

            outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numHandInfoAtoms - 3, handInfo);
        }

        // pinch strength
        if (x->x_handsPinchStrengthFlag)
        {
            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("pinch_strength"));
            SETFLOAT (&handInfo[2], hand.pinchStrength());

            outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numHandInfoAtoms - 3, handInfo);
        }

        // time visible
        if (x->x_handsTimeVisibleFlag)
        {
            SETFLOAT (&handInfo[0], handIdx);
            SETSYMBOL (&handInfo[1], gensym ("time_visible"));
            SETFLOAT (&handInfo[2], hand.timeVisible());

            outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numHandInfoAtoms - 3, handInfo);
        }

        // process fingers per hand
        if (numFingersPerHand)
            leapmotionProcessFingers (x, handIdx, fingerList, interactionBox);
    }
}

// process arm data
static void leapmotionProcessArm (t_leapmotion* x, int handIdx, Leap::Hand hand, Leap::InteractionBox interactionBox)
{
    Leap::Arm arm = hand.arm();
    int numArmInfoAtoms = 6;
    t_atom armInfo[numArmInfoAtoms];
    Leap::Vector point;

    // center
    if (x->x_handsArmCenterFlag)
    {
        if (x->x_iBoxNormalize)
            point = interactionBox.normalizePoint(arm.center(), false);
        else
            point = arm.center();

        SETFLOAT (&armInfo[0], (t_float) handIdx);
        SETSYMBOL (&armInfo[1], gensym ("arm"));
        SETSYMBOL (&armInfo[2], gensym ("center"));
        SETFLOAT (&armInfo[3], point.x);
        SETFLOAT (&armInfo[4], point.y);
        SETFLOAT (&armInfo[5], point.z);

        outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numArmInfoAtoms, armInfo);
    }

    // direction
    if (x->x_handsArmDirectionFlag)
    {
        SETFLOAT (&armInfo[0], (t_float) handIdx);
        SETSYMBOL (&armInfo[1], gensym ("arm"));
        SETSYMBOL (&armInfo[2], gensym ("direction"));
        SETFLOAT (&armInfo[3], arm.direction().x);
        SETFLOAT (&armInfo[4], arm.direction().y);
        SETFLOAT (&armInfo[5], arm.direction().z);

        outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numArmInfoAtoms, armInfo);
    }

    // elbow_position
    if (x->x_handsArmElbowPositionFlag)
    {
        if (x->x_iBoxNormalize)
            point = interactionBox.normalizePoint(arm.elbowPosition(), false);
        else
            point = arm.elbowPosition();

        SETFLOAT (&armInfo[0], (t_float) handIdx);
        SETSYMBOL (&armInfo[1], gensym ("arm"));
        SETSYMBOL (&armInfo[2], gensym ("elbow_position"));
        SETFLOAT (&armInfo[3], point.x);
        SETFLOAT (&armInfo[4], point.y);
        SETFLOAT (&armInfo[5], point.z);

        outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numArmInfoAtoms, armInfo);
    }

    // wrist_position
    if (x->x_handsArmWristPositionFlag)
    {
        if (x->x_iBoxNormalize)
            point = interactionBox.normalizePoint(arm.wristPosition(), false);
        else
            point = arm.wristPosition();

        SETFLOAT (&armInfo[0], (t_float) handIdx);
        SETSYMBOL (&armInfo[1], gensym ("arm"));
        SETSYMBOL (&armInfo[2], gensym ("wrist_position"));
        SETFLOAT (&armInfo[3], point.x);
        SETFLOAT (&armInfo[4], point.y);
        SETFLOAT (&armInfo[5], point.z);

        outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numArmInfoAtoms, armInfo);
    }

    // width
    if (x->x_handsArmWidthFlag)
    {
        SETFLOAT (&armInfo[0], (t_float) handIdx);
        SETSYMBOL (&armInfo[1], gensym ("arm"));
        SETSYMBOL (&armInfo[2], gensym ("width"));
        SETFLOAT (&armInfo[3], (t_float) arm.width());

        outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numArmInfoAtoms - 2, armInfo);
    }
}

// process fingers
static void leapmotionProcessFingers (t_leapmotion* x, int handIdx, Leap::FingerList fingerList, Leap::InteractionBox interactionBox)
{
    for (int fingerIdx = 0; fingerIdx < fingerList.count(); fingerIdx++)
    {
        Leap::Finger finger = fingerList[fingerIdx];
        int numFingerInfoAtoms = 7;
        t_atom fingerInfo[numFingerInfoAtoms];
        Leap::Vector point;

        if (x->x_fingersTypeFlag)
        {
            Leap::Finger::Type fingerType = finger.type();

            SETFLOAT (&fingerInfo[0], handIdx);
            SETSYMBOL (&fingerInfo[1], gensym ("finger"));
            SETFLOAT (&fingerInfo[2], fingerIdx);
            SETSYMBOL (&fingerInfo[3], gensym ("type"));

            switch (fingerType)
            {
                case Leap::Finger::TYPE_THUMB:
                    SETSYMBOL (&fingerInfo[4], gensym ("thumb"));
                    break;
                case Leap::Finger::TYPE_INDEX:
                    SETSYMBOL (&fingerInfo[4], gensym ("index"));
                    break;
                case Leap::Finger::TYPE_MIDDLE:
                    SETSYMBOL (&fingerInfo[4], gensym ("middle"));
                    break;
                case Leap::Finger::TYPE_RING:
                    SETSYMBOL (&fingerInfo[4], gensym ("ring"));
                    break;
                case Leap::Finger::TYPE_PINKY:
                    SETSYMBOL (&fingerInfo[4], gensym ("pinky"));
                    break;
                default:
                    break;
            }

            outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numFingerInfoAtoms - 2, fingerInfo);
        }

        if (x->x_fingersDirectionFlag)
        {
            SETFLOAT (&fingerInfo[0], handIdx);
            SETSYMBOL (&fingerInfo[1], gensym ("finger"));
            // use Leap::Finger.type() to get stable finger indices where 0 is the thumb, and 4 is the pinky
            SETFLOAT (&fingerInfo[2], fingerIdx);
            SETSYMBOL (&fingerInfo[3], gensym ("direction"));
            SETFLOAT (&fingerInfo[4], finger.direction().x);
            SETFLOAT (&fingerInfo[5], finger.direction().y);
            SETFLOAT (&fingerInfo[6], finger.direction().z);

            outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numFingerInfoAtoms, fingerInfo);
        }

        if (x->x_fingersPositionFlag)
        {
            if (x->x_iBoxNormalize)
                point = interactionBox.normalizePoint(finger.tipPosition(), false);
            else
                point = finger.tipPosition();

            SETFLOAT (&fingerInfo[0], handIdx);
            SETSYMBOL (&fingerInfo[1], gensym ("finger"));
            SETFLOAT (&fingerInfo[2], fingerIdx);
            SETSYMBOL (&fingerInfo[3], gensym ("position"));
            SETFLOAT (&fingerInfo[4], point.x);
            SETFLOAT (&fingerInfo[5], point.y);
            SETFLOAT (&fingerInfo[6], point.z);

            outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numFingerInfoAtoms, fingerInfo);
        }

        if (x->x_fingersVelocityFlag)
        {
            SETFLOAT (&fingerInfo[0], handIdx);
            SETSYMBOL (&fingerInfo[1], gensym ("finger"));
            SETFLOAT (&fingerInfo[2], fingerIdx);
            SETSYMBOL (&fingerInfo[3], gensym ("velocity"));
            SETFLOAT (&fingerInfo[4], finger.tipVelocity().x);
            SETFLOAT (&fingerInfo[5], finger.tipVelocity().y);
            SETFLOAT (&fingerInfo[6], finger.tipVelocity().z);

            outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numFingerInfoAtoms, fingerInfo);
        }

        if (x->x_fingersSizeFlag)
        {
            SETFLOAT (&fingerInfo[0], handIdx);
            SETSYMBOL (&fingerInfo[1], gensym ("finger"));
            SETFLOAT (&fingerInfo[2], fingerIdx);
            SETSYMBOL (&fingerInfo[3], gensym ("size"));
            SETFLOAT (&fingerInfo[4], finger.width());
            SETFLOAT (&fingerInfo[5], finger.length());

            outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numFingerInfoAtoms - 1, fingerInfo);
        }

        if (x->x_fingersIsExtendedFlag)
        {
            SETFLOAT (&fingerInfo[0], handIdx);
            SETSYMBOL (&fingerInfo[1], gensym ("finger"));
            SETFLOAT (&fingerInfo[2], fingerIdx);
            SETSYMBOL (&fingerInfo[3], gensym ("is_extended"));
            SETFLOAT (&fingerInfo[4], finger.isExtended());

            outlet_anything (x->x_outletHandsFingersTools, gensym ("hand"), numFingerInfoAtoms - 2, fingerInfo);
        }
    }
}

// process tool data
static void leapmotionProcessTools (t_leapmotion* x, Leap::Frame frame)
{
    Leap::ToolList toolList = frame.tools();
    Leap::InteractionBox interactionBox = frame.interactionBox();

    // tools per frame
    for (int toolIdx = 0; toolIdx < toolList.count(); toolIdx++)
    {
        int numToolInfoAtoms = 5;
        t_atom toolInfo[numToolInfoAtoms];
        Leap::Vector point;

        Leap::Tool tool = toolList[toolIdx];

        if (x->x_toolsDirectionFlag)
        {
            SETFLOAT (&toolInfo[0], toolIdx);
            SETSYMBOL (&toolInfo[1], gensym ("direction"));
            SETFLOAT (&toolInfo[2], tool.direction().x);
            SETFLOAT (&toolInfo[3], tool.direction().y);
            SETFLOAT (&toolInfo[4], tool.direction().z);

            outlet_anything (x->x_outletHandsFingersTools, gensym ("tool"), numToolInfoAtoms, toolInfo);
        }

        if (x->x_toolsPositionFlag)
        {
            if (x->x_iBoxNormalize)
                point = interactionBox.normalizePoint(tool.tipPosition(), false);
            else
                point = tool.tipPosition();

            SETFLOAT (&toolInfo[0], toolIdx);
            SETSYMBOL (&toolInfo[1], gensym ("position"));
            SETFLOAT (&toolInfo[2], point.x);
            SETFLOAT (&toolInfo[3], point.y);
            SETFLOAT (&toolInfo[4], point.z);

            outlet_anything (x->x_outletHandsFingersTools, gensym ("tool"), numToolInfoAtoms, toolInfo);
        }

        if (x->x_toolsVelocityFlag)
        {
            SETFLOAT (&toolInfo[0], toolIdx);
            SETSYMBOL (&toolInfo[1], gensym ("velocity"));
            SETFLOAT (&toolInfo[2], tool.tipVelocity().x);
            SETFLOAT (&toolInfo[3], tool.tipVelocity().y);
            SETFLOAT (&toolInfo[4], tool.tipVelocity().z);

            outlet_anything (x->x_outletHandsFingersTools, gensym ("tool"), numToolInfoAtoms, toolInfo);
        }

        if (x->x_toolsSizeFlag)
        {
            SETFLOAT (&toolInfo[0], toolIdx);
            SETSYMBOL (&toolInfo[1], gensym ("size"));
            SETFLOAT (&toolInfo[2], tool.width());
            SETFLOAT (&toolInfo[3], tool.length());

            outlet_anything (x->x_outletHandsFingersTools, gensym ("tool"), numToolInfoAtoms - 1, toolInfo);
        }
    }
}


// process general data
static void leapmotionProcessGeneral (t_leapmotion* x, Leap::Frame frame)
{
    int numGeneralInfoAtoms = 6;
    t_atom generalInfo[numGeneralInfoAtoms];

    SETFLOAT (&generalInfo[0], (t_float) frame.id());
    // convert from microseconds to seconds
    SETFLOAT (&generalInfo[1], (t_float) ((frame.timestamp() - x->x_timeStampReference) / (t_float)1000000.0));
    SETFLOAT (&generalInfo[2], (t_float) frame.currentFramesPerSecond());
    SETFLOAT (&generalInfo[3], (t_float) frame.hands().count());
    SETFLOAT (&generalInfo[4], (t_float) frame.tools().count());
    SETFLOAT (&generalInfo[5], (t_float) frame.gestures().count());

    outlet_list (x->x_outletGeneral, 0, numGeneralInfoAtoms, generalInfo);
}

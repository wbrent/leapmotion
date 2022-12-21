# leapmotion

[leapmotion] is a Pure Data external for accessing Leap Motion Controller data in Pd under Linux and macOS. This repository is a fork of Chikashi Miyama's Pd_leapmotion version 0.1 code.

To keep things simple, all reference to the FLEXT interface for building Pd & Max/MSP externals in C++ has been removed. It can be built against Leap SDK version 2.3.1+31549 for Linux and macOS, which is its only dependency. Version 2.3.1 of the Leap SDK is available in the [legacy releases](https://developer.leapmotion.com/releases) area of their developer resources page. It may be possible to build/link this external under Windows as well, but only using version 2.3.1 of the Leap SDK.

The code has been organized into separate header and cpp files in order to support future development, and a pd-lib-builder-based Makefile is provided. To avoid breaking changes, all input messages and output data format remains the same as Pd_leapmotion version 0.1. Changes in the initial commit of this fork include:

<ul>
  <li> Removed all reference to the FLEXT interface</li>
  <li> Added a pd-lib-builder-based Makefile</li>
  <li> Fixed bug that was outputting palm velocity instead of palm normal</li>
  <li> Firing output from the *gesture*, *hand/tool*, and *general* outlets in right-to-left order, in keeping with Pd object protocol</li>
  <li> Added "gesture_count" method to output the number of detected gestures from the *gesture* outlet</li>
  <li> Added "hands_type" method to output the right/left classification of a hand</li>
  <li> Using Leap::Finger.type() to output stable finger indices (where 0 is the thumb, and 4 is the pinky)</li>
  <li> Removed finger count from *general* output list (as of Leap SDK version 2, general finger count is always 5 per hand)</li>
  <li> Using Leap::Finger.isExtended() to count the number of extended fingers for inclusion in the *hands/fingers* output list</li>
  <li> Updated help file</li>
</ul>

Documentation for Leap SDK version 2.3 can be found [here](https://developer-archive.leapmotion.com/documentation/v2/cpp/index.html?proglang=cpp).

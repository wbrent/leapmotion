leapmotion
=============

[leapmotion] is a Pure Data external for accessing LEAP motion controller data in Pd under macOS. This repository is a fork of Chikashi Miyama's Pd_leapmotion version 0.1 code.

Most importantly, all reference to the FLEXT interface for building Pd & Max/MSP externals in C++ has been removed. It can be built against the most recent version of the LEAP SDK for macOS (i.e., LeapDeveloperKit_2.3.1+31549_mac, as of December 2022), which is its only dependency. The code has been organized into separate header and cpp files in order to support future development, and a pd-lib-builder-based Makefile is provided. A few minor bugs in the original version 0.1 code have also been fixed.

# Makefile for leapmotion

# specify a location for Pd if desired
# PDDIR = /home/yourname/somedirectory/pd-0.53-1

lib.name = leapmotion

# this project is built against Leap Developer Kit 2.3.1+31549, and requires the same version of libLeap.so (Linux) libLeap.dylib (macOS), or Leap.dll (Windows)
# specify the location of the 2.3.1 LeapSDK directory
leapSDKdir = /your/path/to/the/LeapSDK

define forLinux
  # specify the location and name of the LEAP library
  ldflags = -L$(leapSDKdir)/lib/x64
	ldlibs = -lLeap

  # specify include directory with the LEAP headers
  cflags = -Iinclude -I$(leapSDKdir)/include
endef

define forDarwin
  # specify the location and name of the LEAP library
	ldflags = -L$(leapSDKdir)/lib
  ldlibs = -lLeap

  # specify include directory with the LEAP headers
  cflags = -Iinclude -I$(leapSDKdir)/include -mmacosx-version-min=10.9 -stdlib=libc++
endef

define forWindows
  # specify the location and name of the LEAP library
  ldflags = -L$(leapSDKdir)/lib/x64
	ldlibs = -lLeap

  # specify include directory with the LEAP headers
  cflags = -Iinclude -I$(leapSDKdir)/include
endef

$(lib.name).class.sources = src/$(lib.name).cpp

common.sources = src/Dispatcher.cpp src/LeapMotionObj.cpp

datafiles = help/leapmotion-help.pd README.md LICENSE

# provide the path to pd-lib-builder
PDLIBBUILDER_DIR=./pd-lib-builder/
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder

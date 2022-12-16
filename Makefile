# Makefile for leapmotion

# specify a location for Pd if desired
# PDDIR = /home/yourname/somedirectory/pd-0.53-1

lib.name = leapmotion

# specify the location and name of the LEAP library
# this project is built against LeapDeveloperKit_2.3.1+31549_mac, and requires the same version of libLeap.dylib
ldlibs = -L/your/path/to/LeapDeveloperKit_2.3.1+31549_mac/LeapSDK/lib -lLeap

# specify include directory with the LEAP headers
# NOTE: received the following warning on first compile attempt: "clang: warning: include path for libstdc++ headers not found; pass '-stdlib=libc++' on the command line to use the libc++ standard library instead [-Wstdlibcxx-not-found]". so, should set -stdlib accordingly via pd-lib-builder's cflags. had to set the minimum macOS version to 10.9 in order to work with libc++ standard library.
cflags = -Iinclude -I/your/path/to/LeapDeveloperKit_2.3.1+31549_mac/LeapSDK/include -mmacosx-version-min=10.9 -stdlib=libc++

$(lib.name).class.sources = src/$(lib.name).cpp

common.sources = src/Dispatcher.cpp src/LeapMotionObj.cpp

datafiles = help/leapmotion-help.pd README.md LICENSE

# provide the path to pd-lib-builder
PDLIBBUILDER_DIR=./pd-lib-builder/
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder

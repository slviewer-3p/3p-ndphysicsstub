#!/bin/bash

# turn on verbose debugging output for parabuild logs.
set -x
# make errors fatal
set -e

# Check autobuild is around or fail
if [ -z "$AUTOBUILD" ] ; then
fail
fi

if [ "$OSTYPE" = "cygwin" ] ; then
export AUTOBUILD="$(cygpath -u $AUTOBUILD)"
fi

# Load autobuild provided shell functions and variables
set +x
eval "$("$AUTOBUILD" source_environment)"
set -x

stage="$(pwd)"

mkdir -p "$stage/lib/release"
case "$AUTOBUILD_PLATFORM" in
	"windows")
		# Do something windowsy
	;;
	"darwin")
		cmake ../
		make

		# Copy the new libs
		cp "$stage/Source/lib/libnd_hacdConvexDecomposition.a" "$stage/lib/release/"
		cp "$stage/Source/Pathing/libnd_Pathing.a" "$stage/lib/release/"
		cp "$stage/Source/HACD_Lib/libhacd.a" "$stage/lib/release/"
	;;
	"linux")
		cmake ../
		make

		# Copy the new libs (just a guess)
		cp "$stage/Source/lib/libnd_hacdConvexDecomposition.a" "$stage/lib/release/"
		cp "$stage/Source/Pathing/libnd_Pathing.a" "$stage/lib/release/"
		cp "$stage/Source/HACD_Lib/libhacd.a" "$stage/lib/release/"
	;;
esac

# Copy headers
mkdir -p "$stage/include"
cp "$stage/../Source/lib/LLConvexDecomposition.h" "$stage/include/"
cp "$stage/../Source/lib/ndConvexDecomposition.h" "$stage/include/"
cp "$stage/../Source/Pathing/llpathinglib.h" "$stage/include/"
cp "$stage/../Source/Pathing/llphysicsextensions.h" "$stage/include/"


mkdir -p "$stage/LICENSES"
cp "../COPYING.LESSER" "$stage/LICENSES/ndphysicsstub.txt"
pass

#!/bin/bash

cd "$(dirname "$0")"

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

set +x
eval "$("$AUTOBUILD" source_environment)"
set -x

stage="$(pwd)/stage"

if [ -d "${stage}" ]
then
 rm -rf "${stage}/lib"
 rm -rf "${stage}/include"
fi

build=${AUTOBUILD_BUILD_ID:=0}
echo "1.${build}" > "${stage}/VERSION.txt"

mkdir -p "$stage/lib/debug"
mkdir -p "$stage/lib/release"

cp version.txt ${stage}/version.txt

if [ ! -d "build-${AUTOBUILD_PLATFORM}" ]
then
  mkdir "build-${AUTOBUILD_PLATFORM}"
else
  rm -rf "build-${AUTOBUILD_PLATFORM}"
  mkdir "build-${AUTOBUILD_PLATFORM}"
fi

pushd "build-${AUTOBUILD_PLATFORM}"
    case "${AUTOBUILD_PLATFORM}" in
        windows*)
            load_vsvars

            if [ "${AUTOBUILD_WIN_VSPLATFORM}" = "Win32" ] ; then
              cmake .. -G "Visual Studio 12"
            else
              cmake .. -G "Visual Studio 12 Win64"
            fi

            build_sln "Project.sln" "Release|$AUTOBUILD_WIN_VSPLATFORM" "hacd"
            build_sln "Project.sln" "Release|$AUTOBUILD_WIN_VSPLATFORM" "nd_hacdConvexDecomposition"
            build_sln "Project.sln" "Release|$AUTOBUILD_WIN_VSPLATFORM" "nd_Pathing"

            build_sln "Project.sln" "Debug|$AUTOBUILD_WIN_VSPLATFORM" "hacd"
            build_sln "Project.sln" "Debug|$AUTOBUILD_WIN_VSPLATFORM" "nd_hacdConvexDecomposition"
            build_sln "Project.sln" "Debug|$AUTOBUILD_WIN_VSPLATFORM" "nd_Pathing"

            cp "Source/HACD_Lib/Debug/hacd.lib" "$stage/lib/debug"
            cp "Source/HACD_Lib/Release/hacd.lib" "$stage/lib/release"

            cp "Source/lib/Debug/nd_hacdConvexDecomposition.lib" "$stage/lib/debug"
            cp "Source/lib/Release/nd_hacdConvexDecomposition.lib" "$stage/lib/release"

            cp "Source/Pathing/Debug/nd_Pathing.lib" "$stage/lib/debug"
            cp "Source/Pathing/Release/nd_Pathing.lib" "$stage/lib/release"
        ;;

        darwin*)
        cmake "-DCMAKE_OSX_ARCHITECTURES=x86_64;i386" \
            -DCMAKE_OSX_DEPLOYMENT_TARGET=10.7 \
            -DCMAKE_OSX_SYSROOT=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/ \
            -DCMAKE_CXX_FLAGS="-std=c++11 -stdlib=libc++" \
            ../
        make

        # Copy the new libs
        cp "Source/lib/libnd_hacdConvexDecomposition.a" "$stage/lib/release/"
        cp "Source/Pathing/libnd_Pathing.a" "$stage/lib/release/"
        cp "Source/HACD_Lib/libhacd.a" "$stage/lib/release/"
        ;;
            
        linux*)
        cmake ../
        make

        # Copy the new libs (just a guess)
        cp "Source/lib/libnd_hacdConvexDecomposition.a" "$stage/lib/release/"
        cp "Source/Pathing/libnd_Pathing.a" "$stage/lib/release/"
        cp "Source/HACD_Lib/libhacd.a" "$stage/lib/release/"
        ;;
    esac
popd

mkdir -p "$stage/LICENSES"
cp ndPhysicsStub.txt "$stage/LICENSES"

mkdir -p "$stage/include"
cp Source/lib/LLConvexDecomposition.h "$stage/include/llconvexdecomposition.h"
cp Source/Pathing/llpathinglib.h "$stage/include"
cp Source/Pathing/llphysicsextensions.h "$stage/include"
cp Source/lib/ndConvexDecomposition.h "$stage/include"


#!/bin/sh

# turn on verbose debugging output for parabuild logs.
set -x
# make errors fatal
set -e

if [ -z "$AUTOBUILD" ] ; then 
    fail
fi

if [ "$OSTYPE" = "cygwin" ] ; then
    export AUTOBUILD="$(cygpath -u $AUTOBUILD)"
fi

# load autbuild provided shell functions and variables
set +x
eval "$("$AUTOBUILD" source_environment)"
set -x

top="$(pwd)"
cd "Source"
    case "$AUTOBUILD_PLATFORM" in
        "windows")
            build_sln "LLConvexDecomposition.sln" "Debug|Win32"
            build_sln "LLConvexDecomposition.sln" "Release|Win32"
            mkdir -p ../stage/libraries/i686-win32/lib/{debug,release}
            cp "lib/debug/LLConvexDecompositionStub.lib" \
                "../stage/libraries/i686-win32/lib/debug/LLConvexDecompositionStub.lib"
            cp "lib/debug/LLConvexDecompositionStub.pdb" \
                "../stage/libraries/i686-win32/lib/debug/LLConvexDecompositionStub.pdb"
            cp "lib/release/LLConvexDecompositionStub.lib" \
                "../stage/libraries/i686-win32/lib/release/LLConvexDecompositionStub.lib"
        ;;
        "darwin")
			libdir="$top/stage/libraries/universal-darwin/"
            mkdir -p "$libdir"/lib_{debug,release}
			make -C lib -f Makefile_mac clean
			make -C lib -f Makefile_mac 
			cp "lib/debug_stub/libllconvexdecompositionstub.a" \
				"$libdir/lib_debug/libllconvexdecompositionstub.a"
			cp "lib/release_stub/libllconvexdecompositionstub.a" \
				"$libdir/lib_release/libllconvexdecompositionstub.a"
		;;
        "linux")
			libdir="$top/stage/libraries/i686-linux/"
            mkdir -p "$libdir"/lib_{debug,release}_client
			make -C lib clean
			make -C lib
			cp "lib/debug_stub/libllconvexdecompositionstub.a" \
				"$libdir/lib_debug_client/libllconvexdecompositionstub.a"
			cp "lib/release_stub/libllconvexdecompositionstub.a" \
				"$libdir/lib_release_client/libllconvexdecompositionstub.a"
        ;;
    esac
    mkdir -p "../stage/libraries/include"
    cp "lib/LLConvexDecomposition.h" "../stage/libraries/include/llconvexdecomposition.h"
    mkdir -p ../stage/LICENSES
    cp LICENSE_STUB.txt ../stage/LICENSES/LLConvexDecompositionStubLicense.txt
cd "$top"

pass


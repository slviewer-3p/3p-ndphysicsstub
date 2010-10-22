/** 
 * @file Makefile
 * @author nyx@lindenlab.com
 * @brief Makefile for building llconvexdecompositionstub
 *
 * $LicenseInfo:firstyear=2002&license=viewerlgpl$
 * Second Life Viewer Source Code
 * Copyright (C) 2010, Linden Research, Inc.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation;
 * version 2.1 of the License only.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * Linden Research, Inc., 945 Battery Street, San Francisco, CA  94111  USA
 * $/LicenseInfo$
 */

# example Makefile

HEADERS_STUB:=LLConvexDecomposition.h LLConvexDecompositionStubImpl.h
SOURCES_STUB:=LLConvexDecomposition.cpp LLConvexDecompositionStubImpl.cpp

OBJECTS_RELEASE_STUB:=$(addprefix release_stub/,$(SOURCES_STUB:.cpp=.o))
OBJECTS_DEBUG_STUB:=$(addprefix debug_stub/,$(SOURCES_STUB:.cpp=.o))

CXXFLAGS_STUB:= -DLL_CONVEX_DECOMP_STUB
RELEASE_CXXFLAGS:=-O3 -m32 -msse2 -Wno-invalid-offsetof $(CXXFLAGS)
DEBUG_CXXFLAGS:=-g -m32 -msse2 -Wno-invalid-offsetof $(CXXFLAGS)

all: stub stub_debug

stub: release_stub/libllconvexdecompositionstub.a

stub_debug: debug_stub/libllconvexdecompositionstub.a

#All .unpacked dependencies will rely on a corresponding .dir
%/.unpacked: %.dir

release_stub/libllconvexdecompositionstub.a: $(OBJECTS_RELEASE_STUB)
	$(AR) rc $@ $^

debug_stub/libllconvexdecompositionstub.a: $(OBJECTS_DEBUG_STUB)
	$(AR) rc $@ $^

debug_stub/%.o:	%.cpp debug_stub.dir
	$(CXX) -o $@ -c $< $(DEBUG_CXXFLAGS) $(CXXFLAGS_STUB)

release_stub/%.o:	%.cpp release_stub.dir
	$(CXX) -o $@ -c $< $(RELEASE_CXXFLAGS) $(CXXFLAGS_STUB)

# Create directories with names of the target minus '.dir' suffix
%.dir:
	mkdir -p $*; rm -f $*/*

clean:
	$(RM) -rf release_stub debug_stub 


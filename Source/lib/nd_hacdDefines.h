/**
 * copyright 2011 sl.nicky.ml@googlemail.com
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
 */

#ifndef ND_HACD_DEFINES_H
#define ND_HACD_DEFINES_H

#include "hacdHACD.h"

#define NUM_STAGES 1

typedef unsigned short hacdUINT16;
typedef unsigned int hacdUINT32;

typedef HACD::HACD tHACD;
typedef HACD::Vec3< double > tVecDbl;
typedef HACD::Vec3< long > tVecLong;

typedef tVecLong (*fFromIXX)( void *&, int );

const int MAX_VERTICES_PER_HULL     = 256;    // see http://wiki.secondlife.com/wiki/Mesh/Mesh_physics
const int MIN_NUMBER_OF_CLUSTERS    = 1;
const int CONCAVITY_FOR_SINGLE_HULL = 10000;  // Use a high value so HACD will generate just one hull

#endif

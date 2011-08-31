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

#endif

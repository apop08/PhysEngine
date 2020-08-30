#pragma once
#define _USE_MATH_DEFINES
#include <math.h> // sqrt
#include <cfloat>
#include "Config.h"

// allows for easy changing from floats to double

#define USEFLOATS

#ifdef USEFLOATS
    #define SINGLE_PRECISION
    typedef float FLOAT;

    #define FLOATMax FLT_MAX;
    #define FLOATSqrt sqrtf
    #define FLOATAbs fabsf

    #define FLOATSin sinf
    #define FLOATCos cosf

    #define FLOATExp expf
    #define FLOATPow powf

    #define FLOATFMod fmodf

    #define FLOATEpsilon FLT_EPSILON

    #define FLOATPI float(M_PI)

#else
    #define DOUBLE_PRECISION
    typedef float FLOAT;

    #define FLOATMax DBL_MAX;
    #define FLOATSqrt sqrt
    #define FLOATAbs fabs

    #define FLOATSin sin
    #define FLOATCos cos

    #define FLOATExp exp
    #define FLOATPow pow

    #define FLOATFMod fmod

    #define FLOATEpsilon DBL_EPSILON

    #define FLOATPI M_PI
#endif
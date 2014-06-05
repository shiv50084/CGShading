/* ############################################################################
Name           : transformations.h
University     : University of Edinburgh
Project        : Practical 1, Computer Graphics
Student        : Stavros Vagionitis(s0954319) 
Description    : Header file for 3D transformations

Student        Date           Action
============== ============== =================================================
S. Vagionitis  16/10/2009     Creation
############################################################################ */
#ifndef _TRANSFORMATIONS_H
#define _TRANSFORMATIONS_H

#include "demo.h"

void Translation_3D_Point(float, float, float, VECTOR3F *);
VECTOR3F *Translation_3D_Vertices(float, float, float, TRIANGLE *, int, VECTOR3F *, int);

void Scale_3D_Point(float, float, float, VECTOR3F *);
VECTOR3F *Scale_3D_Vertices(float, float, float, TRIANGLE *, int, VECTOR3F *, int);

void Rotation_X_Axis_3D_Point(float, VECTOR3F *);
VECTOR3F* Rotation_X_Axis_3D_Vertices(float, TRIANGLE *, int, VECTOR3F *, int);

void Rotation_Y_Axis_3D_Point(float, VECTOR3F *);
VECTOR3F* Rotation_Y_Axis_3D_Vertices(float, TRIANGLE *, int, VECTOR3F *, int);

void Rotation_Z_Axis_3D_Point(float, VECTOR3F *);
VECTOR3F* Rotation_Z_Axis_3D_Vertices(float, TRIANGLE *, int, VECTOR3F *, int);

void Rotation_Arbitrary_Axis_3D_Point(float, float, float, float, VECTOR3F *);
VECTOR3F* Rotation_Arbitrary_Axis_3D_Vertices(float, float, float, float, TRIANGLE *, int, VECTOR3F *, int);


#endif //_TRANSFORMATIONS_H

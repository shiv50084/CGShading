/* ############################################################################
Name           : projections.h
University     : University of Edinburgh
Project        : Practical 1, Computer Graphics
Student        : Stavros Vagionitis(s0954319) 
Description    : Header file for 3D projections

Student        Date           Action
============== ============== =================================================
S. Vagionitis  17/10/2009     Creation
############################################################################ */
#ifndef _PROJECTIONS_H
#define _PROJECTIONS_H

#include "demo.h"

void Parallel_Projection_3D_Point(VECTOR3F, VECTOR3F, VECTOR3F *);
VECTOR3F *Parallel_Projection_3D_Vertices(VECTOR3F, VECTOR3F, TRIANGLE *, int, VECTOR3F *, int);

void Parallel_Projection_3D_Point_Simple(VECTOR3F *);
VECTOR3F *Parallel_Projection_3D_Vertices_Simple(TRIANGLE *, int, VECTOR3F *, int);

void Perspective_Projection_3D_Point(VECTOR3F, VECTOR3F, VECTOR3F *);
VECTOR3F *Perspective_Projection_3D_Vertices(VECTOR3F, VECTOR3F, TRIANGLE *, int, VECTOR3F *, int);

void Perspective_Projection_3D_Point_Simple(float, VECTOR3F *);
VECTOR3F *Perspective_Projection_3D_Vertices_Simple(float, TRIANGLE *, int, VECTOR3F *, int);

#endif //_PROJECTIONS_H

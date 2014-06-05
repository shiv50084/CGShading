/* ############################################################################
Name           : vectors.h
University     : University of Edinburgh
Project        : Practical 1, Computer Graphics
Student        : Stavros Vagionitis(s0954319) 
Description    : Header file for Vectors.

Student        Date           Action
============== ============== =================================================
S. Vagionitis  18/10/2009     Creation
############################################################################ */
#ifndef _VECTORS_H
#define _VECTORS_H

#include "demo.h"

void V2SquaredLength(VECTOR3F, float*);
void V2Length(VECTOR3F, float*);
void V2Normalize(VECTOR3F*);
void V2Dot(VECTOR3F, VECTOR3F, float*);

void V3SquaredLength(VECTOR3F, float*);
void V3Length(VECTOR3F, float*);
void V3Normalize(VECTOR3F*);
void V3Dot(VECTOR3F, VECTOR3F, float*);
void V3Cross(VECTOR3F, VECTOR3F, VECTOR3F*);

void Normal_Vector_Triangle(VECTOR3F, VECTOR3F, VECTOR3F, VECTOR3F *);
#endif //_VECTORS_H

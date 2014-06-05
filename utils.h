/* ############################################################################
Name           : utils.h
University     : University of Edinburgh
Project        : Practical 1, Computer Graphics
Student        : Stavros Vagionitis(s0954319) 
Description    : Header file for Utils

Student        Date           Action
============== ============== =================================================
S. Vagionitis  19/10/2009     Creation
############################################################################ */
#ifndef _UTILS_H
#define _UTILS_H

#include "demo.h"

unsigned char Check_Point_In_Triangle(VECTOR3F, VECTOR3F, VECTOR3F, VECTOR3F, VECTOR3F*);
void Color_Point(VECTOR3F, COLOR);
void Color_Triangle(VECTOR3F, VECTOR3F, VECTOR3F, COLOR);
void Barycentric_Coordinates(VECTOR3F, VECTOR3F, VECTOR3F, VECTOR3F, VECTOR3F *);
void Calculate_Normalize_Vertex_Normals(TRIANGLE *, int, VECTOR3F *, int, VECTOR3F *);

#endif //_UTILS_H

/* ############################################################################
Name           : shadings.h
University     : University of Edinburgh
Project        : Practical 1, Computer Graphics
Student        : Stavros Vagionitis(s0954319) 
Description    : Header file for 3D shadings

Student        Date           Action
============== ============== =================================================
S. Vagionitis  18/10/2009     Creation
############################################################################ */
#ifndef _SHADINGS_H
#define _SHADINGS_H

#include "demo.h"

void Ambient_Lighting(float, COLOR, COLOR *);
void Diffuse_Lighting(float, float, COLOR, COLOR *);
void Diffuse_Lighting_Vectors(float, VECTOR3F, VECTOR3F, COLOR, COLOR *);
void Specular_Lighting(float, float, float, COLOR, COLOR *);
void Specular_Lighting_Vectors(float, float, VECTOR3F, VECTOR3F, COLOR, COLOR *);
void Lighting(float, float, float, float, VECTOR3F, VECTOR3F, VECTOR3F, COLOR, COLOR, COLOR, COLOR *);

void Flat_Shading(VECTOR3F, TRIANGLE *, int, VECTOR3F *, int, int, int, COLOR);
void Gouraud_Shading(VECTOR3F, TRIANGLE *, int, VECTOR3F *, int, int, int, COLOR);
void Phong_Shading(VECTOR3F, VECTOR3F, TRIANGLE *, int, VECTOR3F *, int, int, int, COLOR);

#endif //_SHADINGS_H

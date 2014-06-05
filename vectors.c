/* ############################################################################
Name           : vectors.c
University     : University of Edinburgh
Project        : Practical 1, Computer Graphics
Student        : Stavros Vagionitis(s0954319)
Description    : Functions regarding 2D and 3D computations.
		 Most of them are taken from Graphic Gems Repository
		 (http://tog.acm.org/resources/GraphicsGems/)

Procedure                     	  	Description
================================= 	=================================================
V2SquaredLength				Calculate the squared lenght of a 2D vector
V2Length				Calculate the lenght of a 2D vector
V2Normalize				Normalize a 2D vector
V2Dot					Calculate the dot product of 2D vector
V3SquaredLength				Calculate the squared lenght of a 3D vector
V3Length				Calculate the lenght of a 3D vector
V3Normalize				Normalize a 3D vector
V3Dot					Calculate the dot product of 3D vector
V3Cross					Calculate the cross product of 3D vector
Normal_Vector_Triangle			Calculate the normal vector of a triangle.

Globals        Type           Description
============== ============== =====================================================

Student        Date           Action
============== ============== =====================================================
S. Vagionitis  18/10/2009     Creation
############################################################################ */

#define _VECTORS_C
#include "vectors.h"

	
void  V2SquaredLength(VECTOR3F input, float *result) 
{
*result = (input.x * input.x) + 
	  (input.y * input.y);
}

void V2Length(VECTOR3F input, float *result)
{
float temp = 0.0;

V2SquaredLength(input, &temp);

*result = sqrt(temp);
}

void V2Normalize(VECTOR3F *result)
{
float len = 0.0;

V2Length(*result, &len); 

if (len != 0.0) 
	{ 
	result->x /= len; 
	result->y /= len; 
	}

}

void V2Dot(VECTOR3F a, VECTOR3F b, float *result)
{
*result = (a.x*b.x) + 
	  (a.y*b.y);
}


void V3SquaredLength(VECTOR3F input, float *result)
{
*result = (input.x * input.x) + 
	  (input.y * input.y) + 
	  (input.z * input.z);
}


void V3Length(VECTOR3F input, float *result)
{
float temp = 0.0;

V3SquaredLength(input, &temp);

*result = sqrt(temp);
}

void V3Normalize(VECTOR3F *result)
{
float len = 0.0;

V3Length(*result, &len); 

if (len != 0.0) 
	{ 
	result->x /= len; 
	result->y /= len; 
	result->z /= len; 
	}

}

void V3Dot(VECTOR3F a, VECTOR3F b, float *result)
{
*result = (a.x*b.x) + 
	  (a.y*b.y) + 
	  (a.z*b.z);
}

void V3Cross(VECTOR3F a, VECTOR3F b, VECTOR3F *result)
{

result->x = (a.y*b.z) - (a.z*b.y); 
result->y = (a.z*b.x) - (a.x*b.z); 
result->z = (a.x*b.y) - (a.y*b.x); 

}



void Normal_Vector_Triangle(VECTOR3F V1, VECTOR3F V2, VECTOR3F V3, VECTOR3F *NV)
{
float Qx = 0.0, Qy = 0.0, Qz = 0.0, 
      Px = 0.0, Py = 0.0, Pz = 0.0;

Qx = V1.x-V2.x;
Qy = V1.y-V2.y;
Qz = V1.z-V2.z;
Px = V2.x-V3.x;
Py = V2.y-V3.y;
Pz = V2.z-V3.z;

NV->x = Qy*Pz - Qz*Py;
NV->y = Qz*Px - Qx*Pz;
NV->z = Qx*Py - Qy*Px;

V3Normalize(NV);
}



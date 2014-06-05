/* ############################################################################
Name           : transformations.c
University     : University of Edinburgh
Project        : Practical 1, Computer Graphics
Student        : Stavros Vagionitis(s0954319)
Description    : Implements 3D transformations

Procedure                     	  	Description
================================= 	=================================================
Translation_3D_Point			Translation of a point in 3D
Scale_3D_Point				Scale of a point in 3D
Rotation_X_Axis_3D_Point		Rotate in X axis a point in 3D
Rotation_Y_Axis_3D_Point		Rotate in Y axis a point in 3D
Rotation_Z_Axis_3D_Point		Rotate in Z axis a point in 3D
Rotation_Arbitrary_Axis_3D_Point	Rotate in arbitrary axis a point in 3D

Globals        Type           Description
============== ============== =====================================================

Student        Date           Action
============== ============== =====================================================
S. Vagionitis  16/10/2009     Creation
############################################################################ */

#define _TRANSFORMATIONS_C
#include "transformations.h"

/* ############################################################################
Name           : Translation_3D_Point
Description    : Moves the point point_3d to the offset vector specified
		 by (dx, dy, dz)

Arguments      	Type           	Description
============== 	============== 	=================================================
dx		float		X offset
dy		float		Y offset
dz		float		Z offset
point_3d	VECTOR3F *	Point to be moved

Return Values                 Description
============================= =================================================

Globals        Type           Description
============== ============== =================================================

Locals         Type           Description
============== ============== =================================================

############################################################################ */
void Translation_3D_Point(float dx, float dy, float dz, VECTOR3F *point_3d)
{
point_3d->x += dx;
point_3d->y += dy;
point_3d->z += dz;
}

/* ############################################################################
Name           : Translation_3D_Vertices
Description    : Moves the point of all vertices to the offset vector specified
		 by (dx, dy, dz)

Arguments      	Type           	Description
============== 	============== 	=================================================
dx		float		X offset
dy		float		Y offset
dz		float		Z offset
triangles	TRIANGLE *	Triangle verices
max_triangles	int		Max number of triangles
vectors		VECTOR3F *	Vectors of vertices
max_vectors	int		Max number of vectors

Return Values                 	Description
============================= 	=================================================
Output				The translated vertices

Globals        Type           Description
============== ============== =================================================

Locals         Type           Description
============== ============== =================================================

############################################################################ */
VECTOR3F *Translation_3D_Vertices(float dx, float dy, float dz, TRIANGLE *triangles, int max_triangles, VECTOR3F *vectors, int max_vectors)
{
int minx = 0, maxx = 0, miny = 0, maxy = 0;
int i = 0, j = 0, vector = 0, triangle = 0;
VECTOR3F V1, V2, V3, *Output;

if (( Output = (VECTOR3F *) malloc(max_vectors * sizeof(VECTOR3F) ) ) == NULL)
	{
	printf("ERROR ALLOCATING (%u) Translation\n", max_vectors);
	exit(0);
	}


for (triangle = 0; triangle < max_triangles; triangle++)
	{

	V1 = vectors[triangles[triangle].v1];
	V2 = vectors[triangles[triangle].v2];
	V3 = vectors[triangles[triangle].v3];

	Translation_3D_Point(dx, dy, dz, &V1);
	Translation_3D_Point(dx, dy, dz, &V2);
	Translation_3D_Point(dx, dy, dz, &V3);

	Output[triangles[triangle].v1] = V1;
	Output[triangles[triangle].v2] = V2;
	Output[triangles[triangle].v3] = V3;
	}

return Output;
}


/* ############################################################################
Name           : Scale_3D_Point
Description    : Changes the point scale by a specified scale
		 vector (sx, sy, sz)

Arguments      	Type           	Description
============== 	============== 	=================================================
sx		float		X scale offset
sy		float		Y scale offset
sz		float		Z scale offset
point_3d	VECTOR3F *	Point to be scaled

Return Values                 Description
============================= =================================================

Globals        Type           Description
============== ============== =================================================

Locals         Type           Description
============== ============== =================================================

############################################################################ */
void Scale_3D_Point(float sx, float sy, float sz, VECTOR3F *point_3d)
{

point_3d->x *= sx;
point_3d->y *= sy;
point_3d->z *= sz;

}

/* ############################################################################
Name           : Scale_3D_Vertices
Description    : Changes all points of vertices scaled by a specified scale
		 vector (sx, sy, sz)

Arguments      	Type           	Description
============== 	============== 	=================================================
sx		float		X scale offset
sy		float		Y scale offset
sz		float		Z scale offset
triangles	TRIANGLE *	Triangle verices
max_triangles	int		Max number of triangles
vectors		VECTOR3F *	Vectors of vertices
max_vectors	int		Max number of vectors


Return Values                 	Description
============================= 	=================================================
Output				The scaled vertices

Globals        Type           Description
============== ============== =================================================

Locals         Type           Description
============== ============== =================================================

############################################################################ */
VECTOR3F* Scale_3D_Vertices(float sx, float sy, float sz, TRIANGLE *triangles, int max_triangles, VECTOR3F *vectors, int max_vectors)
{
int minx = 0, maxx = 0, miny = 0, maxy = 0;
int i = 0, j = 0, vector = 0, triangle = 0;
VECTOR3F V1, V2, V3, *Output;

if (( Output = (VECTOR3F *) malloc(max_vectors * sizeof(VECTOR3F) ) ) == NULL)
	{
	printf("ERROR ALLOCATING (%u) Scale\n", max_vectors);
	exit(0);
	}

for (triangle = 0; triangle < max_triangles; triangle++)
	{
	V1 = vectors[triangles[triangle].v1];
	V2 = vectors[triangles[triangle].v2];
	V3 = vectors[triangles[triangle].v3];

	Scale_3D_Point(sx, sy, sz, &V1);
	Scale_3D_Point(sx, sy, sz, &V2);
	Scale_3D_Point(sx, sy, sz, &V3);

	Output[triangles[triangle].v1] = V1;
	Output[triangles[triangle].v2] = V2;
	Output[triangles[triangle].v3] = V3;
	}

return Output;
}

/* ############################################################################
Name           : Rotation_X_Axis_3D_Point
Description    : Rotate a point around X axis in 
		 a specified angle. 

Arguments      	Type           	Description
============== 	============== 	=================================================
theta		float		Rotation angle
point_3d	VECTOR3F *	Point to be rotated

Return Values                 Description
============================= =================================================

Globals        Type           Description
============== ============== =================================================

Locals         	Type           	Description
============== 	============== 	=================================================
temp_point	VECTOR3F	Temporary value of point_3d
############################################################################ */
void Rotation_X_Axis_3D_Point(float theta, VECTOR3F *point_3d)
{
VECTOR3F temp_point;

temp_point.x = point_3d->x;
temp_point.y = point_3d->y;
temp_point.z = point_3d->z;

point_3d->y = temp_point.y*cos (theta*PI/180) - 
			  temp_point.z*sin (theta*PI/180);
point_3d->z = temp_point.y*sin (theta*PI/180) + 
			  temp_point.z*cos (theta*PI/180);
point_3d->x = temp_point.x;
}

/* ############################################################################
Name           : Rotation_X_Axis_3D_Vertices
Description    : Rotate all points of vertices around X axis in 
		 a specified angle. 

Arguments      	Type           	Description
============== 	============== 	=================================================
theta		float		Rotation angle
triangles	TRIANGLE *	Triangle verices
max_triangles	int		Max number of triangles
vectors		VECTOR3F *	Vectors of vertices
max_vectors	int		Max number of vectors

Return Values                 	Description
============================= 	=================================================
Output				The rotated vertices

Globals        Type           Description
============== ============== =================================================

Locals         	Type           	Description
============== 	============== 	=================================================
############################################################################ */
VECTOR3F* Rotation_X_Axis_3D_Vertices(float theta, TRIANGLE *triangles, int max_triangles, VECTOR3F *vectors, int max_vectors)
{
int minx = 0, maxx = 0, miny = 0, maxy = 0;
int i = 0, j = 0, vector = 0, triangle = 0;
VECTOR3F V1, V2, V3, *Output;

if (( Output = (VECTOR3F *) malloc(max_vectors * sizeof(VECTOR3F) ) ) == NULL)
	{
	printf("ERROR ALLOCATING (%u) Rotation_X_Axis\n", max_vectors);
	exit(0);
	}

for (triangle = 0; triangle < max_triangles; triangle++)
	{
	V1 = vectors[triangles[triangle].v1];
	V2 = vectors[triangles[triangle].v2];
	V3 = vectors[triangles[triangle].v3];

	Rotation_X_Axis_3D_Point(theta, &V1);
	Rotation_X_Axis_3D_Point(theta, &V2);
	Rotation_X_Axis_3D_Point(theta, &V3);

	Output[triangles[triangle].v1] = V1;
	Output[triangles[triangle].v2] = V2;
	Output[triangles[triangle].v3] = V3;
	}

return Output;
}

/* ############################################################################
Name           : Rotation_Y_Axis_3D_Point
Description    : Rotate a point around Y axis in 
		 a specified angle. 

Arguments      	Type           	Description
============== 	============== 	=================================================
theta		float		Rotation angle
point_3d	VECTOR3F *	Point to be rotated

Return Values                 Description
============================= =================================================

Globals        Type           Description
============== ============== =================================================

Locals         	Type           	Description
============== 	============== 	=================================================
temp_point	VECTOR3F	Temporary value of point_3d
############################################################################ */
void Rotation_Y_Axis_3D_Point(float theta, VECTOR3F *point_3d)
{
VECTOR3F temp_point;

temp_point.x = point_3d->x;
temp_point.y = point_3d->y;
temp_point.z = point_3d->z;

point_3d->z = temp_point.z*cos (theta*PI/180) - 
			  temp_point.x*sin (theta*PI/180);
point_3d->x = temp_point.z*sin (theta*PI/180) + 
			  temp_point.x*cos (theta*PI/180);
point_3d->y = temp_point.y;
}

/* ############################################################################
Name           : Rotation_Y_Axis_3D_Vertices
Description    : Rotate all points of vertices around Y axis in 
		 a specified angle. 

Arguments      	Type           	Description
============== 	============== 	=================================================
theta		float		Rotation angle
triangles	TRIANGLE *	Triangle verices
max_triangles	int		Max number of triangles
vectors		VECTOR3F *	Vectors of vertices
max_vectors	int		Max number of vectors

Return Values                 	Description
============================= 	=================================================
Output				The rotated vertices

Globals        Type           Description
============== ============== =================================================

Locals         	Type           	Description
============== 	============== 	=================================================
############################################################################ */
VECTOR3F* Rotation_Y_Axis_3D_Vertices(float theta, TRIANGLE *triangles, int max_triangles, VECTOR3F *vectors, int max_vectors)
{
int minx = 0, maxx = 0, miny = 0, maxy = 0;
int i = 0, j = 0, vector = 0, triangle = 0;
VECTOR3F V1, V2, V3, *Output;

if (( Output = (VECTOR3F *) malloc(max_vectors * sizeof(VECTOR3F) ) ) == NULL)
	{
	printf("ERROR ALLOCATING (%u) Rotation_Y_Axis\n", max_vectors);
	exit(0);
	}

for (triangle = 0; triangle < max_triangles; triangle++)
	{
	V1 = vectors[triangles[triangle].v1];
	V2 = vectors[triangles[triangle].v2];
	V3 = vectors[triangles[triangle].v3];

	Rotation_Y_Axis_3D_Point(theta, &V1);
	Rotation_Y_Axis_3D_Point(theta, &V2);
	Rotation_Y_Axis_3D_Point(theta, &V3);

	Output[triangles[triangle].v1] = V1;
	Output[triangles[triangle].v2] = V2;
	Output[triangles[triangle].v3] = V3;
	}

return Output;
}

/* ############################################################################
Name           : Rotation_Z_Axis_3D_Point
Description    : Rotate a point around Z axis in 
		 a specified angle. 

Arguments      	Type           	Description
============== 	============== 	=================================================
theta		float		Rotation angle
point_3d	VECTOR3F *	Point to be rotated

Return Values                 Description
============================= =================================================

Globals        Type           Description
============== ============== =================================================

Locals         	Type           	Description
============== 	============== 	=================================================
temp_point	VECTOR3F	Temporary value of point_3d
############################################################################ */
void Rotation_Z_Axis_3D_Point(float theta, VECTOR3F *point_3d)
{
VECTOR3F temp_point;

temp_point.x = point_3d->x;
temp_point.y = point_3d->y;
temp_point.z = point_3d->z;

point_3d->x = temp_point.x*cos (theta*PI/180) - 
			  temp_point.y*sin (theta*PI/180);
point_3d->y = temp_point.x*sin (theta*PI/180) + 
		      temp_point.y*cos (theta*PI/180);
point_3d->z = temp_point.z;
}

/* ############################################################################
Name           : Rotation_Z_Axis_3D_Vertices
Description    : Rotate all points of vertices around Z axis in 
		 a specified angle. 

Arguments      	Type           	Description
============== 	============== 	=================================================
theta		float		Rotation angle
triangles	TRIANGLE *	Triangle verices
max_triangles	int		Max number of triangles
vectors		VECTOR3F *	Vectors of vertices
max_vectors	int		Max number of vectors

Return Values                 	Description
============================= 	=================================================
Output				The rotated vertices

Globals        Type           Description
============== ============== =================================================

Locals         	Type           	Description
============== 	============== 	=================================================
############################################################################ */
VECTOR3F* Rotation_Z_Axis_3D_Vertices(float theta, TRIANGLE *triangles, int max_triangles, VECTOR3F *vectors, int max_vectors)
{
int minx = 0, maxx = 0, miny = 0, maxy = 0;
int i = 0, j = 0, vector = 0, triangle = 0;
VECTOR3F V1, V2, V3, *Output;

if (( Output = (VECTOR3F *) malloc(max_vectors * sizeof(VECTOR3F) ) ) == NULL)
	{
	printf("ERROR ALLOCATING (%u) Rotation_Z_Axis\n", max_vectors);
	exit(0);
	}

for (triangle = 0; triangle < max_triangles; triangle++)
	{
	V1 = vectors[triangles[triangle].v1];
	V2 = vectors[triangles[triangle].v2];
	V3 = vectors[triangles[triangle].v3];

	Rotation_Z_Axis_3D_Point(theta, &V1);
	Rotation_Z_Axis_3D_Point(theta, &V2);
	Rotation_Z_Axis_3D_Point(theta, &V3);

	Output[triangles[triangle].v1] = V1;
	Output[triangles[triangle].v2] = V2;
	Output[triangles[triangle].v3] = V3;
	}

return Output;
}

/* ############################################################################
Name           : Rotation_Arbitrary_Axis_3D_Point
Description    : Rotation of a point in 3 dimensional space 
		 by theta about an arbitrary axes defined by
		 an offset vector (ux, uy, uz).

Arguments      	Type           	Description
============== 	============== 	=================================================
ux		float		X offset
uy		float		Y offset
uz		float		Z offset
theta		float		Rotation angle
point_3d	VECTOR3F *	Point to be rotated

Return Values                 Description
============================= =================================================

Globals        Type           Description
============== ============== =================================================

Locals         Type           Description
============== ============== =================================================

############################################################################ */
void Rotation_Arbitrary_Axis_3D_Point(float ux, float uy, float uz, float theta, VECTOR3F *point_3d)
{
/*(1) translate space so that the rotation axis passes through the origin*/
Translation_3D_Point(ux, uy, uz, point_3d);
/*(2) rotate space about the x axis so that the rotation axis lies in the xz plane*/
Rotation_X_Axis_3D_Point(-90.0, point_3d);
/*(3) rotate space about the y axis so that the rotation axis lies along the z axis*/
Rotation_Y_Axis_3D_Point(-90.0, point_3d);
/*(4) perform the desired rotation by theta about the z axis*/
Rotation_Z_Axis_3D_Point(theta, point_3d);
/*(5) apply the inverse of step (3)*/
Rotation_Y_Axis_3D_Point(90.0, point_3d);
/*(6) apply the inverse of step (2)*/
Rotation_X_Axis_3D_Point(90.0, point_3d);
/*(7) apply the inverse of step (1)*/
Translation_3D_Point(-1.0*ux, -1.0*uy, -1.0*uz, point_3d);
}

/* ############################################################################
Name           : Rotation_Arbitrary_Axis_3D_Vertices
Description    : Rotation of all points of vertices in 3 dimensional space 
		 by theta about an arbitrary axes defined by
		 an offset vector (ux, uy, uz).

Arguments      	Type           	Description
============== 	============== 	=================================================
ux		float		X offset
uy		float		Y offset
uz		float		Z offset
theta		float		Rotation angle
triangles	TRIANGLE *	Triangle verices
max_triangles	int		Max number of triangles
vectors		VECTOR3F *	Vectors of vertices
max_vectors	int		Max number of vectors


Return Values                 	Description
============================= 	=================================================
Output				The arbitrary rotated vertices

Globals        Type           Description
============== ============== =================================================

Locals         Type           Description
============== ============== =================================================

############################################################################ */
VECTOR3F* Rotation_Arbitrary_Axis_3D_Vertices(float ux, float uy, float uz, float theta, TRIANGLE *triangles, int max_triangles, VECTOR3F *vectors, int max_vectors)
{
int minx = 0, maxx = 0, miny = 0, maxy = 0;
int i = 0, j = 0, vector = 0, triangle = 0;
VECTOR3F V1, V2, V3, *Output;

if (( Output = (VECTOR3F *) malloc(max_vectors * sizeof(VECTOR3F) ) ) == NULL)
	{
	printf("ERROR ALLOCATING (%u) Rotation_Arbitrary_Axis\n", max_vectors);
	exit(0);
	}

for (triangle = 0; triangle < max_triangles; triangle++)
	{
	V1 = vectors[triangles[triangle].v1];
	V2 = vectors[triangles[triangle].v2];
	V3 = vectors[triangles[triangle].v3];

	Rotation_Arbitrary_Axis_3D_Point(ux, uy, uz, theta, &V1);
	Rotation_Arbitrary_Axis_3D_Point(ux, uy, uz, theta, &V2);
	Rotation_Arbitrary_Axis_3D_Point(ux, uy, uz, theta, &V3);

	Output[triangles[triangle].v1] = V1;
	Output[triangles[triangle].v2] = V2;
	Output[triangles[triangle].v3] = V3;
	}

return Output;
}


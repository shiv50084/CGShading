/* ############################################################################
Name           : projections.c
University     : University of Edinburgh
Project        : Practical 1, Computer Graphics
Student        : Stavros Vagionitis(s0954319)
Description    : Implements 3D projections

Procedure                     	  		Description
=============================================   =================================================
Parallel_Projection_3D_Point			Parallel projection of 3D point with frustum.
Parallel_Projection_3D_Vertices			Parallel projection of 3D vertices with frustum.
Parallel_Projection_3D_Point_Simple		Parallel projection of 3D point without frustum.
Parallel_Projection_3D_Vertices_Simple		Parallel projection of 3D vertices with frustum.
Perspective_Projection_3D_Point			Perspective projection of 3D point with frustum.
Perspective_Projection_3D_Vertices		Perspective projection of 3D vertices with frustum.
Perspective_Projection_3D_Point_Simple		Perspective projection of 3D point without frustum.
Perspective_Projection_3D_Vertices_Simple	Perspective projection of 3D vertices without frustum.

Globals        Type           Description
============== ============== =====================================================

Student        Date           Action
============== ============== =====================================================
S. Vagionitis  17/10/2009     Creation
############################################################################ */

#define _PROJECTIONS_C
#include "projections.h"
#include "vectors.h"
/*
Matrix

|2/(right - left)	0			0		-(right + left)/(right - left)	|
|0			2/(top - bottom)	0		-(top + bottom)/(top - bottom)	|
|0			0			2/(far - near)	-(far + near)/(far - near)	|
|0			0			0		1				|

*/
void Parallel_Projection_3D_Point(VECTOR3F LeftBottomNear, VECTOR3F RightTopFar, VECTOR3F *point_3d)
{
    VECTOR3F temp_point;

    temp_point.x = point_3d->x;
    temp_point.y = point_3d->y;
    temp_point.z = point_3d->z;

    point_3d->x = ((2*temp_point.x) - (RightTopFar.x + LeftBottomNear.x))/(RightTopFar.x - LeftBottomNear.x);
    point_3d->y = ((2*temp_point.y) - (RightTopFar.y + LeftBottomNear.y))/(RightTopFar.y - LeftBottomNear.y);
    point_3d->z = (temp_point.z - LeftBottomNear.z)/(RightTopFar.z - LeftBottomNear.z);
}

VECTOR3F *Parallel_Projection_3D_Vertices(VECTOR3F LeftBottomNear, VECTOR3F RightTopFar, TRIANGLE *triangles, int max_triangles, VECTOR3F *vectors, int max_vectors)
{
    VECTOR3F V1, V2, V3, *Output;

    if (( Output = (VECTOR3F *) malloc(max_vectors * sizeof(VECTOR3F) ) ) == NULL)
    {
        printf("ERROR ALLOCATING (%u) Parallel_Projection\n", max_vectors);
        exit(0);
    }


    for (int triangle = 0; triangle < max_triangles; triangle++)
    {
        V1 = vectors[triangles[triangle].v1];
        V2 = vectors[triangles[triangle].v2];
        V3 = vectors[triangles[triangle].v3];

        Parallel_Projection_3D_Point(LeftBottomNear, RightTopFar, &V1);
        Parallel_Projection_3D_Point(LeftBottomNear, RightTopFar, &V2);
        Parallel_Projection_3D_Point(LeftBottomNear, RightTopFar, &V3);

        Output[triangles[triangle].v1] = V1;
        Output[triangles[triangle].v2] = V2;
        Output[triangles[triangle].v3] = V3;
    }

    return Output;
}



void Parallel_Projection_3D_Point_Simple(VECTOR3F *point_3d)
{
    VECTOR3F temp_point;

    temp_point.x = point_3d->x;
    temp_point.y = point_3d->y;
    temp_point.z = point_3d->z;

    point_3d->x = temp_point.x;
    point_3d->y = temp_point.y;
    point_3d->z = 0;
}


VECTOR3F *Parallel_Projection_3D_Vertices_Simple(TRIANGLE *triangles, int max_triangles, VECTOR3F *vectors, int max_vectors)
{
    VECTOR3F V1, V2, V3, *Output;

    if (( Output = (VECTOR3F *) malloc(max_vectors * sizeof(VECTOR3F) ) ) == NULL)
    {
        printf("ERROR ALLOCATING (%u) Parallel_Projection\n", max_vectors);
        exit(0);
    }


    for (int triangle = 0; triangle < max_triangles; triangle++)
    {
        V1 = vectors[triangles[triangle].v1];
        V2 = vectors[triangles[triangle].v2];
        V3 = vectors[triangles[triangle].v3];

        Parallel_Projection_3D_Point_Simple(&V1);
        Parallel_Projection_3D_Point_Simple(&V2);
        Parallel_Projection_3D_Point_Simple(&V3);

        Output[triangles[triangle].v1] = V1;
        Output[triangles[triangle].v2] = V2;
        Output[triangles[triangle].v3] = V3;
    }

    return Output;
}

/*
Matrix

|(2*near)/(right - left)		0				-(right + left)/(right - left)		0			|
|0					(2*near)/(top - bottom)		-(top + bottom)/(top - bottom)		0			|
|0					0				(far + near)/(far - near)		-2*far*near/(far - near)|
|0					0				1					0			|

*/

void Perspective_Projection_3D_Point(VECTOR3F LeftBottomNear, VECTOR3F RightTopFar, VECTOR3F *point_3d)
{
    VECTOR3F temp_point;

    temp_point.x = point_3d->x;
    temp_point.y = point_3d->y;
    temp_point.z = point_3d->z;


    point_3d->x = ((2*LeftBottomNear.z*temp_point.x)-((RightTopFar.x+LeftBottomNear.x)*temp_point.z))/(RightTopFar.x-LeftBottomNear.x);
    point_3d->y = ((2*LeftBottomNear.z*temp_point.y)-((RightTopFar.y+LeftBottomNear.y)*temp_point.z))/(RightTopFar.y-LeftBottomNear.y);
    point_3d->z = ((RightTopFar.z*temp_point.z)-(RightTopFar.z*LeftBottomNear.z))/(RightTopFar.z-LeftBottomNear.z);
}

VECTOR3F *Perspective_Projection_3D_Vertices(VECTOR3F LeftBottomNear, VECTOR3F RightTopFar, TRIANGLE *triangles, int max_triangles, VECTOR3F *vectors, int max_vectors)
{
    VECTOR3F V1, V2, V3, *Output;

    if (( Output = (VECTOR3F *) malloc(max_vectors * sizeof(VECTOR3F) ) ) == NULL)
    {
        printf("ERROR ALLOCATING (%u) Perspective_Projection\n", max_vectors);
        exit(0);
    }


    for (int triangle = 0; triangle < max_triangles; triangle++)
    {
        V1 = vectors[triangles[triangle].v1];
        V2 = vectors[triangles[triangle].v2];
        V3 = vectors[triangles[triangle].v3];

        Perspective_Projection_3D_Point(LeftBottomNear, RightTopFar, &V1);
        Perspective_Projection_3D_Point(LeftBottomNear, RightTopFar, &V2);
        Perspective_Projection_3D_Point(LeftBottomNear, RightTopFar, &V3);

        Output[triangles[triangle].v1] = V1;
        Output[triangles[triangle].v2] = V2;
        Output[triangles[triangle].v3] = V3;
    }

    return Output;
}

void Perspective_Projection_3D_Point_Simple(float d, VECTOR3F *point_3d)
{
    VECTOR3F temp_point;
    float w = 0.0;

    temp_point.x = point_3d->x;
    temp_point.y = point_3d->y;
    temp_point.z = point_3d->z;

    if (d <= 0.0)
        d = 1.0;

    w = 1.0 / d;

    point_3d->x = (temp_point.x) * w;
    point_3d->y = (temp_point.y) * w;

}

VECTOR3F *Perspective_Projection_3D_Vertices_Simple(float d, TRIANGLE *triangles, int max_triangles, VECTOR3F *vectors, int max_vectors)
{
    VECTOR3F V1, V2, V3, *Output;

    if (( Output = (VECTOR3F *) malloc(max_vectors * sizeof(VECTOR3F) ) ) == NULL)
    {
        printf("ERROR ALLOCATING (%u) Perspective_Projection\n", max_vectors);
        exit(0);
    }


    for (int triangle = 0; triangle < max_triangles; triangle++)
    {
        V1 = vectors[triangles[triangle].v1];
        V2 = vectors[triangles[triangle].v2];
        V3 = vectors[triangles[triangle].v3];

        Perspective_Projection_3D_Point_Simple(d, &V1);
        Perspective_Projection_3D_Point_Simple(d, &V2);
        Perspective_Projection_3D_Point_Simple(d, &V3);

        Output[triangles[triangle].v1] = V1;
        Output[triangles[triangle].v2] = V2;
        Output[triangles[triangle].v3] = V3;
    }

    return Output;
}


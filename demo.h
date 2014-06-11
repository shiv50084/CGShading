#ifndef _DEMO_H
#define _DEMO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#ifndef	FALSE
#define	FALSE	(0)
#endif

#ifndef	TRUE
#define	TRUE	(!FALSE)
#endif

#define PI 3.14159265

#define MAX(x,y) (x) > (y) ? (x) : (y)
#define MIN(x,y) (x) < (y) ? (x) : (y)

#define	LARGE_VALUE 1000000.0

/* Pragmas */
#pragma option align=packed
#pragma pack(1)

#define FLAT	"flat"
#define GOURAUD	"gouraud"
#define PHONG	"phong"

/*Typedef structures declaration*/
typedef struct vector3f
{
    float x, y, z;/*3D coordinates*/
}VECTOR3F;

typedef struct triangle
{
    int32_t v1, v2, v3;
}TRIANGLE;

typedef struct color
{
    float r, g, b;
}COLOR;

typedef struct trianglemesh
{
    int32_t triangle;	/*Triangle number*/
    TRIANGLE vertices;	/*Triangle vertices*/
    VECTOR3F vert_3d;	/*Triangle Vertices in 3D coordinates*/
}TRIANGLEMESH;

void Normal_Vector_Calc(VECTOR3F, VECTOR3F, VECTOR3F, VECTOR3F *);
void TriangleMesh_LoadFile(char *);
void Choose_Display(char *);
void Flat_Display();
void Gouraud_Display();
void Phong_Display();

#endif //_DEMO_H

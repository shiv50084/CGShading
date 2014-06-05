/* ############################################################################
Name           : utils.c
University     : University of Edinburgh
Project        : Practical 1, Computer Graphics
Student        : Stavros Vagionitis(s0954319)
Description    : Several utilities that we are going
		 to use.

Procedure                     	  	Description
=================================	=================================================
Check_Point_In_Triangle			Check if a point belongs to the triangle.
Color_Point				Put color to a specified point.
Color_Triangle				Color the triangle with a single color(Flat Shading)
Barycentric_Coordinates			Calculate barycentric coordinates.
Calculate_Normalize_Vertex_Normals	Calculate the normal of vertices and normalize them.(Gouraud & Phong)

Globals        Type           Description
============== ============== =====================================================

Student        Date           Action
============== ============== =====================================================
S. Vagionitis  19/10/2009     Creation
############################################################################ */

#define _UTILS_C
#include "utils.h"
#include "vectors.h"

/*RGB colors from 0..1*/
void Color_Point(VECTOR3F p, COLOR rgb)
{
glColor3f(rgb.r, rgb.g, rgb.b);
glRecti((int)p.x, (int)p.y, (int)p.x+1, (int)p.y+1);
}

/*Calculate barycentric coordinates for point p*/
void Barycentric_Coordinates(VECTOR3F p, VECTOR3F V1, VECTOR3F V2, VECTOR3F V3, VECTOR3F *BC)
{
float alpha = 0.0, beta = 0.0, gamma = 0.0;
float diffy23 = 0.0, diffx32 = 0.0, 
      diffy31 = 0.0, diffx13 = 0.0;
float diffxy23 = 0.0, diffxy31 = 0.0;
float f23p = 0.0, f231 = 0.0, f31p = 0.0, f312 = 0.0;

diffy23 = V2.y - V3.y;
diffx32 = V3.x - V2.x;

diffy31 = V3.y - V1.y;
diffx13 = V1.x - V3.x;

diffxy23 = V2.x*V3.y - V3.x*V2.y; 
diffxy31 = V3.x*V1.y - V1.x*V3.y;

f23p = diffy23*p.x + diffx32*p.y + diffxy23;
f231 = diffy23*V1.x + diffx32*V1.y + diffxy23;

f31p = diffy31*p.x + diffx13*p.y + diffxy31;
f312 = diffy31*V2.x + diffx13*V2.y + diffxy31;

BC->x = alpha = f23p / f231;
BC->y = beta = f31p / f312;
BC->z = gamma = 1 - alpha - beta;
}

/*Check point p if it's in the triangle (V1, V2, V3).*/
unsigned char Check_Point_In_Triangle(VECTOR3F p, VECTOR3F V1, VECTOR3F V2, VECTOR3F V3, VECTOR3F *BC)
{

Barycentric_Coordinates(p, V1, V2, V3, BC);

if ((BC->x > 0 && BC->y > 0 && BC->z > 0 &&
     BC->x < 1 && BC->y < 1 && BC->z < 1))
	return TRUE;
else
	return FALSE;
}


/*Color triangle(V1, V2, V3) with color rgb.*/
void Color_Triangle(VECTOR3F V1, VECTOR3F V2, VECTOR3F V3, COLOR rgb)
{
int minx = 0, maxx = 0, miny = 0, maxy = 0;
int i = 0, j = 0;
VECTOR3F VP, BC;

minx = MIN(MIN((int)V1.x, (int)V2.x), (int)V3.x);
maxx = MAX(MAX((int)V1.x, (int)V2.x), (int)V3.x);
miny = MIN(MIN((int)V1.y, (int)V2.y), (int)V3.y);
maxy = MAX(MAX((int)V1.y, (int)V2.y), (int)V3.y);

for (VP.x = minx;VP.x <= maxx;VP.x++)
	for(VP.y = miny;VP.y <= maxy;VP.y++)
		if (Check_Point_In_Triangle(VP, V1, V2, V3, &BC))
			Color_Point(VP, rgb);

}


void Calculate_Normalize_Vertex_Normals(TRIANGLE *triangles, int max_triangles, VECTOR3F *vectors, int max_vectors, VECTOR3F *NV_Vertex)
{
int i = 0, j = 0, vector = 0, triangle = 0;
VECTOR3F NV_Triangle;

/*Calculate vertex normals*/
for(vector = 0; vector < max_vectors; vector++)
	{
	memset(&NV_Triangle, 0, sizeof(NV_Triangle));
	for (triangle = 0; triangle < max_triangles; triangle++)
		{
		/*if vertex is in the triangles*/
		if ((triangles[triangle].v1 == vector) ||
		    (triangles[triangle].v2 == vector) ||
		    (triangles[triangle].v3 == vector) )
			{
			/*Find Normal Vector of Triangle*/

			Normal_Vector_Triangle(vectors[triangles[triangle].v1], 
					       vectors[triangles[triangle].v2], 
					       vectors[triangles[triangle].v3], &NV_Triangle);

			NV_Vertex[vector].x += NV_Triangle.x;
			NV_Vertex[vector].y += NV_Triangle.y;
			NV_Vertex[vector].z += NV_Triangle.z;
			}
		}
	/*Normalize Vertex Normal*/
	V3Normalize(&NV_Vertex[vector]);
	}
}

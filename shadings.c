/* ############################################################################
Name           : shadings.c
University     : University of Edinburgh
Project        : Practical 1, Computer Graphics
Student        : Stavros Vagionitis(s0954319)
Description    : Implements 3D shadings

Procedure                     	  	Description
================================= 	=================================================
Ambient_Lighting			Calculte ambient lighting.
Diffuse_Lighting			Calculte diffuse lighting using degrees.
Diffuse_Lighting_Vectors		Calculte diffuse lighting using vectors.
Specular_Lighting			Calculte specular lighting using degrees.
Specular_Lighting_Vectors		Calculte diffuse lighting using vectors.
Lighting				Calculate overall lighting using vectors.
Flat_Shading				Calculate Flat Shading.
Gouraud_Shading				Calculate Gouraud Shading.
Phong_Shading				Calculate Phong Shading.

Globals        Type           Description
============== ============== =====================================================

Student        Date           Action
============== ============== =====================================================
S. Vagionitis  18/10/2009     Creation
############################################################################ */

#define _SHADINGS_C
#include "shadings.h"
#include "vectors.h"
#include "utils.h"

/*
ka:	reflectance
ia:	light intensity
i:	resulting intensity
*/
void Ambient_Lighting(float ka, COLOR ia, COLOR *i)
{
    i->r = (ka * ia.r);
    i->g = (ka * ia.g);
    i->b = (ka * ia.b);
}

/*
kd:	diffuse reflectivity
id:	light intensity
theta:	the angle between the normal vector
	direction towards the light
i:	resulting intensity
*/
void Diffuse_Lighting(float kd, float theta, COLOR id, COLOR *i)
{
    i->r = (kd * id.r * cos(theta*PI/180));
    i->g = (kd * id.g * cos(theta*PI/180));
    i->b = (kd * id.b * cos(theta*PI/180));
}

/*
kd:	diffuse reflectivity
ip:	light intensity
N:	Normal vector of the colored point
L:	Normalized vector from the colored poit
	towards the light source
i:	resulting intensity
*/
void Diffuse_Lighting_Vectors(float kd, VECTOR3F N, VECTOR3F L, COLOR id, COLOR *i)
{
    float dotNL = 0.0;

    V3Dot(N, L, &dotNL);

    i->r = (kd * id.r * dotNL);
    i->g = (kd * id.g * dotNL);
    i->b = (kd * id.b * dotNL);
}


/*
ks:	material specular reflectivity coefficient
is:	light intensity
alpha:	angle between reflection vector and direction towards camera
n:	shininess factor(rate of decay)
i:	resulting intensity
*/
void Specular_Lighting(float ks, float n, float alpha, COLOR is, COLOR *i)
{
    i->r = (ks * is.r * pow(cos(alpha*PI/180), n));
    i->g = (ks * is.g * pow(cos(alpha*PI/180), n));
    i->b = (ks * is.b * pow(cos(alpha*PI/180), n));
}

/*
ks:	material specular reflectivity coefficient
is:	light intensity
V:	Vector from the surface to the viewer
R:	Normalized reflection vector
n:	shininess factor(rate of decay)
i:	resulting intensity
*/
void Specular_Lighting_Vectors(float ks, float n, VECTOR3F N, VECTOR3F V, COLOR is, COLOR *i)
{
    float dotVR = 0.0, dotNV = 0.0;
    VECTOR3F R;

    V3Dot(N, V, &dotNV);
    R.x = 2*dotNV*N.x - V.x;
    R.y = 2*dotNV*N.y - V.y;
    R.z = 2*dotNV*N.z - V.z;

    V3Dot(V, R, &dotVR);


    i->r = (ks * is.r * pow(dotVR, n));
    i->g = (ks * is.g * pow(dotVR, n));
    i->b = (ks * is.b * pow(dotVR, n));
}

/*
ka:	reflectance
ia:	Ambient light intensity

kd:	diffuse reflectivity
ip:	Diffuse light intensity
N:	Normal vector of the colored point
L:	Normalized vector from the colored poit
	towards the light source

ks:	material specular reflectivity coefficient
is:	Specular light intensity
V:	Vector from the surface to the viewer
R:	Normalized reflection vector
n:	shininess factor(rate of decay)

i:	resulting intensity
*/
void Lighting(float ka, float kd, float ks, float n, VECTOR3F N, VECTOR3F L, VECTOR3F V, COLOR ia, COLOR id, COLOR is, COLOR *I)
{
    COLOR Ia, Id, Is;

    Ambient_Lighting(ka, ia, &Ia);
    Diffuse_Lighting_Vectors(kd, N, L, id, &Id);
    Specular_Lighting_Vectors(ks, n, N, V, is, &Is);

    I->r = Ia.r + Id.r + Is.r;
    I->g = Ia.g + Id.g + Is.g;
    I->b = Ia.b + Id.b + Is.b;
}


void Flat_Shading(VECTOR3F L, TRIANGLE *triangles, int max_triangles, VECTOR3F *vectors, int max_vectors, int nCols, int nRows, COLOR rgb)
{
    int minx = 0, maxx = 0, miny = 0, maxy = 0;
    VECTOR3F VP, NV, BC, V1, V2, V3;
    COLOR CP, **Flat_Color_Buffer;
    float dotNVL = 0.0;
    float **z_buffer;

    memset(&VP, 0, sizeof(VP));
    memset(&NV, 0, sizeof(NV));
    memset(&BC, 0, sizeof(BC));
    memset(&V1, 0, sizeof(V1));memset(&V2, 0, sizeof(V2));memset(&V3, 0, sizeof(V3));
    memset(&CP, 0, sizeof(CP));

    /*Allocate memory and initializing for z buffer*/
    if( ( z_buffer = (float **)malloc( nCols * sizeof( float * ) ) ) != NULL )
        for(int i = 0; i < nCols; i++)
            if( ( z_buffer[i] = (float *)malloc( nRows * sizeof( float ) ) ) != NULL )
            {
                for(int j=0;j<nRows;j++)
                    z_buffer[i][j] = LARGE_VALUE;
            }

    /*Allocate memory and initializing for color buffer*/
    if( ( Flat_Color_Buffer = (COLOR **)malloc( nCols * sizeof( COLOR * ) ) ) != NULL )
        for(int i = 0; i < nCols; i++)
            if( ( Flat_Color_Buffer[i] = (COLOR *)malloc( nRows * sizeof( COLOR ) ) ) != NULL )
            {
                for(int j=0;j<nRows;j++)
                {
                    Flat_Color_Buffer[i][j].r = 0.0;
                    Flat_Color_Buffer[i][j].g = 0.0;
                    Flat_Color_Buffer[i][j].b = 0.0;
                }
            }


    /*Normalize Light Vector*/
    V3Normalize(&L);

    for (int triangle = 0; triangle < max_triangles; triangle++)
    {

        dotNVL = 0.0;

        /*Edge coordinates of triangle*/
        V1 = vectors[triangles[triangle].v1];
        V2 = vectors[triangles[triangle].v2];
        V3 = vectors[triangles[triangle].v3];

        minx = MIN(MIN((int)V1.x, (int)V2.x), (int)V3.x);
        maxx = MAX(MAX((int)V1.x, (int)V2.x), (int)V3.x);
        miny = MIN(MIN((int)V1.y, (int)V2.y), (int)V3.y);
        maxy = MAX(MAX((int)V1.y, (int)V2.y), (int)V3.y);


        /*Find Normal Vector of Triangle*/
        Normal_Vector_Triangle(V1, V2, V3, &NV);

        /*
         * Check Light(view point) with normal vector
         * of triangle(Back face culling)
         */
        V3Dot(NV, L, &dotNVL);
        if (dotNVL < 0.0)
            dotNVL = 0.0;

        CP.r = rgb.r * dotNVL;
        CP.g = rgb.g * dotNVL;
        CP.b = rgb.b * dotNVL;

        for (VP.y = miny;VP.y <= maxy;VP.y++)
            for(VP.x = minx;VP.x <= maxx;VP.x++)
                if (Check_Point_In_Triangle(VP, V1, V2, V3, &BC))
                {
                    VP.z = BC.x*V1.z + BC.y*V2.z + BC.z*V3.z;

                    if (VP.z < z_buffer[(int)VP.y + nCols/2][(int)VP.x + nRows/2])
                    {
                        z_buffer[(int)VP.y + nCols/2][(int)VP.x + nRows/2] = VP.z;

                        Flat_Color_Buffer[(int)VP.y + nCols/2][(int)VP.x + nRows/2].r = CP.r;
                        Flat_Color_Buffer[(int)VP.y + nCols/2][(int)VP.x + nRows/2].g = CP.g;
                        Flat_Color_Buffer[(int)VP.y + nCols/2][(int)VP.x + nRows/2].b = CP.b;

                        Color_Point(VP, CP);
                    }
                    else
                    {
                        Color_Point(VP, Flat_Color_Buffer[(int)VP.y + nCols/2][(int)VP.x + nRows/2]);
                    }

                }
    }

    /*Free memory for color buffer*/
    for(int i = 0; i < nCols; i++)
        free(Flat_Color_Buffer[i]);
    free(Flat_Color_Buffer);

    /*Free memory for z buffer*/
    for(int i = 0; i < nCols; i++)
        free(z_buffer[i]);
    free(z_buffer);
}

void Gouraud_Shading(VECTOR3F L, TRIANGLE *triangles, int max_triangles, VECTOR3F *vectors, int max_vectors, int nCols, int nRows, COLOR rgb)
{
    int minx = 0, maxx = 0, miny = 0, maxy = 0;
    VECTOR3F VP, *NV_Vertex, NV_Triangle, V1, V2, V3, NV1, NV2, NV3, BC;
    float dotNV1 = 0.0, dotNV2 = 0.0, dotNV3 = 0.0;
    COLOR C1, C2, C3, CP, **Gouraud_Color_Buffer;
    float **z_buffer;

    /*Initialize local variables*/
    memset(&VP, 0, sizeof(VP));
    memset(&V1, 0, sizeof(V1));memset(&V2, 0, sizeof(V2));memset(&V3, 0, sizeof(V3));
    memset(&NV1, 0, sizeof(NV1));memset(&NV2, 0, sizeof(NV2));memset(&NV3, 0, sizeof(NV3));
    memset(&NV_Triangle, 0, sizeof(NV_Triangle));
    memset(&BC, 0, sizeof(BC));

    /*Allocate memory and initializing for z buffer*/
    if( ( z_buffer = (float **)malloc( nCols * sizeof( float * ) ) ) != NULL )
        for(int i = 0; i < nCols; i++)
            if( ( z_buffer[i] = (float *)malloc( nRows * sizeof( float ) ) ) != NULL )
            {
                for(int j=0;j<nRows;j++)
                    z_buffer[i][j] = LARGE_VALUE;
            }

    /*Allocate memory and initializing for color buffer*/
    if( ( Gouraud_Color_Buffer = (COLOR **)malloc( nCols * sizeof( COLOR * ) ) ) != NULL )
        for(int i = 0; i < nCols; i++)
            if( ( Gouraud_Color_Buffer[i] = (COLOR *)malloc( nRows * sizeof( COLOR ) ) ) != NULL )
            {
                for(int j=0;j<nRows;j++)
                {
                    Gouraud_Color_Buffer[i][j].r = 0.0;
                    Gouraud_Color_Buffer[i][j].g = 0.0;
                    Gouraud_Color_Buffer[i][j].b = 0.0;
                }
            }


    /*Allocating bytes for normal vertices*/
    if (( NV_Vertex = (VECTOR3F *) malloc(max_vectors * sizeof(VECTOR3F) ) ) == NULL)
    {
        printf("ERROR ALLOCATING (%u) NV_Vertex\n", max_vectors);
        exit(0);
    }


    Calculate_Normalize_Vertex_Normals(triangles, max_triangles, vectors, max_vectors, NV_Vertex);

    /*Normalize Light Vector*/
    V3Normalize(&L);

    for (int triangle = 0; triangle < max_triangles; triangle++)
    {

        /*Edge coordinates of triangle*/
        V1 = vectors[triangles[triangle].v1];
        V2 = vectors[triangles[triangle].v2];
        V3 = vectors[triangles[triangle].v3];

        /*Vertex Normals for each Edge of Triangle*/
        NV1 = NV_Vertex[triangles[triangle].v1];
        NV2 = NV_Vertex[triangles[triangle].v2];
        NV3 = NV_Vertex[triangles[triangle].v3];

        /*(Back face culling)*/
        V3Dot(NV1, L, &dotNV1);
        if (dotNV1 < 0.0)
            dotNV1 = 0.0;
        C1.r = (rgb.r * dotNV1);
        C1.g = (rgb.g * dotNV1);
        C1.b = (rgb.b * dotNV1);

        /*(Back face culling)*/
        V3Dot(NV2, L, &dotNV2);
        if (dotNV2 < 0.0)
            dotNV2 = 0.0;
        C2.r = (rgb.r * dotNV2);
        C2.g = (rgb.g * dotNV2);
        C2.b = (rgb.b * dotNV2);

        /*(Back face culling)*/
        V3Dot(NV3, L, &dotNV3);
        if (dotNV3 < 0.0)
            dotNV3 = 0.0;
        C3.r = (rgb.r * dotNV3);
        C3.g = (rgb.g * dotNV3);
        C3.b = (rgb.b * dotNV3);

        minx = MIN(MIN((int)V1.x, (int)V2.x), (int)V3.x);
        maxx = MAX(MAX((int)V1.x, (int)V2.x), (int)V3.x);
        miny = MIN(MIN((int)V1.y, (int)V2.y), (int)V3.y);
        maxy = MAX(MAX((int)V1.y, (int)V2.y), (int)V3.y);

        for (VP.y = miny;VP.y <= maxy;VP.y++)
            for(VP.x = minx;VP.x <= maxx;VP.x++)
                if (Check_Point_In_Triangle(VP, V1, V2, V3, &BC))
                {

                    VP.z = BC.x*V1.z + BC.y*V2.z + BC.z*V3.z;

                    if (VP.z < z_buffer[(int)VP.y + nCols/2][(int)VP.x + nRows/2])
                    {
                        z_buffer[(int)VP.y + nCols/2][(int)VP.x + nRows/2] = VP.z;

                        CP.r = ((BC.x * C1.r) + (BC.y * C2.r) + (BC.z * C3.r));
                        CP.g = ((BC.x * C1.g) + (BC.y * C2.g) + (BC.z * C3.g));
                        CP.b = ((BC.x * C1.b) + (BC.y * C2.b) + (BC.z * C3.b));

                        Gouraud_Color_Buffer[(int)VP.y + nCols/2][(int)VP.x + nRows/2].r = CP.r;
                        Gouraud_Color_Buffer[(int)VP.y + nCols/2][(int)VP.x + nRows/2].g = CP.g;
                        Gouraud_Color_Buffer[(int)VP.y + nCols/2][(int)VP.x + nRows/2].b = CP.b;

                        Color_Point(VP, CP);
                    }
                    else
                    {
                        Color_Point(VP, Gouraud_Color_Buffer[(int)VP.y + nCols/2][(int)VP.x + nRows/2]);
                    }

                }
    }

    /*Free memory for color buffer*/
    for(int i = 0; i < nCols; i++)
        free(Gouraud_Color_Buffer[i]);
    free(Gouraud_Color_Buffer);

    /*Free memory for z buffer*/
    for(int i = 0; i < nCols; i++)
        free(z_buffer[i]);
    free(z_buffer);

    free(NV_Vertex);
}

void Phong_Shading(VECTOR3F C, VECTOR3F L, TRIANGLE *triangles, int max_triangles, VECTOR3F *vectors, int max_vectors, int nCols, int nRows, COLOR rgb)
{
    int minx = 0, maxx = 0, miny = 0, maxy = 0;
    VECTOR3F VP, *NV_Vertex, V1, V2, V3, NV1, NV2, NV3, NVP, BC;
    float dotNVP = 0.0;
    COLOR CP, **Phong_Color_Buffer;
    float **z_buffer;

    /*Initialize local variables*/
    memset(&VP, 0, sizeof(VP));
    memset(&V1, 0, sizeof(V1));memset(&V2, 0, sizeof(V2));memset(&V3, 0, sizeof(V3));
    memset(&NV1, 0, sizeof(NV1));memset(&NV2, 0, sizeof(NV2));memset(&NV3, 0, sizeof(NV3));
    memset(&NVP, 0, sizeof(NVP));
    memset(&BC, 0, sizeof(BC));


    /*Allocate memory and initializing for z buffer*/
    if( ( z_buffer = (float **)malloc( nCols * sizeof( float * ) ) ) != NULL )
        for(int i = 0; i < nCols; i++)
            if( ( z_buffer[i] = (float *)malloc( nRows * sizeof( float ) ) ) != NULL )
            {
                for(int j=0;j<nRows;j++)
                    z_buffer[i][j] = LARGE_VALUE;
            }

    /*Allocate memory and initializing for color buffer*/
    if( ( Phong_Color_Buffer = (COLOR **)malloc( nCols * sizeof( COLOR * ) ) ) != NULL )
        for(int i = 0; i < nCols; i++)
            if( ( Phong_Color_Buffer[i] = (COLOR *)malloc( nRows * sizeof( COLOR ) ) ) != NULL )
            {
                for(int j=0;j<nRows;j++)
                {
                    Phong_Color_Buffer[i][j].r = 0.0;
                    Phong_Color_Buffer[i][j].g = 0.0;
                    Phong_Color_Buffer[i][j].b = 0.0;
                }
            }

    /*Allocating bytes for normal vertices*/
    if (( NV_Vertex = (VECTOR3F *) malloc(max_vectors * sizeof(VECTOR3F) ) ) == NULL)
    {
        printf("ERROR ALLOCATING (%u) NV_Vertex\n", max_vectors);
        exit(0);
    }

    Calculate_Normalize_Vertex_Normals(triangles, max_triangles, vectors, max_vectors, NV_Vertex);

    /*Normalize Light Vector*/
    V3Normalize(&L);

    /*Normalize Camera Vector*/
    V3Normalize(&C);

    for (int triangle = 0; triangle < max_triangles; triangle++)
    {

        /*Edge coordinates of triangle*/
        V1 = vectors[triangles[triangle].v1];
        V2 = vectors[triangles[triangle].v2];
        V3 = vectors[triangles[triangle].v3];

        /*Vertex Normals for each Edge of Triangle*/
        NV1 = NV_Vertex[triangles[triangle].v1];
        NV2 = NV_Vertex[triangles[triangle].v2];
        NV3 = NV_Vertex[triangles[triangle].v3];

        minx = MIN(MIN((int)V1.x, (int)V2.x), (int)V3.x);
        maxx = MAX(MAX((int)V1.x, (int)V2.x), (int)V3.x);
        miny = MIN(MIN((int)V1.y, (int)V2.y), (int)V3.y);
        maxy = MAX(MAX((int)V1.y, (int)V2.y), (int)V3.y);

        for (VP.y = miny;VP.y <= maxy;VP.y++)
            for(VP.x = minx;VP.x <= maxx;VP.x++)
                if (Check_Point_In_Triangle(VP, V1, V2, V3, &BC))
                {
                    VP.z = BC.x*V1.z + BC.y*V2.z + BC.z*V3.z;

                    if (VP.z < z_buffer[(int)VP.y + nCols/2][(int)VP.x + nRows/2])
                    {
                        z_buffer[(int)VP.y + nCols/2][(int)VP.x + nRows/2] = VP.z;

                        NVP.x = ((BC.x * NV1.x) + (BC.y * NV2.x) + (BC.z * NV3.x));
                        NVP.y = ((BC.x * NV1.y) + (BC.y * NV2.y) + (BC.z * NV3.y));
                        NVP.z = ((BC.x * NV1.z) + (BC.y * NV2.z) + (BC.z * NV3.z));

                        /*(Back face culling)*/
                        V3Dot(NVP, L, &dotNVP);
                        if (dotNVP < 0.0)
                                dotNVP = 0.0;
                        CP.r = (rgb.r * dotNVP);
                        CP.g = (rgb.g * dotNVP);
                        CP.b = (rgb.b * dotNVP);

                        Lighting(0.4, 0.6, 0.8, 7.0, NVP, L, C, rgb, rgb, rgb, &CP);

                        Phong_Color_Buffer[(int)VP.y + nCols/2][(int)VP.x + nRows/2].r = CP.r;
                        Phong_Color_Buffer[(int)VP.y + nCols/2][(int)VP.x + nRows/2].g = CP.g;
                        Phong_Color_Buffer[(int)VP.y + nCols/2][(int)VP.x + nRows/2].b = CP.b;

                        Color_Point(VP, CP);
                    }
                    else
                    {
                        Color_Point(VP, Phong_Color_Buffer[(int)VP.y + nCols/2][(int)VP.x + nRows/2]);
                    }

                }
    }

    /*Free memory for color buffer*/
    for(int i = 0; i < nCols; i++)
        free(Phong_Color_Buffer[i]);
    free(Phong_Color_Buffer);

    /*Free memory for z buffer*/
    for(int i = 0; i < nCols; i++)
        free(z_buffer[i]);
    free(z_buffer);

    free(NV_Vertex);
}


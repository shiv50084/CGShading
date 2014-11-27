#include "demo.h"
#include "transformations.h"
#include "projections.h"
#include "vectors.h"
#include "shadings.h"
#include "utils.h"

/*Global variables*/
TRIANGLEMESH	trig_mesh;
TRIANGLE        *trig;
VECTOR3F        *vec;
COLOR           rgb;//color
VECTOR3F        l;//light
VECTOR3F        c;//camera
char            shading_name[20];

float	_xmax = 0.0, _xmin = 0.0,
		_ymax = 0.0, _ymin = 0.0,
		_zmin = 0.0, _zmax = 0.0;
int 	v_counter = 0, f_counter = 0,
		i_v = 0, i_f = 0;

int nRows = 640;
int nCols = 480;

void TriangleMesh_LoadFile(char *filename)
{
    FILE 	*fp;
    char 	buf[1024];
    char 	header[100];
    float 	x = 0.0, y = 0.0, z = 0.0;
    float 	xmax = 0.0, ymax = 0.0, zmax = 0.0,
            xmin = 0.0, ymin = 0.0, zmin = 0.0;
    int 	v1 = 0, v2 = 0, v3 = 0,
            n1 = 0, n2 = 0, n3 = 0;

    memset(buf, 0, sizeof(buf));
    memset(header, 0, sizeof(header));

    if((fp = fopen(filename, "r")) == NULL)
    {
        printf("Cannot open file %s for reading.\n", filename);
        exit(1);
    }

    /*Count lines with v and with f*/
    while (!feof(fp))
    {
        memset(buf, 0, sizeof(buf));

        while (fgets(buf, sizeof(buf), fp) != NULL) /* read a line */
        {
            memset(header, 0, sizeof(header));

            sscanf(buf, "%s", header);

            if (strcmp(header, "v") == 0)
                    v_counter++;
            else if (strcmp(header, "f") == 0)
                f_counter++;
            else
                continue;

        }
    }

    /*File pointer at the beginning*/
    rewind(fp);

    /*Allocating bytes for vertices and triangles*/
    if (( vec = (VECTOR3F *) malloc(v_counter * sizeof(VECTOR3F) ) ) == NULL)
    {
        printf("ERROR ALLOCATING (%u) vec\n", v_counter);
        exit(0);
    }

    if (( trig = (TRIANGLE *) malloc(f_counter * sizeof(TRIANGLE) ) ) == NULL)
    {
        printf("ERROR ALLOCATING (%u) trig\n", f_counter);
        exit(0);
    }


    memset(buf, 0, sizeof(buf));
    memset(header, 0, sizeof(header));

    xmax = -1000; ymax = -1000; zmax = -1000;
    xmin =  1000; ymin =  1000; zmin =  1000;

    VECTOR3F av;
    av.x = av.y = av.z = 0.0;

    i_v = 0, i_f = 0;

    while (!feof(fp))
    {
        memset(buf, 0, sizeof(buf));

        while (fgets(buf, sizeof(buf), fp) != NULL) /* read a line */
        {
            memset(header, 0, sizeof(header));

            sscanf(buf, "%s", header);

            if (strcmp(header, "v") == 0)
            {
                sscanf(buf, "%s %f %f %f", header, &x, &y, &z);

                vec[i_v].x = x;
                vec[i_v].y = y;
                vec[i_v].z = z;

                av.x += x; av.y += y; av.z += z;

                if (x > xmax)
                    xmax = x;
                if (y > ymax)
                    ymax = y;
                if (z > zmax)
                    zmax = z;

                if (x < xmin)
                    xmin = x;
                if (y < ymin)
                    ymin = y;
                if (z < zmin)
                    zmin = z;
                i_v++;
            }
            else if (strcmp(header, "f") == 0)
            {
                sscanf(buf, "%s %d %d %d", header, &v1, &v2, &v3);

                trig[i_f].v1 = v1 - 1;
                trig[i_f].v2 = v2 - 1;
                trig[i_f].v3 = v3 - 1;

                i_f++;
            }
            else
                continue;
        }
    }

    _xmin = xmin; _ymin = ymin; _zmin = zmin;
    _xmax = xmax; _ymax = ymax; _zmax = zmax;

    float range;
    if (xmax-xmin > ymax-ymin)
        range = xmax-xmin;
    else
        range = ymax-ymin;

    av.x /= i_v;
    av.y /= i_v;
    av.z /= i_v;

    for (int i = 0; i < i_v; i++)
    {
        vec[i].x = (vec[i].x - av.x)/range*400;
        vec[i].y = (vec[i].y - av.y)/range*400;
        vec[i].z = (vec[i].z - av.z)/range*400;
    }

    printf("trig: %u vertices: %u\n", i_f, i_v);

    fclose(fp);
}

void keyboardNormalKeys(unsigned char key, int x, int y)
{
    float theta = 0.0, scal = 1.0, presp_d = 1.0;

    switch(key)
    {
        case 27://esc
                free(trig);
                free(vec);
                exit(0);
                break;
        case 62://> Rotation Y
                theta -= 5;
                vec = Rotation_Y_Axis_3D_Vertices(theta, trig, f_counter, vec, v_counter);

                printf("Rotation Y Axis(theta)=(%.3f)\n", theta);

                Choose_Display(shading_name);

                break;
        case 60://< Rotation Y
                theta += 5;
                vec = Rotation_Y_Axis_3D_Vertices(theta, trig, f_counter, vec, v_counter);

                printf("Rotation Y Axis(theta)=(%.3f)\n", theta);

                Choose_Display(shading_name);

                break;
        case 41://) Rotation Z
                theta -= 5;
                vec = Rotation_Z_Axis_3D_Vertices(theta, trig, f_counter, vec, v_counter);

                printf("Rotation Z Axis(theta)=(%.3f)\n", theta);

                Choose_Display(shading_name);

                break;
        case 40://( Rotation Z
                theta += 5;
                vec = Rotation_Z_Axis_3D_Vertices(theta, trig, f_counter, vec, v_counter);

                printf("Rotation Z Axis(theta)=(%.3f)\n", theta);

                Choose_Display(shading_name);

                break;
        case 43://+ scale
                scal += 0.1;
                vec = Scale_3D_Vertices(scal, scal, scal, trig, f_counter, vec, v_counter);

                printf("Scale (factor)=(%.3f)\n", scal);

                Choose_Display(shading_name);

                break;
        case 45://- scale
                scal -= 0.1;
                vec = Scale_3D_Vertices(scal, scal, scal, trig, f_counter, vec, v_counter);

                printf("Scale (factor)=(%.3f)\n", scal);

                Choose_Display(shading_name);

                break;
        case 91://[ prespective
                presp_d -= 0.1;

                if (presp_d != 0.0)
                    vec = Perspective_Projection_3D_Vertices_Simple(presp_d, trig, f_counter, vec, v_counter);
                else
                    vec = Perspective_Projection_3D_Vertices_Simple(1.0, trig, f_counter, vec, v_counter);

                printf("Perspective (d)=(%.3f)\n", presp_d);

                Choose_Display(shading_name);

                break;
        case 93://] prespective
                presp_d += 0.1;

                if (presp_d != 0.0)
                    vec = Perspective_Projection_3D_Vertices_Simple(presp_d, trig, f_counter, vec, v_counter);
                else
                    vec = Perspective_Projection_3D_Vertices_Simple(1.0, trig, f_counter, vec, v_counter);

                printf("Perspective (d)=(%.3f)\n", presp_d);

                Choose_Display(shading_name);

                break;
    }

}

void keyboardSpecialKeys(int key, int x, int y)
{
    float theta = 0.0, transl = 0.0;

    switch(key)
    {
        case GLUT_KEY_F1://F1 red
                rgb.r = 1.0;rgb.g = 0.0;rgb.b = 0.0;

                printf("Color RED\n");
                Choose_Display(shading_name);

                break;
        case GLUT_KEY_F2://F2 green
                rgb.r = 0.0;rgb.g = 1.0;rgb.b = 0.0;

                printf("Color GREEN\n");
                Choose_Display(shading_name);

                break;
        case GLUT_KEY_F3://F3 blue
                rgb.r = 0.0;rgb.g = 0.0;rgb.b = 1.0;

                printf("Color BLUE\n");
                Choose_Display(shading_name);

                break;
        case GLUT_KEY_F4://F4 white grayscale
                rgb.r = 1.0;rgb.g = 1.0;rgb.b = 1.0;

                printf("Color WHITE\n");
                Choose_Display(shading_name);

                break;
        case GLUT_KEY_PAGE_UP://PG UP rotate x axis
                theta += 5;
                vec = Rotation_X_Axis_3D_Vertices(theta, trig, f_counter, vec, v_counter);

                printf("Rotation X Axis(theta)=(%.3f)\n", theta);

                Choose_Display(shading_name);

                break;
        case GLUT_KEY_PAGE_DOWN://PG DOWN rotate x axis
                theta -= 5;
                vec = Rotation_X_Axis_3D_Vertices(theta, trig, f_counter, vec, v_counter);

                printf("Rotation X Axis(theta)=(%.3f)\n", theta);

                Choose_Display(shading_name);

                break;
        case GLUT_KEY_RIGHT://Right translation
                transl += 10;
                vec = Translation_3D_Vertices(transl, 0.0, 0.0, trig, f_counter, vec, v_counter);

                printf("Translation X Axis(dx)=(%.3f)\n", transl);

                Choose_Display(shading_name);

                break;
        case GLUT_KEY_LEFT://Left translation
                transl -= 10;
                vec = Translation_3D_Vertices(transl, 0.0, 0.0, trig, f_counter, vec, v_counter);

                printf("Translation X Axis(dx)=(%.3f)\n", transl);

                Choose_Display(shading_name);

                break;
        case GLUT_KEY_UP://Up translation
                transl += 10;
                vec = Translation_3D_Vertices(0.0, transl, 0.0, trig, f_counter, vec, v_counter);

                printf("Translation Y Axis(dy)=(%.3f)\n", transl);

                Choose_Display(shading_name);

                break;
        case GLUT_KEY_DOWN://Down translation
                transl -= 10;
                vec = Translation_3D_Vertices(0.0, transl, 0.0, trig, f_counter, vec, v_counter);

                printf("Translation Y Axis(dy)=(%.3f)\n", transl);

                Choose_Display(shading_name);

                break;

    }
}

void mouseMov(int button, int state, int x, int y)
{

    switch(button)
    {
        case GLUT_LEFT_BUTTON:
                if (state == GLUT_DOWN)
                {
                    l.z += 50.0;
                    if (l.z > 500.0)
                        l.z = -500.0;
                }

                l.x = x;l.y = y;

                printf("Light(x, y, z)=(%.3f, %.3f, %.3f)\n", l.x, l.y, l.z);

                Choose_Display(shading_name);


                break;
        case GLUT_RIGHT_BUTTON:
                if (state == GLUT_DOWN)
                {
                    c.z += 50.0;
                    if (c.z > 500.0)
                        c.z = -500.0;
                }

                c.x = x;c.y = y;

                printf("Camera(x, y, z)=(%.3f, %.3f, %.3f)\n", c.x, c.y, c.z);

                Choose_Display(shading_name);

                break;
    }
}

void Flat_Display()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear OpenGL Window

    Flat_Shading(l, trig, f_counter, vec, v_counter, nCols, nRows, rgb);

    glFlush();// Output everything
}

void Gouraud_Display()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear OpenGL Window

    Gouraud_Shading(l, trig, f_counter, vec, v_counter, nCols, nRows, rgb);

    glFlush();// Output everything
}

void Phong_Display()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear OpenGL Window

    Phong_Shading(c, l, trig, f_counter, vec, v_counter, nCols, nRows, rgb);

    glFlush();// Output everything
}


void Choose_Display(char *shad_name)
{
    if (!strcmp(shad_name, FLAT))
        Flat_Display();
    else if (!strcmp(shad_name, GOURAUD))
        Gouraud_Display();
    else if (!strcmp(shad_name, PHONG))
        Phong_Display();
}

void usage(char *argv0)
{
    printf("Usage: %s <filename> <shading>\n", argv0);
    printf("filename: filename of the 3D computer model in .obj format.\n");
    printf("shading: flat, gouraud or phong.\n");
    exit(1);
}

int main(int argc, char **argv)
{
    int width, height;

    memset(&shading_name, '\0', sizeof(shading_name));

    if (argc ==  3)
    {
        TriangleMesh_LoadFile(argv[1]);

        strcpy (shading_name,argv[2]);

        if (!(strcmp(shading_name, FLAT) || 
              strcmp(shading_name, GOURAUD) || 
              strcmp(shading_name, PHONG)))
            usage(argv[0]);

    }
    else
        usage(argv[0]);

    glutInit(&argc, argv);
    glutInitWindowSize(nRows, nCols);

    glutCreateWindow(shading_name);
    gluOrtho2D(-(float)nRows/2, (float)nRows/2, -(float)nCols/2,  (float)nCols/2);

    if (!strcmp(shading_name, FLAT))
        glutDisplayFunc(Flat_Display);// Callback function for Flat
    else if (!strcmp(shading_name, GOURAUD))
        glutDisplayFunc(Gouraud_Display);// Callback function for Gouraud
    else if (!strcmp(shading_name, PHONG))
        glutDisplayFunc(Phong_Display);// Callback function for Phong

    glutKeyboardFunc(keyboardNormalKeys);
    glutSpecialFunc(keyboardSpecialKeys);
    glutMouseFunc(mouseMov);
    glutMainLoop();// Display everything and wait

}


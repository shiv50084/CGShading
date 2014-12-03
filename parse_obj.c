#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct vector3f
{
    float x, y, z;
}VECTOR3F;

typedef struct triangle
{
    int32_t v1, v2, v3;
}TRIANGLE;

typedef struct trianglemesh
{
    int32_t id;
    TRIANGLE t; // vertices number
    VECTOR3F v[3]; // vertices coordinates
}TRIANGLEMESH;


void usage(char *argv0)
{
    fprintf(stdout, "%s <obj filename>\n", argv0);
    exit(1);
}

int parse_file(const char *filename)
{
    FILE *fp = NULL;
    char buf[1024];
    int vertices_count = 0;
    int faces_count = 0;

    if ((fp = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "Cannot open file %s.\n", filename);
        return -1;
    }

    // Reading file until the end
    while (!feof(fp))
    {
        memset(buf, 0, sizeof(buf));
        char start_line = 0;

        // Read a line and save to a buffer.
        while (fgets(buf, sizeof(buf), fp) != NULL)
        {
            // Read the first character of the line
            sscanf(buf, "%c", &start_line);

            switch(start_line)
            {
                VECTOR3F v;
                TRIANGLE t;
                TRIANGLEMESH tm;

                case 'v':
                    sscanf(buf, "%c %f %f %f", &start_line, &v.x, &v.y, &v.z);
                    vertices_count += 1;

                    fprintf(stdout, "%c %f %f %f\n", start_line, v.x, v.y, v.z);
                    break;
                case 'f':
                    sscanf(buf, "%c %d %d %d", &start_line, &t.v1, &t.v2, &t.v3);
                    faces_count += 1;

                    fprintf(stdout, "%c %d %d %d\n", start_line, t.v1, t.v2, t.v3);
                    break;
                default:
                    fprintf(stdout, "Not known start line %c\n", start_line);
                    break;
            }

        }

    }

    return 0;
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        usage(argv[0]);
    }

    const char* filename = argv[1];

    parse_file(filename);

    return 0;
}


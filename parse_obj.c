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

int parse_file(const char *filename, uint32_t *vertices_count, uint32_t *faces_count, VECTOR3F **v, TRIANGLE **f, TRIANGLEMESH **tm)
{
    FILE *fp = NULL;
    char buf[1024];
    *vertices_count = 0;
    *faces_count = 0;

    VECTOR3F *_v = NULL;
    TRIANGLE *_f = NULL;
    TRIANGLEMESH *_tm = NULL;

    if ((fp = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "Cannot open file %s.\n", filename);
        return 0;
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
                VECTOR3F __v;
                TRIANGLE __f;
                TRIANGLEMESH __tm;

                case 'v':
                    sscanf(buf, "%c %f %f %f", &start_line, &__v.x, &__v.y, &__v.z);
                    *vertices_count += 1;

                    _v = realloc(*v, *vertices_count * sizeof(VECTOR3F));
                    if (_v != NULL)
                    {
                        *v = _v;
                    }
                    else
                    {
                        if (*v)
                            free(*v);

                        if (_v)
                            free(_v);

                        fprintf(stderr, "Realloc error in vertices -- count %u!!!\n", *vertices_count);
                        return 0;
                    }

                    (*v)[*vertices_count - 1].x = __v.x;
                    (*v)[*vertices_count - 1].y = __v.y;
                    (*v)[*vertices_count - 1].z = __v.z;

                    fprintf(stdout, "%u - %c %f %f %f\n", *vertices_count, start_line, (*v)[*vertices_count - 1].x, (*v)[*vertices_count - 1].y, (*v)[*vertices_count - 1].z);
                    break;
                case 'f':
                    sscanf(buf, "%c %d %d %d", &start_line, &__f.v1, &__f.v2, &__f.v3);
                    *faces_count += 1;

                    _f = realloc(*f, *faces_count * sizeof(VECTOR3F));
                    if (_f != NULL)
                    {
                        *f = _f;
                    }
                    else
                    {
                        if (*f)
                            free(*f);

                        if (_f)
                            free(_f);

                        fprintf(stderr, "Realloc error in faces -- count %u!!!\n", *faces_count);
                        return 0;
                    }

                    (*f)[*faces_count - 1].v1 = __f.v1 - 1;
                    (*f)[*faces_count - 1].v2 = __f.v2 - 1;
                    (*f)[*faces_count - 1].v3 = __f.v3 - 1;

                    fprintf(stdout, "%u - %c %d %d %d\n", *faces_count, start_line, (*f)[*faces_count - 1].v1, (*f)[*faces_count - 1].v2, (*f)[*faces_count - 1].v3);
                    break;
                default:
                    fprintf(stdout, "Not known start line %c\n", start_line);
                    break;
            }

        }

    }

    return 1;
}

int main(int argc, char *argv[])
{
    VECTOR3F *v = NULL;
    TRIANGLE *f = NULL;
    TRIANGLEMESH *tm = NULL;
    uint32_t v_c = 0;
    uint32_t f_c = 0;

    if (argc != 2)
    {
        usage(argv[0]);
    }

    const char* filename = argv[1];

    parse_file(filename, &v_c, &f_c, &v, &f, &tm);

    if (v)
        free(v);

    if (f)
        free(f);

    if (tm)
        free(tm);
    return 0;
}


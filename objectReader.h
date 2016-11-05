// Author: Nate Nichols, October 2016

#ifndef OBJECTREADER_H_INCLUDED
#define OBJECTREADER_H_INCLUDED

#define LINE_SIZE 100

typedef struct
{
    float x;
    float y;
    float z;
} vertex;

typedef struct
{
    int v1;
    int v2;
    int v3;
} triangle;

typedef struct
{
    float *vertices;
    int verticeCount;
    int *triangles;
    int triangleCount;
} obj;


vertex line2vertex(char line[LINE_SIZE]);

triangle line2triangle(char line[LINE_SIZE]);

obj readObjFile(const char *objFile);

#endif // OBJECTREADER_H_INCLUDED

// Author: Nate Nichols, October 2016

#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 100

typedef struct {
    float x;
    float y;
    float z;
} vertex;

typedef struct {
    int v1;
    int v2;
    int v3;
}triangle;

typedef struct {
    float *vertices;
    int verticeCount;
    int *triangles;
    int triangleCount;
} obj;


vertex line2vertex(char line[LINE_SIZE]){
    vertex vert;

    vert.x = atof(strtok (line," v"));
    vert.y = atof(strtok (NULL," v"));
    vert.z = atof(strtok (NULL," v"));
    //printf("%f, %f , %f\n",vert.x,vert.y,vert.z);

    return vert;
}


triangle line2triangle(char line[LINE_SIZE]){
    triangle tri;
    tri.v1 = atoi(strtok (line," f"));
    tri.v2 = atoi(strtok (NULL," f"));
    tri.v3 = atoi(strtok (NULL," f"));
    //printf("%i , %i , % i\n",tri.v1,tri.v2,tri.v3);
    return tri;
}

obj readObjFile(const char *objFile){

    FILE *fp;
    int vCount = 0;
    int tCount = 0;
    char line[LINE_SIZE];

    fp = fopen(objFile,"r");

    if(!fp){
        obj nullObj;
        nullObj.vertices = 0;
        nullObj.triangles = 0;
        return nullObj;
    }

    while(fgets(line, sizeof(line),fp)){
        if( (line[0] != '#') && (line[0] != '\n') ){
            if(line[0] == 'v'){
                vCount = vCount + 1;
            }

            if(line[0] == 'f'){
                tCount = tCount + 1;
            }
        }
    }

    float  *vertices = (float*)malloc(vCount*(6*sizeof(float)));
    //float  *vertices = (float*)malloc(vCount*(3*sizeof(float)));

    if(vertices == nullptr){
        printf("malloc call fucked up");
    }
    int *triangles = (int*)malloc(tCount*3*sizeof(int));
    if(triangles == nullptr){
        printf("malloc call fucked up");
    }
    vCount = 0;
    tCount = 0;

    rewind(fp);

    while(fgets(line, sizeof(line),fp)){
        if( (line[0] != '#') && (line[0] != '\n') ){
            if(line[0] == 'v'){
                vertices[vCount] = atof(strtok(line," v"));
                vertices[vCount+1] = atof(strtok(NULL," v"));
                vertices[vCount+2] = atof(strtok(NULL," v"));
                vertices[vCount+3] = atof(strtok(NULL," v"));
                vertices[vCount+4] = atof(strtok(NULL," v"));
                vertices[vCount+5] = atof(strtok(NULL," v"));
                vCount = vCount + 6;
            }

            if(line[0] == 'f'){
                triangles[tCount] = (atoi(strtok (line," f"))-1);
                triangles[tCount+1] = (atoi(strtok (NULL," f"))-1);
                triangles[tCount+2] = (atoi(strtok (NULL," f"))-1);
                tCount = tCount + 3;
            }
        }
    }

    fclose(fp);

    obj Object;

    Object.vertices = vertices;
    Object.triangles = triangles;
    Object.triangleCount = tCount;
    Object.verticeCount = vCount;

    return Object;
}

#endif

// OBJREADER_H_INCLUDED
/*
// Author: Nate Nichols, October 2016

#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 100

typedef struct {
    float x;
    float y;
    float z;
} vertex;

typedef struct {
    int v1;
    int v2;
    int v3;
}triangle;

typedef struct {
    vertex *vertices;
    int verticeCount;
    triangle *triangles;
    int triangleCount;
} obj;


vertex line2vertex(char line[LINE_SIZE]){
    vertex vert;

    vert.x = atof(strtok (line," v"));
    vert.y = atof(strtok (NULL," v"));
    vert.z = atof(strtok (NULL," v"));
    //printf("%f, %f , %f\n",vert.x,vert.y,vert.z);

    return vert;
}


triangle line2triangle(char line[LINE_SIZE]){
    triangle tri;
    tri.v1 = atoi(strtok (line," f"));
    tri.v2 = atoi(strtok (NULL," f"));
    tri.v3 = atoi(strtok (NULL," f"));
    //printf("%i , %i , % i\n",tri.v1,tri.v2,tri.v3);
    return tri;
}

obj readObjFile(const char *objFile){

    FILE *fp;
    int vCount = 0;
    int tCount = 0;
    char line[LINE_SIZE];

    fp = fopen(objFile,"r");

    if(!fp){
        obj nullObj;
        nullObj.vertices = 0;
        nullObj.triangles = 0;
        return nullObj;
    }

    while(fgets(line, sizeof(line),fp)){
        if( (line[0] != '#') && (line[0] != '\n') ){
            if(line[0] == 'v'){
                vCount = vCount + 1;
            }

            if(line[0] == 'f'){
                tCount = tCount + 1;
            }
        }
    }

    vertex vertices[vCount];
    triangle triangles[tCount];

    vCount = 0;
    tCount = 0;

    rewind(fp);

    while(fgets(line, sizeof(line),fp)){
        if( (line[0] != '#') && (line[0] != '\n') ){
            if(line[0] == 'v'){
                vertices[vCount] = line2vertex(line);
                vCount = vCount + 1;
            }

            if(line[0] == 'f'){
                triangles[tCount] = line2triangle(line);
                tCount = tCount + 1;
            }
        }
    }

    fclose(fp);

    obj Object;

    Object.vertices = vertices;
    Object.triangles = triangles;
    Object.triangleCount = tCount;
    Object.verticeCount = vCount;

    printf("%i\n",tCount);

    return Object;
}

#endif // OBJREADER_H_INCLUDED




    float vertices[36] = {0,  -0.525731,  0.850651,
                0.850651,  0,  0.525731,
                0.850651,  0,  -0.525731,
                -0.850651,  0,  -0.525731,
                -0.850651,  0,  0.525731,
                -0.525731,  0.850651,  0,
                0.525731,  0.850651,  0,
                0.525731,  -0.850651,  0,
                -0.525731,  -0.850651,  0,
                0,  -0.525731,  -0.850651,
                0,  0.525731,  -0.850651,
                0,  0.525731,  0.850651};

    int elements[60] = {2,  3,  7,
                2,  8,  3,
                4,  5,  6,
                5,  4,  9,
                7,  6,  12,
                6,  7,  11,
                10,  11,  3,
                11,  10,  4,
                8,  9,  10,
                9,  8,  1,
                12,  1,  2,
                1,  12,  5,
                7,  3,  11,
                2,  7,  12,
                4,  6,  11,
                6,  5,  12,
                3,  8,  10,
                8,  2,  1,
                4,  10,  9,
                5,  9,  1};


    int totalSize = 0;
    int totalTSize = 0;
    for (int i = 0; i < 36; i++){
        printf("%f:%f:%s\n",vertices[i],iso.vertices[i],(vertices[i]==iso.vertices[i])?"true":"false");
        totalSize += sizeof(iso.vertices[i]);
    }

    for (int i = 0; i < 60; i++){
        printf("%i:%i:%s\n",elements[i],iso.triangles[i],(elements[i]==iso.triangles[i])?"true":"false");
        totalTSize += sizeof(iso.triangles[i]);

    }
    printf("vcount:%i\nvsize:%i",iso.verticeCount,totalSize);
    printf("\ntcount:%i\ntsize:%i\n",iso.triangleCount,totalTSize);


    printf("\n\n%i\n\n",sizeof(vertices));
    printf("\n\n%i\n\n",sizeof(elements));



*/

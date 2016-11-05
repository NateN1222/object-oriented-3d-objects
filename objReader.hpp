#ifndef OBJREADER_HPP_INCLUDED
#define OBJREADER_HPP_INCLUDED

#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

#ifndef GLM_H_INCLUDED
#define GLM_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glm/glm.hpp> // instead of my structs should probably use GLM


#define LINE_SIZE 128

typedef struct {
    float x;
    float y;
    float z;
} vertex;

typedef struct {
    int v1;
    int v2;
    int v3;
}triangle ;

typedef struct {
    vertex *vertices;
    triangle *triangles;
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
    tri.v1 = atof(strtok (line," f"));
    tri.v2 = atof(strtok (NULL," f"));
    tri.v3 = atof(strtok (NULL," f"));
    //printf("%i , %i , % i\n",tri.v1,tri.v2,tri.v3);
    return tri;
}

obj readFile(char *objFile){
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

    return Object;
}

#endif // OBJREADER_HPP_INCLUDED

#include "object.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>
#include <cmath>
#include "object.hpp"


object::object(obj modl, glm::vec3 Pos, float scal,GLuint shader){

    scale = scal;
    shaderProgram = shader;
    spawned = false;
    model = modl;
    worldPosition = Pos;
    //rotationAngle = Ang;
    uniModel = glGetUniformLocation(shaderProgram, "model");

    // Create Vertex Array Object
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, model.verticeCount*sizeof(float), model.vertices, GL_STATIC_DRAW);

    // Create a Element Buffer Object and copy the element data to it
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.triangleCount*sizeof(GL_UNSIGNED_INT), (void*) model.triangles, GL_STATIC_DRAW);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GL_FLOAT), 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GL_FLOAT), (void*) (3*sizeof(GL_FLOAT)));

}

object::object(char* objFile, glm::vec3 Pos,float scal,GLuint shader){

    scale = scal;
    shaderProgram = shader;
    spawned = false;
    model = readObjFile(objFile);
    worldPosition = Pos;
    //rotationAngle = Ang;
    uniModel = glGetUniformLocation(shaderProgram, "model");

    // Create Vertex Array Object
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, model.verticeCount*sizeof(float), model.vertices, GL_STATIC_DRAW);

    // Create a Element Buffer Object and copy the element data to it
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.triangleCount*sizeof(GL_UNSIGNED_INT), (void*) model.triangles, GL_STATIC_DRAW);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GL_FLOAT), 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GL_FLOAT), (void*) (3*sizeof(GL_FLOAT)));
}

object::~object(){
    //dtor
    free(model.vertices); // maybe we can free these as soon as it gets put into the buffer
    free(model.triangles);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void object::spawn(){
    // load in the constructor, start drawing when this gets called
    spawned = true;
    //this.draw(); //  compiles?
}

void object::draw(float cum_x,float cum_y){

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);


    //set the model matrix uniform
    glm::mat4 modelMatrix;

    //modelMatrix = ( glm::rotate(glm::mat4(),cum_x/10,glm::vec3(0.0f,1.0f,0.0f)) ) * modelMatrix;
    //modelMatrix = ( glm::rotate(glm::mat4(),cum_y/10,glm::vec3(1.0f,0.0f,0.0f)) ) * modelMatrix;

    modelMatrix = glm::scale(modelMatrix, glm::vec3(scale, scale, scale)); // TODO: fix this, doesn't scale in local coords (scale uniform?)
    modelMatrix = glm::translate(modelMatrix, worldPosition);

    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));


    // draw
    glDrawElements(
         GL_TRIANGLES,      // mode
         model.triangleCount,    // count
         GL_UNSIGNED_INT,   // type
         (void*) 0          // element array buffer offset
    );

}



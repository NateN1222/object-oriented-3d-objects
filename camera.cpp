#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>
#include <cmath>
#include "camera.hpp"


camera::camera(glm::vec3 Pos, glm::vec3 Ang){
    spawned = false;
    worldPosition = Pos;
    rotationAngle = Ang;
    //uniView = glGetUniformLocation(shaderProgram, "View");
}

camera::~camera(){
    //dtor
}

void camera::spawn(){
    // load in the constructor, start drawing when this gets called
    spawned = true;
    //this.draw(); //  compiles?
}

void camera::draw(){

    glm::mat4 view = glm::lookAt(
        glm::vec3(1.2f, 1.2f, 1.2f), // the position of the camera
        // note: position should be made 0,0
        glm::vec3(0.0f, 0.0f, 0.0f), // the point to be centered on-screen
        glm::vec3(0.0f, 0.0f, 1.0f) // the up axis. Here up is defined as the Z axis, which implies that the XY plane is the "ground".
    );

}



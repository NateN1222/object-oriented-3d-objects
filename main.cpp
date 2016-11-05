#include <chrono>
#include <cmath>
#include <stdio.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLEW_STATIC
#include <GL/glew.h>

#define unit_length 0.2f
#define player_v unit_length*20
#define radius 1.0f


#include "object.hpp"
#include "camera.hpp"

#define DEG2RAD M_PI/180.0f

#define SCALE_MPOS_X 1.0f
#define SCALE_MPOS_Y 1.0f
#define WIDTH 800
#define HEIGHT 600




glm::vec3 rotateVector(glm::vec3 inputVector,glm::vec3 unitVectorAxis,float angle){
    if (angle == 0.0f){
        return glm::vec3(0.0f,0.0f,0.0f);
    }

    return inputVector*
    ((float) cos(angle))+
    (glm::cross(inputVector,unitVectorAxis)*
    ((float) sin(angle))+
    (unitVectorAxis *
     glm::dot(unitVectorAxis,inputVector))*
    (1-((float) cos(angle))));


}

shaders compileShaders(){
    // Shader sources
    const GLchar* vertexSource =
        "#version 150 core\n"
        "in vec3 position;"
        "in vec3 color;"
        "out vec3 Color;"
        "uniform mat4 model;"
        "uniform mat4 view;"
        "uniform mat4 proj;"
        "void main()"
        "{"
            "gl_Position = proj * view * model * vec4(position, 1.0);"
            "Color = color;"
        "}";

    const GLchar* fragmentSource =
        "#version 150 core\n"
        "in vec3 Color;"
        "out vec4 outColor;"
        "void main()"
        "{"
        "outColor = vec4(Color, 1.0);"
        "}";
        // Create and compile the vertex shader
    GLint status;

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    char buffer[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    glGetShaderInfoLog(vertexShader, 512, NULL, buffer);

    if(status == GL_TRUE){
        printf("vertex shader compiled.\n");
    } else{
        printf("\n\n%s\n\n",buffer);
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

    glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);

    if(status == GL_TRUE){
        printf("frag shader compiled.\n");
    } else{
        printf("\n\n%s\n\n",buffer);
    }

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    shaders ret;
    ret.frag = fragmentShader;
    ret.program = shaderProgram;
    ret.vert = vertexShader;

    return ret;
}

GLint lastVertice = (2*(6*sizeof(GL_FLOAT)))+3*sizeof(float);
GLint thisVertice;
int counter = 0;
//obj iso = readObjFile("iso.obj");
const float red[] = {1,0,0};
const float blue[] = {0,0,1};
bool clicked = false;
bool first = true;

void mbutton_callback(GLFWwindow* window, int button, int action, int mods){

    if(button == GLFW_MOUSE_BUTTON_1 && !clicked){
        clicked = true;
        first = true;
        glfwGetCursorPos(window,0,0);


    } else{
        clicked = false;

    }


}
double dx = 0;
double dy = 0;
float cum_x;
float cum_y;
double lastX;
double lastY;

void mpos_callback(GLFWwindow* window, double xpos, double ypos){


    if(clicked == true){
        if (first == true){
            lastX = xpos;
            lastY = ypos;
            first = false;
        } else{
            dx = (lastX-xpos)*SCALE_MPOS_X;
            dy = (lastY-ypos)*SCALE_MPOS_Y;

            cum_x += (float) dx;
            cum_y += (float) dy;

            //printf("x:%f,y:%f\n",dx,dy);

            lastX = xpos;
            lastY = ypos;
        }
    }
}

bool cursor_grabbed = false;

bool w_pressed = false;
bool a_pressed = false;
bool s_pressed = false;
bool d_pressed = false;

float angle = 1.0f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
/*
    //  void glBufferSubData​(enum target, intptr offset, sizeiptr size, const void *data)
    if (0 && key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS && counter < model.verticeCount / 6){

        counter = counter + 1;
        printf(" \n %i",counter);

        thisVertice = (counter*(6*sizeof(GL_FLOAT)))+3*sizeof(float);

        glBufferSubData(GL_ARRAY_BUFFER,lastVertice,3*sizeof(float),blue);
        glBufferSubData(GL_ARRAY_BUFFER,thisVertice,3*sizeof(float),red);

        lastVertice = thisVertice;

    }
*/
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        if(!cursor_grabbed){
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            cursor_grabbed = true;
        } else{
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            cursor_grabbed = false;
        }
    }
    if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS && counter != 0){

        counter = counter - 1;
        printf("\n %i",counter);


        thisVertice = (counter*(6*sizeof(GL_FLOAT)))+3*sizeof(float);
        glBufferSubData(GL_ARRAY_BUFFER,thisVertice,3*sizeof(float),red);
        glBufferSubData(GL_ARRAY_BUFFER,lastVertice,3*sizeof(float),blue);
        lastVertice = thisVertice;

//        glBufferData(GL_ARRAY_BUFFER, iso.verticeCount*sizeof(float),temp, GL_STATIC_DRAW);
    }
    if( (key == GLFW_KEY_W) && (action == GLFW_PRESS)){
        w_pressed = true;

    }
    if( (key == GLFW_KEY_A) && (action == GLFW_PRESS)){
        a_pressed = true;

    }
    if( (key == GLFW_KEY_S) && (action == GLFW_PRESS)){
        s_pressed = true;

    }
    if( (key == GLFW_KEY_D) && (action == GLFW_PRESS)){
        d_pressed = true;

    }
    if( (key == GLFW_KEY_W) && (action == GLFW_RELEASE)){
        w_pressed = false;

    }
    if( (key == GLFW_KEY_A) && (action == GLFW_RELEASE)){
        a_pressed = false;

    }
    if( (key == GLFW_KEY_S) && (action == GLFW_RELEASE)){
        s_pressed = false;

    }
    if( (key == GLFW_KEY_D) && (action == GLFW_RELEASE)){
        d_pressed = false;
    }

    if( (key == GLFW_KEY_V) && (action == GLFW_PRESS)){
        angle -= 1.0f;
        printf("angle: %f\n",angle);
    }
    if( (key == GLFW_KEY_B) && (action == GLFW_PRESS)){
        angle += 1.0f;
        printf("angle: %f\n",angle);

    }


}



int main(){
    auto t_start = std::chrono::high_resolution_clock::now();
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL",NULL,NULL); // Windowed
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window,mbutton_callback);
    glfwSetCursorPosCallback(window,mpos_callback);

    // compile shaders
    shaders programs = compileShaders();
    GLuint shaderProgram = programs.program;
    GLuint vertexShader = programs.vert;
    GLuint fragmentShader = programs.frag;

    // setting up view transformation

    //GLint uniModel = glGetUniformLocation(shaderProgram, "model");
    GLint uniView = glGetUniformLocation(shaderProgram, "view");

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);
    GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // important

    glm::vec3 Test = glm::vec3(4.0f,0.0f,0.0f);
    glm::vec3 Test2 = glm::vec3(0.0f,4.0f,0.0f);
    glm::vec3 Test3 = glm::vec3(0.0f,0.0f,4.0f);
    glm::vec3 Test4 = glm::vec3(2.0f,0.0f,0.0f);
    glm::vec3 Test5 = glm::vec3(0.0f,2.0f,0.0f);
    glm::vec3 Test6 = glm::vec3(0.0f,0.0f,2.0f);



    object izo1("isor.obj",Test,0.005f,shaderProgram);
    object izo2("isog.obj",Test2,0.005f,shaderProgram);
    object izo3("iso.obj",Test3,0.005f,shaderProgram);
    object izo4("isor.obj",Test4,0.005f,shaderProgram);
    object izo5("isog.obj",Test5,0.005f,shaderProgram);
    object izo6("iso.obj",Test6,0.005f,shaderProgram);

    object refPoint("isog.obj",Test6,0.002f,shaderProgram);
    object refPoint2("isog.obj",Test6,0.002f,shaderProgram);
    object refPoint3("isor.obj",Test6,0.001f,shaderProgram);
    object refPoint4("iso.obj",Test6,0.001f,shaderProgram);




    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(glm::mat4()));
    float lastTime = 0.0f;
    glm::vec3 playerPos = glm::vec3(1.0f,1.0f,1.0f); // world
    glm::vec3 origin = glm::vec3(0.0f,0.0f,0.0f); // world
    glm::vec3 lookDir; // local
    glm::vec3 lookDir2; // local
    glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f); // local, pitch = 2pi or 0
    glm::vec3 right = glm::vec3(1.0f,0.0f,0.0f); // local, yaw = 2pi or 0
    float pitch = 0;
    float yaw = 0;
    float pitch2 = 0;
    float yaw2 = 0;

    while(!glfwWindowShouldClose(window)){
        auto t_now = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
        float d_time = time - lastTime;
        lastTime = time;
        // note: eventually we will want to sync frames with time


        if(w_pressed){
            playerPos.z -= d_time*player_v;
            printf("[%f,%f,%f]\n",playerPos.x,playerPos.y,playerPos.z);

        }
        if(a_pressed){
            playerPos.x -= d_time*player_v;
            printf("[%f,%f,%f]\n",playerPos.x,playerPos.y,playerPos.z);
        }
        if(s_pressed){
            playerPos.z += d_time*player_v;
            printf("[%f,%f,%f]\n",playerPos.x,playerPos.y,playerPos.z);

        }
        if(d_pressed){
            playerPos.x += d_time*player_v;
            printf("[%f,%f,%f]\n",playerPos.x,playerPos.y,playerPos.z);

        }


        //////////////////////////////view////////////////////////////////////

        // pitch is along x axis
        yaw = cum_x/50;
        pitch = 0.0f;

        yaw2 = 0.0f;
        pitch2 = (cum_y/50);

        glm::vec3 pos = glm::vec3(sin(yaw),0,cos(yaw));
        glm::vec3 pos2 = glm::vec3(0,sin(pitch),cos(pitch));

        glm::vec3 pos3 = glm::vec3(sin(yaw2),0,cos(yaw2));
        glm::vec3 pos4 = glm::vec3(0,sin(pitch2),cos(pitch2));

        lookDir = 3.0f*(glm::normalize((pos+pos2))+glm::normalize(pos3+pos4));
        //lookDir = 3.0f*glm::normalize(rotateVector(lookDir,glm::vec3(0.0f,1.0f,0.0f),yaw));

        lookDir2 = 3.0f*glm::normalize(glm::vec3(-lookDir.x,lookDir.y,-lookDir.z));
        refPoint.SetworldPosition(glm::normalize((pos+pos2)));
        refPoint2.SetworldPosition(glm::normalize(pos3+pos4));
        refPoint3.SetworldPosition(lookDir);
        refPoint4.SetworldPosition(lookDir2);

        glm::mat4 view = glm::lookAt(
            playerPos, // the position of the camera
            origin, // convert from local to world
            up // the up axis
        );

        glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
        ////////////////////////////////////////////////////////////////////////

        glClear(GL_COLOR_BUFFER_BIT);

        izo1.draw(cum_x,cum_y);
        izo2.draw(cum_x,cum_y);
        izo3.draw(cum_x,cum_y);
        izo4.draw(cum_x,cum_y);
        izo5.draw(cum_x,cum_y);
        izo6.draw(cum_x,cum_y);
        refPoint.draw(cum_x,cum_y); // X component of view
        refPoint2.draw(cum_x,cum_y); // Y component of view
        refPoint3.draw(cum_x,cum_y); // first viewDir
        refPoint4.draw(cum_x,cum_y); // alt viewDir

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // black
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // memory leaks?
    return 0;
}

/*

        //////////////////////////////view////////////////////////////////////

        // pitch is along x axis
        yaw = cum_x/50;
        pitch = 0.0f;

        yaw2 = 0.0f;
        pitch2 = (cum_y/50);

        glm::vec3 pos = glm::vec3(sin(yaw),0,cos(yaw));
        glm::vec3 pos2 = glm::vec3(0,sin(pitch),cos(pitch));

        glm::vec3 pos3 = glm::vec3(sin(yaw2),0,cos(yaw2));
        glm::vec3 pos4 = glm::vec3(0,sin(pitch2),cos(pitch2));

        lookDir = 3.0f*(glm::normalize((pos+pos2))+glm::normalize(pos3+pos4));
        lookDir2 = glm::vec3(-lookDir.x,lookDir.y,-lookDir.z);
        refPoint.SetworldPosition(glm::normalize((pos+pos2)));
        refPoint2.SetworldPosition(glm::normalize(pos3+pos4));
        refPoint3.SetworldPosition(lookDir);
        refPoint4.SetworldPosition(lookDir2);

        glm::mat4 view = glm::lookAt(
            playerPos, // the position of the camera
            origin, // convert from local to world
            up // the up axis
        );

        glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
        ////////////////////////////////////////////////////////////////////////

        glClear(GL_COLOR_BUFFER_BIT);

        izo1.draw(cum_x,cum_y);
        izo2.draw(cum_x,cum_y);
        izo3.draw(cum_x,cum_y);
        izo4.draw(cum_x,cum_y);
        izo5.draw(cum_x,cum_y);
        izo6.draw(cum_x,cum_y);
        refPoint.draw(cum_x,cum_y); // X component of view
        refPoint2.draw(cum_x,cum_y); // Y component of view
        refPoint3.draw(cum_x,cum_y); // first viewDir
        refPoint4.draw(cum_x,cum_y); // alt viewDir

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // black
        glfwSwapBuffers(window);
        glfwPollEvents();
*/

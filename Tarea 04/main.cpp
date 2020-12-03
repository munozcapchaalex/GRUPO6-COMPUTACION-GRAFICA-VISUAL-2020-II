#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include <vector>

#include "Utils.hpp"

using namespace std;

#define WIDTH 800
#define HEIGHT 800

GLFWwindow* window;
GLuint renderingProgram;
GLuint VBO;
GLuint VAO;
vector<GLdouble> vertices={
		-1.0f, -1.0f, 0.0f, //Triangle 01
		-1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, //Triangle 02
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f
};

void init(GLFWwindow *window){
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLdouble)*vertices.size(), &vertices[0], GL_STATIC_DRAW);

    renderingProgram=Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl");
    glUseProgram(renderingProgram);
}

void display(double currentTime){
	GLuint uTime = glGetUniformLocation(renderingProgram, "u_time");
	glProgramUniform1f(renderingProgram, uTime, currentTime);

	GLuint uResolution = glGetUniformLocation(renderingProgram, "u_resolution");
	glProgramUniform2f(renderingProgram, uResolution, WIDTH, HEIGHT);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 6);

}

int main(){
    if (!glfwInit()){
    	exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window=glfwCreateWindow(WIDTH, HEIGHT, "Tarea 04: GLSL(Shaders)", NULL, NULL);

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK){
    	exit(EXIT_FAILURE);
    }

    glfwSwapInterval(0); // Enable vsync

    init(window);

    while (!glfwWindowShouldClose(window)){
        glfwPollEvents();
        display(glfwGetTime());
        glfwSwapBuffers(window);
    }

    glDeleteBuffers(1, &VBO);
    glDeleteShader(renderingProgram);
    glDeleteVertexArrays(1, &VAO);


    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

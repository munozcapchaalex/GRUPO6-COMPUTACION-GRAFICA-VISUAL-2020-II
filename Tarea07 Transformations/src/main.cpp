//============================================================================
// Name        : Display Simple Solar System version Resizable
// Professor   : Herminio Paucar
// Version     :
// Description :
//============================================================================

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <cmath>
#include <stack>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Utils.h"

using namespace std;

#define numVAOs 1
#define numVBOs 4

// Utils util = Utils();
float cameraX, cameraY, cameraZ;
float x1 = 5.0f;
float inc = 0.05f;
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

// variable allocation for display
GLuint mvLoc, projLoc;
// GLuint mvLoc, projLoc;
int width, height;
float aspect;
float timeFactor;
glm::mat4 pMat, vMat, mMat, mvMat;

stack<glm::mat4> mvStack;

int dimVertices;
int numberOfVertices;

void setupVertices(void) {
	// 12 triangles * 3 vertices * 3 values (x, y, z)
	float cubePositions[108] = {
			-1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f,
			-1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f, };
	// 6 triangles * 3 vertices * 3 values
	float pyramidPositions[54] = { -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, -1.0f,
			-1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f };

	float rectangulo[24] = {-0.05f, 1.0f, 0.0f, -0.05f, -1.0f, 0.0f,
							0.05f,-1.0f, 0.0f, 0.05f, 1.0f, 0.0f,
							-0.05f, 1.0f, 0.0f, -0.05f, -1.0f, 0.0f,
							0.05f,-1.0f, 0.0f, 0.05f, 1.0f, 0.0f};

		GLfloat x = 0;
		GLfloat y = 0;
		GLfloat z = 0;
		GLdouble radius = 0.4;
		GLint numberOfSides = 51;
		numberOfVertices = numberOfSides+1;
		GLfloat twicePi = 2.0f * M_PI;

		GLfloat verticesX[numberOfVertices];
		GLfloat verticesY[numberOfVertices];
		GLfloat verticesZ[numberOfVertices];
		verticesX[0] = x;
		verticesY[0] = y;
		verticesZ[0] = z;

		for (int i = 1; i < numberOfVertices; i++) {
			verticesX[i] = x + (radius * cos(i * twicePi / (numberOfSides-1)));
			verticesY[i] = y + (radius * sin(i * twicePi / (numberOfSides-1)));
			verticesZ[i] = z;
			if(i==51){
				int j=1;
				verticesX[i] = x + (radius * cos(j * twicePi / (numberOfSides-1)));
				verticesY[i] = y + (radius * sin(j * twicePi / (numberOfSides-1)));
				verticesZ[i] = z;
			}
		}
		dimVertices = (numberOfVertices) * 3;
		GLfloat m_Vertices[dimVertices];

		for (int i = 1; i < numberOfVertices; i++) {
			m_Vertices[i * 3] = verticesX[i];
			m_Vertices[i * 3 + 1] = verticesY[i];
			m_Vertices[i * 3 + 2] = verticesZ[i];
		}





	// we need at least 1 VAO and 2 VBOs
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numVBOs, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubePositions), cubePositions,
			GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(pyramidPositions),pyramidPositions,
			GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(m_Vertices),m_Vertices,
			GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(rectangulo),rectangulo,
			GL_STATIC_DRAW);

}

void init(GLFWwindow *window) {
	renderingProgram = Utils::createShaderProgram("src/vertShader.glsl", "src/fragShader.glsl");

	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float) width / (float) height;
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); // 1.0472 radians == 60 degrees

	// position the camera further down the positive Z axis (to see all of the cubes)
	cameraX = 0.0f;
	cameraY = 0.0f;
	cameraZ = 12.0f;
	setupVertices();
}

// repeatedly
void display(GLFWwindow *window, double currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");

	GLuint time = glGetUniformLocation(renderingProgram, "utime");
	glProgramUniform1f(renderingProgram, time, currentTime);

    x1 += inc;
    // switch to moving the triangle to the left
    if (x1 > 12.0f) inc = -0.05f;
    // switch to moving the triangle to the right
    if (x1 < 0.0f) inc = 0.05f;



	// push view matrix onto the stack
	vMat = glm::translate(glm::mat4(1.0f),
	//vMat = glm::translate(glm::mat4(1.0f),
			glm::vec3(-cameraX, -cameraY, -cameraZ));
	mvStack.push(vMat);

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	// pyramid sun

	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f),
	//mvStack.top() *= glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, 0.0f, 0.0f));  // sun position

	mvStack.push(mvStack.top());  // duplicating
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float) currentTime,
			glm::vec3(3.0f, 0.0f, 0.0f));  // sun rotation
			//glm::vec3(1.0f, 0.0f, 0.0f));  // sun rotation


	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//glDrawArrays(GL_TRIANGLES, 0, 18);
	mvStack.pop();
	//fondo
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f),
	//mvStack.top() *= glm::translate(glm::mat4(1.0f),
	glm::vec3(0.0f, 0.0f, 0.0f));  // sun position
	mvStack.top() *= glm::scale(glm::mat4(1.0f),glm::vec3(40.0f, 6.8f, 0.0f));

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, 24);
	mvStack.pop();
	//fondo2
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f),
	//mvStack.top() *= glm::translate(glm::mat4(1.0f),
	glm::vec3(0.0f, 0.0f, 0.0f));  // sun position
	mvStack.top() *= glm::scale(glm::mat4(1.0f),glm::vec3(20.0f, 3.4f, 0.0f));

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, 24);
	mvStack.pop();
//CIRCULO
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f),
	//mvStack.top() *= glm::translate(glm::mat4(1.0f),
			glm::vec3(-7+x1, -5.0f, 0.0f));  // sun position

	mvStack.top() *= glm::scale(glm::mat4(1.0f),
				glm::vec3(x1*0.5, x1*0.5, 0.0f));  // make the moon smaller

	//mvStack.push(mvStack.top());  // duplicating

	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float) currentTime,
	glm::vec3(1.0f, 0.0f, 0.0f));  // sun rotation
			//glm::vec3(1.0f, 0.0f, 0.0f));  // sun rotation


	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLE_FAN, 1, numberOfVertices-1);
	mvStack.pop();

	//CIRCULO PENDULo
		mvStack.push(mvStack.top());
		mvStack.top() *= glm::translate(glm::mat4(1.0f),
		//mvStack.top() *= glm::translate(glm::mat4(1.0f),
				//glm::vec3(0.0f, 0.0f, 0.0f));  // sun position

				glm::vec3( sin((float) currentTime) * 0.5, 0.0f, 0.0f));
		//glm::vec3(0.0f, sin((float) currentTime) * 2.0,
			//	cos((float) currentTime) * 2.0));

		//mvStack.top() *= glm::scale(glm::mat4(1.0f),
			//		glm::vec3(0.0f, 0.0f, 0.0f));  // make the moon smaller

		//mvStack.push(mvStack.top());  // duplicating

		//mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float) currentTime,
		//glm::vec3(0.0f, 0.0f, 0.0f));  // sun rotation
				//glm::vec3(1.0f, 0.0f, 0.0f));  // sun rotation


		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		//glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LEQUAL);
		glDrawArrays(GL_TRIANGLE_FAN, 1, numberOfVertices-1);
		mvStack.pop();

//barra pendulo
		mvStack.push(mvStack.top());
		mvStack.top() *= glm::translate(glm::mat4(1.0f),
		//mvStack.top() *= glm::translate(glm::mat4(1.0f),
				glm::vec3(0.0f, 1.4f, 0.0f));  // sun position

		mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float) currentTime,
				glm::vec3( 0.0f, 0.1f,0.0f));
		//glm::vec3(0.0f, sin((float) currentTime) * 2.0,
			//	cos((float) currentTime) * 2.0));

		//mvStack.top() *= glm::scale(glm::mat4(1.0f),
			//		glm::vec3(0.0f, 0.0f, 0.0f));  // make the moon smaller

		//mvStack.push(mvStack.top());  // duplicating

		//mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float) currentTime,
		//glm::vec3(0.0f, 0.0f, 0.0f));  // sun rotation
				//glm::vec3(1.0f, 0.0f, 0.0f));  // sun rotation


		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		//glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LEQUAL);
		glDrawArrays(GL_TRIANGLES, 0, 24);
		mvStack.pop();

		//barra reloj
		mvStack.push(mvStack.top());
		mvStack.top() *= glm::translate(glm::mat4(1.0f),
		//mvStack.top() *= glm::translate(glm::mat4(1.0f),
		glm::vec3(0.0f, 5.0f, 0.0f));  // sun position

		mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float) currentTime,
		glm::vec3( 0.0f, 0.0f,1.0f));

		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		//glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LEQUAL);
		glDrawArrays(GL_TRIANGLES, 0, 24);
		mvStack.pop();

		//barra reloj 2
		mvStack.push(mvStack.top());
		mvStack.top() *= glm::translate(glm::mat4(1.0f),
		//mvStack.top() *= glm::translate(glm::mat4(1.0f),
		glm::vec3(0.0f, 5.0f, 0.0f));  // sun position

		mvStack.top() *= glm::scale(glm::mat4(1.0f),glm::vec3(0.5f, 0.5f, 0.0f));

		mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float) currentTime,
		glm::vec3( 0.5f, 0.2f,0.02f));

		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		//glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LEQUAL);
		glDrawArrays(GL_TRIANGLES, 0, 24);
		mvStack.pop();

	    //CIRCULO reloj
		mvStack.push(mvStack.top());
		mvStack.top() *= glm::translate(glm::mat4(1.0f),
		//mvStack.top() *= glm::translate(glm::mat4(1.0f),
		glm::vec3(0.0f, 6.5f, 0.0f));  // sun position
		mvStack.top() *= glm::scale(glm::mat4(1.0f),glm::vec3(0.5, 0.5, 0.0f));
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLE_FAN, 1, numberOfVertices-1);
		mvStack.pop();

		//CIRCULO reloj1
		mvStack.push(mvStack.top());
		mvStack.top() *= glm::translate(glm::mat4(1.0f),
		//mvStack.top() *= glm::translate(glm::mat4(1.0f),
		glm::vec3(0.0f, 3.5f, 0.0f));  // sun position
		mvStack.top() *= glm::scale(glm::mat4(1.0f),glm::vec3(0.5, 0.5, 0.0f));
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLE_FAN, 1, numberOfVertices-1);
		mvStack.pop();

		//CIRCULO reloj2
		mvStack.push(mvStack.top());
		mvStack.top() *= glm::translate(glm::mat4(1.0f),
		//mvStack.top() *= glm::translate(glm::mat4(1.0f),
		glm::vec3(-1.5f, 5.0f, 0.0f));  // sun position
		mvStack.top() *= glm::scale(glm::mat4(1.0f),glm::vec3(0.5, 0.5, 0.0f));
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLE_FAN, 1, numberOfVertices-1);
		mvStack.pop();

		//CIRCULO reloj3
		mvStack.push(mvStack.top());
		mvStack.top() *= glm::translate(glm::mat4(1.0f),
		//mvStack.top() *= glm::translate(glm::mat4(1.0f),
		glm::vec3(1.5f, 5.0f, 0.0f));  // sun position
		mvStack.top() *= glm::scale(glm::mat4(1.0f),glm::vec3(0.5, 0.5, 0.0f));
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLE_FAN, 1, numberOfVertices-1);
		mvStack.pop();

		//CIRCULO reloj4
		mvStack.push(mvStack.top());
		mvStack.top() *= glm::translate(glm::mat4(1.0f),
		//mvStack.top() *= glm::translate(glm::mat4(1.0f),
		glm::vec3(1.5f, 5.0f, 0.0f));  // sun position
		mvStack.top() *= glm::scale(glm::mat4(1.0f),glm::vec3(0.5, 0.5, 0.0f));
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLE_FAN, 1, numberOfVertices-1);
		mvStack.pop();

		//CIRCULO reloj5
		mvStack.push(mvStack.top());
		mvStack.top() *= glm::translate(glm::mat4(1.0f),
		//mvStack.top() *= glm::translate(glm::mat4(1.0f),
		glm::vec3(0.8f, 6.2f, 0.0f));  // sun position
		mvStack.top() *= glm::scale(glm::mat4(1.0f),glm::vec3(0.5, 0.5, 0.0f));
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLE_FAN, 1, numberOfVertices-1);
		mvStack.pop();

		//CIRCULO reloj6
		mvStack.push(mvStack.top());
		mvStack.top() *= glm::translate(glm::mat4(1.0f),
		//mvStack.top() *= glm::translate(glm::mat4(1.0f),
		glm::vec3(1.3f, 5.7f, 0.0f));  // sun position
		mvStack.top() *= glm::scale(glm::mat4(1.0f),glm::vec3(0.5, 0.5, 0.0f));
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLE_FAN, 1, numberOfVertices-1);
		mvStack.pop();

		//CIRCULO reloj7
		mvStack.push(mvStack.top());
		mvStack.top() *= glm::translate(glm::mat4(1.0f),
		//mvStack.top() *= glm::translate(glm::mat4(1.0f),
		glm::vec3(-0.8f, 6.2f, 0.0f));  // sun position
		mvStack.top() *= glm::scale(glm::mat4(1.0f),glm::vec3(0.5, 0.5, 0.0f));
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLE_FAN, 1, numberOfVertices-1);
		mvStack.pop();

		//CIRCULO reloj8
		mvStack.push(mvStack.top());
		mvStack.top() *= glm::translate(glm::mat4(1.0f),
		//mvStack.top() *= glm::translate(glm::mat4(1.0f),
		glm::vec3(-1.3f, 5.7f, 0.0f));  // sun position
		mvStack.top() *= glm::scale(glm::mat4(1.0f),glm::vec3(0.5, 0.5, 0.0f));
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLE_FAN, 1, numberOfVertices-1);
		mvStack.pop();

		//CIRCULO reloj9
		mvStack.push(mvStack.top());
		mvStack.top() *= glm::translate(glm::mat4(1.0f),
		//mvStack.top() *= glm::translate(glm::mat4(1.0f),
		glm::vec3(-0.8f, 3.8f, 0.0f));  // sun position
		mvStack.top() *= glm::scale(glm::mat4(1.0f),glm::vec3(0.5, 0.5, 0.0f));
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLE_FAN, 1, numberOfVertices-1);
		mvStack.pop();

		//CIRCULO reloj10
		mvStack.push(mvStack.top());
		mvStack.top() *= glm::translate(glm::mat4(1.0f),
		//mvStack.top() *= glm::translate(glm::mat4(1.0f),
		glm::vec3(-1.3f, 4.2f, 0.0f));  // sun position
		mvStack.top() *= glm::scale(glm::mat4(1.0f),glm::vec3(0.5, 0.5, 0.0f));
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLE_FAN, 1, numberOfVertices-1);
		mvStack.pop();

		//CIRCULO reloj11
		mvStack.push(mvStack.top());
		mvStack.top() *= glm::translate(glm::mat4(1.0f),
		//mvStack.top() *= glm::translate(glm::mat4(1.0f),
		glm::vec3(0.8f, 3.8f, 0.0f));  // sun position
		mvStack.top() *= glm::scale(glm::mat4(1.0f),glm::vec3(0.5, 0.5, 0.0f));
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLE_FAN, 1, numberOfVertices-1);
		mvStack.pop();

		//CIRCULO reloj12
		mvStack.push(mvStack.top());
		mvStack.top() *= glm::translate(glm::mat4(1.0f),
		//mvStack.top() *= glm::translate(glm::mat4(1.0f),
		glm::vec3(1.3f, 4.2f, 0.0f));  // sun position
		mvStack.top() *= glm::scale(glm::mat4(1.0f),glm::vec3(0.5, 0.5, 0.0f));
		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLE_FAN, 1, numberOfVertices-1);
		mvStack.pop();
/*
	// cube planet

	mvStack.push(mvStack.top());  // mvMat of sun
	mvStack.top() *= glm::translate(glm::mat4(1.0f),
			glm::vec3(sin((float) currentTime) * 4.0, 0.0f,
					cos((float) currentTime) * 4.0));  // planet position
	mvStack.push(mvStack.top());  // duplicating
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float) currentTime,
			glm::vec3(0.0, 1.0, 0.0));  // planet rotation

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LEQUAL);


	//glDrawArrays(GL_TRIANGLES, 0, 36);
	mvStack.pop();

	// cube moon

	mvStack.push(mvStack.top());  // mvMat of planet
	mvStack.top() *= glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, sin((float) currentTime) * 2.0,
					cos((float) currentTime) * 2.0));  // moon position
	mvStack.push(mvStack.top());  // duplicating
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float) currentTime,
			glm::vec3(0.0, 0.0, 1.0));  // moon rotation

	mvStack.top() *= glm::scale(glm::mat4(1.0f),
			glm::vec3(0.25f, 0.25f, 0.25f));  // make the moon smaller
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	//    glEnable(GL_DEPTH_TEST);
	//    glDepthFunc(GL_LEQUAL);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	mvStack.pop();

	mvStack.pop();
	mvStack.pop();
	mvStack.pop();*/
}

void window_size_callback(GLFWwindow* win, int newWidth, int newHeight) {
    aspect = (float)newWidth / (float)newHeight;
    glViewport(0, 0, newWidth, newHeight);
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}

int main(void) {
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);     //
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); 	// Resizable option.

	GLFWwindow *window = glfwCreateWindow(800, 800, "Tarea07 Transformations", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		exit(EXIT_FAILURE);
	}
	glfwSwapInterval(1);

    glfwSetWindowSizeCallback(window, window_size_callback);

	init(window);

	// the rate at which display() is called is referred to as the frame rate
	while (!glfwWindowShouldClose(window)) {
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

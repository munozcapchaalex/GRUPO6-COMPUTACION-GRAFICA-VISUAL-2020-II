#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw.h"
#include "imgui\imgui_impl_opengl3.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <iostream>

#include "utils.h"

GLFWwindow *window;
GLuint program;
GLuint m_VAO;
GLuint m_VBO;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
ImVec4 circle_color = ImVec4(0.5f, 1.0f, 0.3f, 1.0f);
int dimVertices;
int numberOfVertices;
float x = 0.0f;
float y = 0.0f;

void init(GLFWwindow *window){
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsClassic();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    program = createShaderProgram("vshader.glsl", "fshader.glsl" );

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

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(
			GL_ARRAY_BUFFER,
			dimVertices * sizeof(GLfloat),
			m_Vertices,
			GL_STATIC_DRAW
	);

	glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*) 0
	);
	glEnableVertexAttribArray(0);
}

void display(){
	glUseProgram(program);
    glClear(GL_COLOR_BUFFER_BIT);

    static float tras_x = 0, tras_y=0;
    static float rota_x = 0, rota_y = 0;
    static float scale = 1;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowSize(ImVec2(400, 300));
    ImGui::SetNextWindowPos(ImVec2(400,0));

    ImGui::Begin("Panel de control");

    ImGui::Text("Traslaciones");
    ImGui::Separator();

    if(ImGui::Button("Mover Arriba")){
    		tras_y+=0.1f;
    }
    ImGui::SameLine();
    if(ImGui::Button("Mover Abajo")){
    		tras_y-=0.1f;
    }
    if(ImGui::Button("Mover Izquierda")){
    		tras_x-=0.1f;
    }
    ImGui::SameLine();
	if(ImGui::Button("Mover Derecha")){
		tras_x+=0.1f;
	}

    ImGui::Text("Rotaciones");
    ImGui::Separator();
	if(ImGui::Button("Rotar Arriba")){
		rota_x =  rota_x-M_PI /15;
	}
	ImGui::SameLine();
	if(ImGui::Button("Rotar Abajo")){
		rota_x = rota_x +M_PI /15;
	}
	if(ImGui::Button("Rotar Izquierda")){
			rota_y= rota_y +M_PI /15;
	}
	ImGui::SameLine();
	if(ImGui::Button("Rotar Derecha")){
		rota_y = rota_y-M_PI /15;
	}

	ImGui::Text("Escalamiento");
	ImGui::Separator();
	if(ImGui::Button("Escala Grande")){
		scale =  scale+0.1;
	}
	ImGui::SameLine();
	if(ImGui::Button("Escala Pequenia")){
		scale =  scale-0.1;
	}

	ImGui::Text("Cambio de Colores");
	ImGui::Separator();
	ImGui::ColorEdit3("color de fondo", (float*)&clear_color);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	ImGui::ColorEdit3("color de circulo", (float*)&circle_color);
	ImGui::Separator();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate); // Muestra los FPS de la aplicación
	ImGui::End();

	GLuint color = glGetUniformLocation(program, "circle");
	glProgramUniform3f(program, color, circle_color.x, circle_color.y, circle_color.z);

    glm::mat4 trans = translate(glm::mat4(1), glm::vec3(tras_x, tras_y, 0));
    trans = glm::rotate(trans, rota_x, glm::vec3(1, 0, 0));
    trans = glm::rotate(trans, rota_y, glm::vec3(0, 1, 0));
    trans = glm::scale(trans, glm::vec3(scale, scale, 1));

    glUniformMatrix4fv(glGetUniformLocation(program, "transformation_matrix"), 1, false, value_ptr(trans));

    glDrawArrays(GL_TRIANGLE_FAN, 1, numberOfVertices-1);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int main(){
    if (!glfwInit()) exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_RESIZABLE,false);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Tarea 05: Shaders y IMGUI", NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    if (glewInit() != GLEW_OK) exit(EXIT_FAILURE);

    init(window);

    while (!glfwWindowShouldClose(window)){
        glfwPollEvents();
        display();
        glfwSwapBuffers(window);
    }

    glDeleteBuffers(1, &m_VBO);
    glDeleteShader(program);
    glDeleteVertexArrays(1, &m_VAO);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

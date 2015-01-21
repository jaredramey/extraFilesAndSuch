#include <glew.h>
#include <wglew.h>
#include <glfw3.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Entity.h"
#include "SOIL.h"

//Function Prototypes


Entity start;
Entity other;

int main()
{
	//initialize GLFW, create a window, Initialize GLEW and then enable Depth
	start.Initialize();
	
	/*//create shader programs
	GLuint uiProgramFlat = CreateProgram("VertexShader.glsl", "FlatFragmentShader.glsl");
	GLuint uiProgramTextured = CreateProgram("VertexShader.glsl" , "TexturedFragmentShader.glsl");

	//find the position of the matrix var in the shader so we can send info there later
	GLuint MatrixIDFlat = glGetUniformLocation(uiProgramFlat, "MVP");

	//set up the mapping of the screen to pixel co-ordinates. Try changing values and see what happens
	float *orthographicProjection = getOrtho(0, 1080, 0, 720, 0, 180); */

	Entity::TriangleVertex* test_Triangle = new Entity::TriangleVertex[3];


	float points2[] =
	{
		0.9f, 0.5f, 1.0f,
		1.0f, 0.5f, 1.0f,
		0.5f, 0.5f, 1.0f,
	};

	start.points[0] = 0.0f;
	start.points[1] = 0.5f;
	start.points[2] = 0.0f;
	start.points[3] = 0.5f;
	start.points[4] = -0.5f;
	start.points[5] = 0.0f;
	start.points[6] = -0.5f;
	start.points[7] = -0.5f;
	start.points[8] = 0.0f;

	other.points[0] = -0.5f;
	other.points[1] = 0.0f;
	other.points[2] = -0.5f;
	other.points[3] = 0.0f;
	other.points[4] = 0.5f;
	other.points[5] = 0.0f;
	other.points[6] = 0.5f;
	other.points[7] = 0.5f;
	other.points[8] = 0.0f;

	const char* vertex_shader =
		"#version 400\n"
		"in vec3 vp;"
		"void main(){"
		"gl_Position = vec4(vp, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 400\n"
		"out vec4 frag_color;"
		"void main(){"
		"frag_color = vec4(0.0,0.0,1.0,1.0);"
		"}";

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fs);
	glAttachShader(shaderProgram, vs);
	glLinkProgram(shaderProgram);


	//loop until the user closes the window
	while (!glfwWindowShouldClose(start.window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderProgram);
		//send orthographic projection info to shader
		//glUniformMatrix4fv(MatrixIDFlat, 1, GL_FALSE, orthographicProjection);

		start.DrawTriangle();
		other.DrawTriangle();

		//swap front and back buffers
		glfwSwapBuffers(start.window);

		//poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


//Functions


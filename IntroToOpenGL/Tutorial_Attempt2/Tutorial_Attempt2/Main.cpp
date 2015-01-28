

#include <vector>
#include <string>
#include <fstream>
#include <iostream>



#include <glew.h>
#include "glfont.h"
//#include <wglew.h>
#include <glfw3.h>

#include "SOIL.h"

#include "Entity.h"

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
	
	
	//trying to get glfont working
	//Initialize OpenGL
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Initialize the viewport
	glViewport(0, 0, 640, 480);

	//Initialize OpenGL projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, 640.0f, 480.0f, 0.0f, -2.0f, 2.0f);

	//Clear back buffer
	glClear(GL_COLOR_BUFFER_BIT);

	//Create font
	GLuint textureName;
	glGenTextures(1, &textureName);
	PixelPerfectGLFont font;
	try {
		font.Create("DatFont.glf", textureName);
	}
	catch (GLFontError::InvalidFile) {
		std::cerr << "Cannot load font\n";
		abort();
	}

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

	bool drawTriangle;

	//loop until the user closes the window
	while (!glfwWindowShouldClose(start.window))
	{
		drawTriangle = false;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//send orthographic projection info to shader
		//glUniformMatrix4fv(MatrixIDFlat, 1, GL_FALSE, orthographicProjection);
	
		//Draw some stuff
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glColor3f(1.0f, 1.0f, 1.0f);


		try {
			font.Begin();

			font.TextOutThing("hello my wonderfull world", 400, 200, 0);
			font.TextOutThing("Test", 50, 50, 0);
		}
		catch (GLFontError::InvalidFont) {
			std::cerr << "Trying to draw with an uninitialized font\n";
			abort();
		}

		glDisable(GL_TEXTURE_2D);
		glLoadIdentity();

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


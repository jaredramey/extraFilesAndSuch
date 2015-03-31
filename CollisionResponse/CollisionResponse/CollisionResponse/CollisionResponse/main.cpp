#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "Timer.h"
#include "Shaders.h"
#include "Circle.h"
#include "Window.h"

#include <Vector2.h>
#include <Vector3.h>
#include <Matrix3x3.h>
#include <Matrix4x4.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static GLFWwindow* pWin = nullptr;

static int iScreenWidth = 1280;
static int iScreenHeight = 720;

bool Setup();

int main ()
{
	if ( !Setup() )
	{
		printf("Init failed!\n");
		return 1;
	}

	srand((unsigned int)time(0));

	//create shader program
	GLuint uiProgramFlat = CreateProgram("./Resources/VertexShader.glsl", "./Resources/FlatFragmentShader.glsl");
	//find the position of the matrix variable in the shader so we can send info there later
	GLuint MatrixIDFlat = glGetUniformLocation(uiProgramFlat, "mViewProj");
	//set up the mapping of the screen to pixel co-ordinates. (0,0) is the center of the screen, with 1 world spac unit = one screen space pixel
	Matrix4x4 mViewProj = Matrix4x4::GetOrtho(-iScreenWidth/2.f, iScreenWidth/2.f, -iScreenHeight/2.f, iScreenHeight/2.f, 0, 100);
	//Set clear color to black
	glClearColor(0,0,0,1);

	///////////////////////////////////////////////////////////////////////////////
	const int CIRCLE_COUNT = 20;
	Circle myCircle[CIRCLE_COUNT];
	
	//loop through the circles, creating each one with a radius of 20
	//set them to start with a random position and velocity
	for ( int i = 0 ; i < CIRCLE_COUNT ; ++i)
	{
		myCircle[i] = Circle(20, Vector4(1,0,0,1));
		//set each circle to a random position and velocity
		myCircle[i].SetPosition(Vector3(
			  rand() % (int)GetWindowDimensions().x - GetWindowDimensions().x / 2.f
			, rand() % (int)GetWindowDimensions().y - GetWindowDimensions().y / 2.f
			, 1));

		myCircle[i].SetVelocity(
			Vector3(rand() % 1000 - 500.f, rand() % 1000 - 500.f, 0)
			);
	}

	while (!glfwWindowShouldClose(pWin))
	{
		Timer::Get()->UpdateTimer();
		float dt = (float)Timer::Get()->GetDeltaTime();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glUseProgram(uiProgramFlat);
		//send our orthographic projection info to the shader
		glUniformMatrix4fv(MatrixIDFlat, 1, GL_FALSE, (float*)&mViewProj);
	
		//if K is held down, reset all the positions and velocities to be random again
		if ( glfwGetKey(pWin, GLFW_KEY_K) == GLFW_PRESS )
		{
			for ( int i = 0 ; i < CIRCLE_COUNT; ++i )
			{		
				myCircle[i].SetPosition(Vector3(
					  rand() % (int)GetWindowDimensions().x - GetWindowDimensions().x / 2.f
					, rand() % (int)GetWindowDimensions().y - GetWindowDimensions().y / 2.f
					, 1));

				myCircle[i].SetVelocity(Vector3(rand() % 1000 - 500.f, rand() % 1000 - 500.f, 0));
			}
		}

		//loop through all the circle pairs. If they are colliding, call ApplyCollision
		for ( int i = 0 ; i < CIRCLE_COUNT; ++i )
		{
			for ( int j = i + 1 ; j < CIRCLE_COUNT ; ++j)
			{
				if (myCircle[i].IsColliding(&myCircle[j]))
				{
					myCircle[i].ApplyCollision(&myCircle[j]);
				}
			}
		}
		
		//Update and render the circles
		for ( int i = 0 ; i < CIRCLE_COUNT; ++i )
		{
			myCircle[i].Update(dt);
			myCircle[i].Draw(uiProgramFlat);
		}

		// Swap front and back rendering buffers
		glfwSwapBuffers( pWin );
		glfwPollEvents();
		
	}
}

GLFWwindow* GetWindowPtr()
{
	return pWin;
}

Vector2 GetWindowDimensions()
{
	return Vector2((float)iScreenWidth, (float)iScreenHeight);
}

Vector3 GetMousePos()
{
	double mx, my;
	glfwGetCursorPos(pWin, &mx, &my);
	my = (GetWindowDimensions().y - my) - (GetWindowDimensions().y / 2.f);
	mx -= (GetWindowDimensions().x / 2.f);
	return Vector3((float)mx, (float)my, 0);
}

bool Setup()
{
	Timer::Get()->UpdateTimer();
	if( !glfwInit() )
	{
		return false;
	}
	// Open an OpenGL window
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasingGLFW_OPENGL_DEBUG_CONTEXT 

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 4);

	pWin = glfwCreateWindow( iScreenWidth, iScreenHeight, "Hello World", 0, 0 );
	
	glfwMakeContextCurrent(pWin);
	// Open a window and create its OpenGL context
	if( !pWin )
	{
		glfwTerminate();
		return false;
	}
	
	// Initialize GLEW
	GLenum glewRes = glewInit();
	if (glewRes != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return false;
	}
	
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	
	return true;

}
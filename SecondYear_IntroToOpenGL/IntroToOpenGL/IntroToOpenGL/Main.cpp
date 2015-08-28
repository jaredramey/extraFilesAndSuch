#include <iostream>
#include <gl_core_4_4.h>
#include <glfw3.h>
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

int main()
{
	//initialize glfw
	if (glfwInit() == false)
		return -1;

	//create the window
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	//make the window the current context
	glfwMakeContextCurrent(window);

	//load functions
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	//display version to console window
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();

	printf("GL: %i,%i\n", major, minor);

	//starting gizmos
	Gizmos::create();

	vec3 LookX = vec3(10, 10, 10);
	vec3 LookY = vec3(0, 0, 0);
	vec3 LookZ = vec3(0, 1, 0);

	mat4 view = glm::lookAt(LookX, LookY, LookZ);
	mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);

	//Clear color buffer
	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST);

	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		//glClear before any other call
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Game logic and update code goes here
		//Gizmos update
		Gizmos::clear();
		//so does render code

		//Movement Controls
		if (glfwGetKey(window, GLFW_KEY_W) ==  GLFW_PRESS)
		{
			
		}


		//Gizmos code from tutorial
		Gizmos::addTransform(glm::mat4(1));

		//Adding a sphere for the sun
		Gizmos::addSphere(vec3(0.0f, 0.0f, 0.0f), 1.5f, 10, 10, vec4(1.f, 0.59f, 0.0f, 1.f));
		//Sphere for Mercury
		Gizmos::addSphere(vec3(2.7f, 0.0f, 0.0f), 0.5f, 10, 10, vec4(1.f, 0.0f, 0.0f, 1.f));
		//Sphere for venus
		Gizmos::addSphere(vec3(3.7f, 0.0f, 3.0f), 0.4f, 10, 10, vec4(0.9f, 0.5f, 0.8f, 1.f));

		vec4 white(1);
		vec4 black(0, 0, 0, 1);

		for (int i = 0; i < 21; i++)
		{
			Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);
			Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
		}

		Gizmos::draw(projection * view);

		//shut down the window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//shut down everything
	Gizmos::destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
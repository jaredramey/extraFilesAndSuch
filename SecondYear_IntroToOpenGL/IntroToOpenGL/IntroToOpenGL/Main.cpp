#include <iostream>
#include <gl_core_4_4.h>
#include <glfw3.h>
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Planet.h"

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
	glClearColor(0.f, 0.f, 0.f, 1);
	glEnable(GL_DEPTH_TEST);

	//Init planets
	Planet Sun = Planet(vec3(), 2.f, 10, 10, vec4(0.9f, 0.5f, 0.0f, 1.f));
	Planet Mercury = Planet(vec3(), 0.25f, 10, 10, vec4(0.9f, 0.7f, 0.7f, 1.f));
	Planet venus = Planet(vec3(), 0.3f, 10, 10, vec4(0.61f, 0.0f, 0.f, 1.f));
	Planet Earth = Planet(vec3(), 0.3f, 10, 10, vec4(0.61, 0.0f, 0.0f, 1.0f));
	Planet Moon = Planet(vec3(), 0.9f, 10, 10, vec4());
	Planet Mars = Planet(vec3(), 0.28f, 10, 10, vec4());
	Planet Jupiter = Planet(vec3(), 0.8f, 10, 10, vec4());
	Planet Saturn = Planet(vec3(), 0.6f, 10, 10, vec4());
	Planet Uranus = Planet(vec3(), 0.5f, 10, 10, vec4());
	Planet Neptune = Planet(vec3(), 0.4f, 10, 10, vec4());

	//Getting ready for currentTime
	float currentTime = 0;

	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		//glClear before any other call
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Game logic and update code goes here
		//Gizmos update
		Gizmos::clear();
		currentTime = glfwGetTime();
		//so does render code

		//Rotation for planets
		mat4 S_T = (glm::translate(Sun.Position)			 //orbitee
			//* glm::rotate(currentTime, vec3(0, 0, 1))	 //orbiting
			* glm::translate(vec3(0, 0, 0))				 //orbital offset
			//* glm::rotate(currentTime*1.f, vec3(0, 1, 1))//
			* glm::rotate(currentTime, vec3(0, 1, .2)));	 //spin
			//* glm::scale(vec3(1, .8, 1));				 //squish

		mat4 M_T = (glm::translate(Mercury.Position)			 //orbitee
			* glm::rotate(currentTime, vec3(0, 0, 1))	 //orbiting
			* glm::translate(vec3(0, 0, 2.5f))				 //orbital offset
			* glm::rotate(currentTime*1.f, vec3(0, 1, 1))//
			* glm::rotate(currentTime, vec3(0, 1, .2))	 //spin
			* glm::scale(vec3(1, .9, 1)));				 //squish

		mat4 V_T = glm::translate(venus.Position)			 //orbitee
			* glm::rotate(currentTime, vec3(0, 0, 1))	 //orbiting
			* glm::translate(vec3(0, 0, 3.5f))				 //orbital offset
			* glm::rotate(currentTime*1.f, vec3(0, 1, 1))//
			* glm::rotate(currentTime, vec3(0, 1, .2))	 //spin
			* glm::scale(vec3(1, .9, 1));				 //squish

		mat4 E_T = glm::translate(Earth.Position)			 //orbitee
			* glm::rotate(currentTime, vec3(0, 0, 1))	 //orbiting
			* glm::translate(vec3(0, 0, 4.5f))				 //orbital offset
			* glm::rotate(currentTime*1.f, vec3(0, 1, 1))//
			* glm::rotate(currentTime, vec3(0, 1, .2))	 //spin
			* glm::scale(vec3(1, .9, 1));

		mat4 Mo_T = glm::translate(Moon.Position)			 //orbitee
			* glm::rotate(currentTime, Earth.Position)	 //orbiting
			* glm::translate(vec3(0, 0, 1.f))				 //orbital offset
			* glm::rotate(currentTime*1.f, vec3(0, 1, 1))//
			* glm::rotate(currentTime, vec3(0, 1, .2))	 //spin
			* glm::scale(vec3(1, .9, 1));

		mat4 Ma_T = glm::translate(Mars.Position)			 //orbitee
			* glm::rotate(currentTime, vec3(0, 0, 1))	 //orbiting
			* glm::translate(vec3(0, 0, 5.5f))				 //orbital offset
			* glm::rotate(currentTime*1.f, vec3(0, 1, 1))//
			* glm::rotate(currentTime, vec3(0, 1, .2))	 //spin
			* glm::scale(vec3(1, .9, 1));

		mat4 J_T = glm::translate(Jupiter.Position)			 //orbitee
			* glm::rotate(currentTime, vec3(0, 0, 1))	 //orbiting
			* glm::translate(vec3(0, 0, 7.5f))				 //orbital offset
			* glm::rotate(currentTime*1.f, vec3(0, 1, 1))//
			* glm::rotate(currentTime, vec3(0, 1, .2))	 //spin
			* glm::scale(vec3(1, .9, 1));

		mat4 Sa_T = glm::translate(Saturn.Position)			 //orbitee
			* glm::rotate(currentTime, vec3(0, 0, 1))	 //orbiting
			* glm::translate(vec3(0, 0, 9.5f))				 //orbital offset
			* glm::rotate(currentTime*1.f, vec3(0, 1, 1))//
			* glm::rotate(currentTime, vec3(0, 1, .2))	 //spin
			* glm::scale(vec3(1, .9, 1));

		mat4 U_T = glm::translate(Uranus.Position)			 //orbitee
			* glm::rotate(currentTime, vec3(0, 0, 1))	 //orbiting
			* glm::translate(vec3(0, 0, 10.5f))				 //orbital offset
			* glm::rotate(currentTime*1.f, vec3(0, 1, 1))//
			* glm::rotate(currentTime, vec3(0, 1, .2))	 //spin
			* glm::scale(vec3(1, .9, 1));

		mat4 N_T = glm::translate(Neptune.Position)			 //orbitee
			* glm::rotate(currentTime, vec3(0, 0, 1))	 //orbiting
			* glm::translate(vec3(0, 0, 11.5f))				 //orbital offset
			* glm::rotate(currentTime*1.f, vec3(0, 1, 1))//
			* glm::rotate(currentTime, vec3(0, 1, .2))	 //spin
			* glm::scale(vec3(1, .9, 1));

		//Orbitation for planets
		mat4 sunOrb = mat4(1);

		mat4 mercOrb = sunOrb * glm::rotate(0.48f*currentTime, vec3(0, 1, 0))
			* (glm::translate(vec3(0, 0, 0.5)));

		mat4 venOrb = sunOrb * glm::rotate(0.35f*currentTime, vec3(0, 1, 0))
			* (glm::translate(vec3(0, 0, 1)));

		mat4 earOrb = sunOrb * glm::rotate(0.3f*currentTime, vec3(0, 1, 0))
			* (glm::translate(vec3(0, 0, 1.5)));

		mat4 moonOrb = sunOrb * glm::rotate(0.8f*currentTime, vec3(0, 1, 0))
			* (glm::translate(vec3(0, 0, 1.5)));

		mat4 marOrb = sunOrb * glm::rotate(0.24f*currentTime, vec3(0, 1, 0))
			* (glm::translate(vec3(0, 0, 1.5)));

		mat4 jupOrb = sunOrb * glm::rotate(0.29f*currentTime, vec3(0, 1, 0))
			* (glm::translate(vec3(0, 0, 1.5)));

		mat4 satOrb = sunOrb * glm::rotate(0.1f*currentTime, vec3(0, 1, 0))
			* (glm::translate(vec3(0, 0, 1.5)));

		mat4 uraOrb = sunOrb * glm::rotate(0.07f*currentTime, vec3(0, 1, 0))
			* (glm::translate(vec3(0, 0, 1.5)));

		mat4 nepOrb = sunOrb * glm::rotate(0.05f*currentTime, vec3(0, 1, 0))
			* (glm::translate(vec3(0, 0, 1.5)));

		//Movement Controls
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			LookY -= vec3(1, 0, 1);
			view = glm::lookAt(LookX, LookY, LookZ);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			LookY += vec3(1, 0, 1);
			view = glm::lookAt(LookX, LookY, LookZ);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			LookY += vec3(0, 1, 1);
			view = glm::lookAt(LookX, LookY, LookZ);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			LookY -= vec3(0, 1, 1);
			view = glm::lookAt(LookX, LookY, LookZ);
		}


		//Gizmos code from tutorial
		Gizmos::addTransform(glm::mat4(1));

		Sun.Update(sunOrb * S_T);
		Mercury.Update(mercOrb * M_T);
		venus.Update(venOrb * V_T);
		Earth.Update(earOrb * E_T);
		Moon.Update(moonOrb * Mo_T);
		Mars.Update(marOrb * Ma_T);
		Jupiter.Update(jupOrb * J_T);
		Saturn.Update(satOrb * Sa_T);
		Uranus.Update(uraOrb * U_T);
		Neptune.Update(nepOrb * N_T);

		//need to find a way to get jupiters newest cords as it updates
		//Gizmos::addRing(Jupiter.Position, 2.f, 10.f, 20, vec4(1.f, 1.f, 1.f, 1.f) , &(jupOrb /** J_T*/));

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


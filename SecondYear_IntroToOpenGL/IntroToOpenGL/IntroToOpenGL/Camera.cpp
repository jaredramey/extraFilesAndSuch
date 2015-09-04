#include "Camera.h"

#include <iostream>

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::update(float deltaTime, GLFWwindow* window)
{
	//// newValue = oldValue + changeInValue * dt;

	//// Pitch/yaw += DeltaMouse * DeltaTime * speed
	///*
	//deltaTime = newTime - lastTime;

	//deltaMouse = newPos - lastPos;

	//yaw   += deltaMouse.y * YawSpeed * dt 
	//pitch += deltaMouse.x * pitchSpeed * dt
	//
	//*/
	static double cX = 0, cY = 0;
	static double dX = 0, dY = 0;
	static double nX = 0, nY = 0;

	glfwGetCursorPos(window, &cX, &cY);

	dX = cX - nX;
	dY = cY - nY;
	nX = cX;
	nY = cY;


	mat4 yaw = glm::rotate(float((deltaTime/2) * dX), vec3(0,1,0));
	mat4 pitch = glm::rotate(float((deltaTime/2) * dY), vec3(worldTransform[0])); // pitch

	if (cX != 0.0f)
	{
		worldTransform[0] = pitch*worldTransform[0];
		worldTransform[1] = pitch*worldTransform[1];
		worldTransform[2] = pitch*worldTransform[2];
	}

	if (cY != 0.0f)
	{
		worldTransform[0] = yaw*worldTransform[0];
		worldTransform[1] = yaw*worldTransform[1];
		worldTransform[2] = yaw*worldTransform[2];
	}

	// float pitch,yaw,roll;
	//glm::extractEulerAngleXYZ(worldTransform,pitch,yaw,roll);

	//std::cout << pitch << " " << yaw << " " << roll << std::endl;

	//pitch += dX*deltaTime;
	//yaw += dY*deltaTime;


	//glm::vec3 forward = vec3(cos(yaw)*cos(pitch), sin(pitch), sin(yaw)*cos(pitch));
	//setLookAt(vec3(worldTransform[3]), normalize(vec3(worldTransform[3]) + forward), vec3(0, 1, 0));
	//std::cout << worldTransform[3].x << " " << worldTransform[3].y << " " << worldTransform[3].z << std::endl;

	/*
	Transformation matrix is an encoding of:
	0: right
	1: up
	2: forward
	3: position

	*/

	//Movement controls


	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // UP
	{
		//worldTransform = worldTransform*glm::translate(glm::vec3(worldTransform[1])*.16);
		worldTransform[3] += worldTransform[1] * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // DOWN
	{
		//worldTransform = worldTransform*glm::translate(glm::vec3(-(worldTransform[1]))*.16);
		worldTransform[3] -= worldTransform[1] * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // LEFT
	{
		//worldTransform = worldTransform*glm::translate(glm::vec3(-(worldTransform[0]))*.16);
		worldTransform[3] -= worldTransform[0] * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // RIGHT
	{
		//worldTransform = worldTransform*glm::translate(glm::vec3((worldTransform[0]))*.16);
		worldTransform[3] += worldTransform[0] * deltaTime;
	}
}

void Camera::setPerspective(float fieldOfView, float aspectRatio, float Near, float Far)
{
	//Nice to know that hand making this ends up being pointless
	/*
	float n = Near;
	float f = Far;
	float S = 1/(n*tan(fieldOfView/2));
	float a = aspectRatio;

	glm::mat4 finalProjectionMatrix = 
	{a*S, 0, 0, 0,
		0, S, 0, 0,
		0, 0, (-((f+n)/(f-n))), (-(2*(f*n)/(f-n))),
		0, 0, -1, 0
	};

	projectionTransform = finalProjectionMatrix;*/
	//Since GLM already does it for you
	projectionTransform = glm::perspective(fieldOfView, aspectRatio, Near, Far);
}

void Camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
	worldTransform = glm::inverse(glm::lookAt(from, to, up));
}


void Camera::setPosition(glm::vec3 position)
{
	worldTransform[3] = vec4(position,1);
}

glm::mat4 Camera::GetWorldTransform()
{
	return worldTransform;
}

glm::mat4 Camera::GetView()
{
	return glm::inverse(worldTransform);
}

glm::mat4 Camera::GetProjection()
{
	return projectionTransform;
}

void Camera::UpdateProjectionViewTransform()
{
	projectionTransform = projectionTransform * worldTransform;
}
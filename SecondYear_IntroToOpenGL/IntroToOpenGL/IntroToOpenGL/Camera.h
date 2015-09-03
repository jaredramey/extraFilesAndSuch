#pragma once
#include <iostream>
#include <gl_core_4_4.h>
#include <glfw3.h>
#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

class Camera
{
	glm::mat4 worldTransform;
	glm::mat4 viewTransform;
	glm::mat4 projectionTransform;
	glm::mat4 projectionViewTransform;

public:
	Camera();
	~Camera();

	void update(float deltaTime);
	void setPerspective(float fieldOfView, float aspectRatio, float near, float far);
	void setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void setPosition(glm::vec3 position);
	glm::mat4 GetWorldTransform();
	glm::mat4 GetView();
	glm::mat4 GetProjection();
	void UpdateProjectionViewTransform();

};


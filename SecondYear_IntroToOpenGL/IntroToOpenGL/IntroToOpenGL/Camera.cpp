#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}


void Camera::update(float deltaTime)
{

}
void Camera::setPerspective(float fieldOfView, float aspectRatio, float near, float far)
{

}
void Camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{

}
void Camera::setPosition(glm::vec3 position)
{

}
glm::mat4 Camera::GetWorldTransform()
{
	return worldTransform;
}
glm::mat4 Camera::GetView()
{
	return viewTransform;
}
glm::mat4 Camera::GetProjection()
{
	return projectionTransform;
}
void Camera::UpdateProjectionViewTransform()
{

}
#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <GLFW\glfw3.h>
#include <Vector2.h>

GLFWwindow* GetWindowPtr();

Vector2 GetWindowDimensions();

Vector3 GetMousePos();

#endif //_WINDOW_H_
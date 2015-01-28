#ifndef _SHADERS_H_
#define _SHADERS_H_

#include <GL/glew.h>

GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile);
GLuint CreateProgram(const char *a_vertex, const char *a_frag);

#endif //_SHADERS_H_


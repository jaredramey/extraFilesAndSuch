#include <glew.h>
#include <wglew.h>
#include <glfw3.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Entity.h"
#include "Player.h"
#include "SOIL.h"

//Function Prototypes
GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile);
GLuint CreateProgram(const char *a_vertex, const char *a_frag);
float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);
unsigned int loadTexture(const char* a_pFileName, int & a_iWidth, int & a_iHeight, int a_iBPP);

Entity create;

int main()
{

	//Initialise GLFW
	if (!glfwInit())
	{
		return -1;
	}

	//create a windowed mode window and it's OpenGL context
	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}


	//make the window's context current
	glfwMakeContextCurrent(window);

	//Initialize Glew
	if (glewInit() != GLEW_OK)
	{
		// OpenGL didn't start-up! shutdown GLFW and return an error code
		glfwTerminate();
		return -1;
	}

	//Testing player class possibilities
	Entity::TriangleVertex* PlayerShape = new Entity::TriangleVertex[3];
	PlayerShape[0].fPositions[0] = 1024 / 2.0;
	PlayerShape[0].fPositions[1] = 720 / 2.0 + 100.0f;
	PlayerShape[1].fPositions[0] = 1024 / 2.0 - 100.0f;
	PlayerShape[1].fPositions[1] = 720 / 2.0 - 100.0f;
	PlayerShape[2].fPositions[0] = 1024 / 2.0 + 100.0f;
	PlayerShape[2].fPositions[1] = 720 / 2.0 - 100.0f;
	for (int i = 0; i < 3; i++)
	{
		PlayerShape[i].fPositions[2] = 0.0f;
		PlayerShape[i].fPositions[3] = 1.0f;
		//Add Color
		PlayerShape[i].fColours[0] = 1.0f;
		PlayerShape[i].fColours[1] = 1.0f;
		PlayerShape[i].fColours[2] = 0.0f;
		PlayerShape[i].fColours[3] = 0.0f;
		//Set up the UVs
		PlayerShape[0].fUVs[0] = 0.5f; //<-- Top of triangle
		PlayerShape[0].fUVs[1] = 1.0f;
		PlayerShape[1].fUVs[0] = 0.0f; //<-- Bottom Left
		PlayerShape[1].fUVs[1] = 0.0f;
		PlayerShape[2].fUVs[0] = 1.0f; //<-- Bottom Right
		PlayerShape[2].fUVs[1] = 0.0f;
	}
	// \/\/\/\/ Just for the rainbow effect \/\/\/\/
	//Top point color
	PlayerShape[0].fColours[0] = 1.0f;
	PlayerShape[0].fColours[1] = 0.0f;
	PlayerShape[0].fColours[2] = 0.0f;
	PlayerShape[0].fColours[3] = 1.0f;
	//Bottom Left color
	PlayerShape[1].fColours[0] = 0.0f;
	PlayerShape[1].fColours[1] = 1.0f;
	PlayerShape[1].fColours[2] = 0.0f;
	PlayerShape[1].fColours[3] = 1.0f;
	//Bottom Right color
	PlayerShape[2].fColours[0] = 0.0f;
	PlayerShape[2].fColours[1] = 0.0f;
	PlayerShape[2].fColours[2] = 1.0f;
	PlayerShape[2].fColours[3] = 1.0f;

	//create ID for a vertex buffer object
	GLuint uiVBO;
	glGenBuffers(1, &uiVBO);

	//check it succeeded
	if (uiVBO != 0)
	{
		//bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
		//allocate space for vertices on the graphics card
		glBufferData(GL_ARRAY_BUFFER, sizeof(Entity::TriangleVertex)* 3, NULL, GL_STATIC_DRAW);
		//get pointer to allocated space on the graphics card
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		//copy data to graphics card
		memcpy(vBuffer, PlayerShape, sizeof(Entity::TriangleVertex) * 3);
		//unmap and unbind buffer
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//create ID for an index buffer object
	GLuint uiIBO;
	glGenBuffers(1, &uiIBO);

	if (uiIBO != 0)
	{
		//bind IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);
		//allocate space for verticies on the graphics card
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*sizeof(char), NULL, GL_STATIC_DRAW);
		//get pointer to allocated space on the graphics card
		GLvoid* iBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		//specify the order we'd like to draw our verticies
		//In this case, they are in sequintial order
		for (int i = 0; i < 3; i++)
		{
			((char*)iBuffer)[i] = i;
		}
		//unmap and unbind buffer
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	//create TextureID
	int width = 50, height = 50, bpp = 4;
	GLuint uiTextureID = loadTexture("myTexture.jpg", width, height, bpp);

	//create shader program
	GLuint uiProgramFlat = CreateProgram("VertexShader.glsl", "FlatFragmentShader.glsl");

	GLuint uiProgramTextured = CreateProgram("VertexShader.glsl" , "TexturedFragmentShader.glsl");

	//find the position of the matrix var in the shader so we can send info there later
	GLuint MatrixIDFlat = glGetUniformLocation(uiProgramFlat, "MVP");

	//set up the mapping of the screen to pixel co-ordinates. Try changing values and see what happens
	float *orthographicProjection = getOrtho(0, 1080, 0, 720, 0, 180); 

	//loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//send orthographic projection info to shader
		glUniformMatrix4fv(MatrixIDFlat, 1, GL_FALSE, orthographicProjection);

		//enable shaders
		//glUseProgram(uiProgramFlat);
		glUseProgram(uiProgramTextured);

		//Playing with movement
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			//move forward
			for (int i = 0; i < 3; i++)
			{

			}
		}

		//enable the vertex array states
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//bind Texture
		glBindTexture(GL_TEXTURE_2D, uiTextureID);
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Entity::TriangleVertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Entity::TriangleVertex), (void*)(sizeof(float)*4));
		//now to worry about the UVs and send that info to the graphics card as well
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Entity::TriangleVertex), (void*)(sizeof(float)*8));

		//Draw to screen
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);


		//swap front and back buffers
		glfwSwapBuffers(window);

		//poll for and process events
		glfwPollEvents();
	}

	//delete the index buffer to free up allocated memory
	glDeleteBuffers(1, &uiIBO);

	glfwTerminate();
	return 0;
}


//Functions
GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile)
{
	std::string strShaderCode;
	//open shader file
	std::ifstream shaderStream(a_strShaderFile);
	//if that worked ok, load file line by line
	if (shaderStream.is_open())
	{
		std::string Line = "";
		while (std::getline(shaderStream, Line))
		{
			strShaderCode += "\n" + Line;
		}
		shaderStream.close();
	}

	//convert to cstring
	char const *szShaderSourcePointer = strShaderCode.c_str();

	//create shader ID
	GLuint uiShader = glCreateShader(a_eShaderType);
	//load source code
	glShaderSource(uiShader, 1, &szShaderSourcePointer, NULL);

	//compile shader
	glCompileShader(uiShader);

	//check for compilation errors and output them
	GLint iStatus;
	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iStatus);
	if (iStatus == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(uiShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(uiShader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch (a_eShaderType)
		{
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}

	return uiShader;
}

GLuint CreateProgram(const char *a_vertex, const char *a_frag)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(CreateShader(GL_VERTEX_SHADER, a_vertex));
	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, a_frag));

	//create shader program ID
	GLuint uiProgram = glCreateProgram();

	//attach shaders
	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
		glAttachShader(uiProgram, *shader);

	//link program
	glLinkProgram(uiProgram);

	//check for link errors and output them
	GLint status;
	glGetProgramiv(uiProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(uiProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(uiProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
	{
		glDetachShader(uiProgram, *shader);
		glDeleteShader(*shader);
	}

	return uiProgram;
}

float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar)
{
	//to correspond with mat4 in the shader
	//ideally this function would be part of your matrix class
	//however I wasn't willing to write your matrix class for you just to show you this
	//so here we are in array format!
	//add this to your matrix class as a challenge if you like!
	float* toReturn = new float[12];
	toReturn[0] = 2.0 / (right - left);;
	toReturn[1] = toReturn[2] = toReturn[3] = toReturn[4] = 0;
	toReturn[5] = 2.0 / (top - bottom);
	toReturn[6] = toReturn[7] = toReturn[8] = toReturn[9] = 0;
	toReturn[10] = 2.0 / (a_fFar - a_fNear);
	toReturn[11] = 0;
	toReturn[12] = -1 * ((right + left) / (right - left));
	toReturn[13] = -1 * ((top + bottom) / (top - bottom));
	toReturn[14] = -1 * ((a_fFar + a_fNear) / (a_fFar - a_fNear));
	toReturn[15] = 1;
	return toReturn;
}


unsigned int loadTexture(const char* a_pFileName, int & a_iWidth, int & a_iHeight, int a_iBPP)
{
	unsigned int uiTextureID = 0;
	//check if the file exists
	if (a_pFileName != nullptr)
	{
		//read in image data from file
		unsigned char* pImageData = SOIL_load_image(a_pFileName, &a_iWidth, &a_iHeight, &a_iBPP, SOIL_LOAD_AUTO);

		//check for a successful read
		if (pImageData)
		{
			//create openGL texture handle
			uiTextureID = SOIL_create_OGL_texture(pImageData, a_iWidth, a_iHeight, a_iBPP, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS| SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

			//clear what was read in from file now that it's stored in the handle
			SOIL_free_image_data(pImageData);
		}

		//check for errors
		if (uiTextureID == 0)
		{
			std::cerr << "SOIL loading error: " << SOIL_last_result() << std::endl;
		}
		return uiTextureID;
	}
}
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
	window = glfwCreateWindow(1024, 720, "Hello World", NULL, NULL);
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

	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

	Entity::QuadVertex* PlayerShape = new Entity::QuadVertex[4];
	PlayerShape[0].fPositions[0] = 1024 / 2.0 - 100.0f;
	PlayerShape[0].fPositions[1] = 720 / 2.0;
	PlayerShape[1].fPositions[0] = 1024 / 2.0 - 100.0f;
	PlayerShape[1].fPositions[1] = 720 / 2.0 - 100.0f;
	PlayerShape[2].fPositions[0] = 1024 / 2.0 + 100.0f;
	PlayerShape[2].fPositions[1] = 720 / 2.0 - 100.0f;
	PlayerShape[3].fPositions[0] = 1024 / 2.0 + 100.0f;
	PlayerShape[3].fPositions[1] = 720 / 2.0;
	for (int i = 0; i < 4; i++)
	{
		PlayerShape[i].fPositions[2] = 0.0f;
		PlayerShape[i].fPositions[3] = 1.0f;
		//Set up the UVs
		PlayerShape[0].fUVs[0] = 0.0f; //<-- Top Left
		PlayerShape[0].fUVs[1] = 1.0f;
		PlayerShape[1].fUVs[0] = 0.0f; //<-- Bottom Left
		PlayerShape[1].fUVs[1] = 0.0f;
		PlayerShape[2].fUVs[0] = 1.0f; //<-- Bottom Right
		PlayerShape[2].fUVs[1] = 0.0f;
		PlayerShape[3].fUVs[0] = 1.0f; //<-- Top Right
		PlayerShape[3].fUVs[1] = 1.0f;
	}
	// \/\/\/\/ Just for the rainbow effect \/\/\/\/
	//Top point color
	PlayerShape[0].fColours[0] = 1.0f;
	PlayerShape[0].fColours[1] = 1.0f;
	PlayerShape[0].fColours[2] = 1.0f;
	PlayerShape[0].fColours[3] = 0.0f;
	//Bottom Left color
	PlayerShape[1].fColours[0] = 1.0f;
	PlayerShape[1].fColours[1] = 1.0f;
	PlayerShape[1].fColours[2] = 1.0f;
	PlayerShape[1].fColours[3] = 1.0f;
	//Bottom Right color
	PlayerShape[2].fColours[0] = 1.0f;
	PlayerShape[2].fColours[1] = 1.0f;
	PlayerShape[2].fColours[2] = 1.0f;
	PlayerShape[2].fColours[3] = 1.0f;
	//Top Right color
	PlayerShape[3].fColours[0] = 1.0f;
	PlayerShape[3].fColours[1] = 1.0f;
	PlayerShape[3].fColours[2] = 1.0f;
	PlayerShape[3].fColours[3] = 1.0f;

	Entity::QuadVertex* OtherShape = new Entity::QuadVertex[4];
	OtherShape[0].fPositions[0] = 1024 / 2.0 - 100.0f;
	OtherShape[0].fPositions[1] = 720 / 2.0;
	OtherShape[1].fPositions[0] = 1024 / 2.0 - 100.0f;
	OtherShape[1].fPositions[1] = 720 / 2.0 - 100.0f;
	OtherShape[2].fPositions[0] = 1024 / 2.0 + 100.0f;
	OtherShape[2].fPositions[1] = 720 / 2.0 - 100.0f;
	OtherShape[3].fPositions[0] = 1024 / 2.0 + 100.0f;
	OtherShape[3].fPositions[1] = 720 / 2.0;
	for (int i = 0; i < 4; i++)
	{
		OtherShape[i].fPositions[2] = 0.0f;
		OtherShape[i].fPositions[3] = 1.0f;
		//Set up the UVs
		OtherShape[0].fUVs[0] = 0.0f; //<-- Top Left
		OtherShape[0].fUVs[1] = 1.0f;
		OtherShape[1].fUVs[0] = 0.0f; //<-- Bottom Left
		OtherShape[1].fUVs[1] = 0.0f;
		OtherShape[2].fUVs[0] = 1.0f; //<-- Bottom Right
		OtherShape[2].fUVs[1] = 0.0f;
		OtherShape[3].fUVs[0] = 1.0f; //<-- Top Right
		OtherShape[3].fUVs[1] = 1.0f;
	}
	// \/\/\/\/ Just for the rainbow effect \/\/\/\/
	//Top point color
	OtherShape[0].fColours[0] = 1.0f;
	OtherShape[0].fColours[1] = 1.0f;
	OtherShape[0].fColours[2] = 1.0f;
	OtherShape[0].fColours[3] = 0.0f;
	//Bottom Left color
	OtherShape[1].fColours[0] = 1.0f;
	OtherShape[1].fColours[1] = 1.0f;
	OtherShape[1].fColours[2] = 1.0f;
	OtherShape[1].fColours[3] = 1.0f;
	//Bottom Right color
	OtherShape[2].fColours[0] = 1.0f;
	OtherShape[2].fColours[1] = 1.0f;
	OtherShape[2].fColours[2] = 1.0f;
	OtherShape[2].fColours[3] = 1.0f;
	//Top Right color
	OtherShape[3].fColours[0] = 1.0f;
	OtherShape[3].fColours[1] = 1.0f;
	OtherShape[3].fColours[2] = 1.0f;
	OtherShape[3].fColours[3] = 1.0f;

	//create ID for a vertex buffer object
	GLuint uiVBO;
	glGenBuffers(1, &uiVBO);

	//check it succeeded
	if (uiVBO != 0)
	{
		//bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
		//allocate space for vertices on the graphics card
		glBufferData(GL_ARRAY_BUFFER, sizeof(Entity::QuadVertex)* 4, NULL, GL_STATIC_DRAW);
		//get pointer to allocated space on the graphics card
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		//copy data to graphics card
		memcpy(vBuffer, PlayerShape, sizeof(Entity::QuadVertex) * 4);
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
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(char), NULL, GL_STATIC_DRAW);
		//get pointer to allocated space on the graphics card
		GLvoid* iBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		//specify the order we'd like to draw our verticies
		//In this case, they are in sequintial order
		for (int i = 0; i < 4; i++)
		{
			((char*)iBuffer)[i] = i;
		}
		//unmap and unbind buffer
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


	const char* myTexture = "frame-1.png";

	//create TextureID
	int width = 927, height = 633, bpp = 4;
	GLuint uiTextureID = loadTexture(myTexture, width, height, bpp);
	GLuint uiTextureID2 = loadTexture("frame-2.png", width, height, bpp);
	GLuint uiTextureID3 = loadTexture("frame-3.png", width, height, bpp);
	GLuint uiTextureID4 = loadTexture("frame-4.png", width, height, bpp);
	GLuint uiTextureID5 = loadTexture("frame-5.png", width, height, bpp);
	GLuint uiTextureID6 = loadTexture("frame-6.png", width, height, bpp);
	GLuint uiTextureID7 = loadTexture("frame-7.png", width, height, bpp);
	GLuint uiTextureID8 = loadTexture("frame-8.png", width, height, bpp);

	glEnable(GL_BLEND);
	

	//attempting to make a clock
	float timer = 1.0;
	bool isMoving = false;

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
		system("CLS");

		//send orthographic projection info to shader
		glUniformMatrix4fv(MatrixIDFlat, 1, GL_FALSE, orthographicProjection);

		//glUseProgram(uiProgramFlat);
		glUseProgram(uiProgramTextured);

		//Playing with movement
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			//move forward
			for (int i = 0; i < 4; i++)
			{
				PlayerShape[i].fPositions[1] += 10.0f;
			}
			glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
			GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			//copy data to graphics card
			memcpy(vBuffer, PlayerShape, sizeof(Entity::QuadVertex)*4);
			//unmap and unbind buffer
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			isMoving = true;
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			//move back
			for (int i = 0; i < 4; i++)
			{
				PlayerShape[i].fPositions[1] -= 10.0f;
			}
			glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
			GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			//copy data to graphics card
			memcpy(vBuffer, PlayerShape, sizeof(Entity::QuadVertex) * 4);
			//unmap and unbind buffer
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			isMoving = true;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			//move left
			for (int i = 0; i < 4; i++)
			{
				PlayerShape[i].fPositions[0] -= 10.0f;
			}
			glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
			GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			//copy data to graphics card
			memcpy(vBuffer, PlayerShape, sizeof(Entity::QuadVertex) * 4);
			//unmap and unbind buffer
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			isMoving = true;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			//move right
			for (int i = 0; i < 4; i++)
			{
				PlayerShape[i].fPositions[0] += 10.0f;
			}
			glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
			GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			//copy data to graphics card
			memcpy(vBuffer, PlayerShape, sizeof(Entity::QuadVertex) * 4);
			//unmap and unbind buffer
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			isMoving = true;
		}
		else
		{
			isMoving = false;
		}

		//blend stuff
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
		}

		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		}

		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		{
			glBlendFunc(GL_SRC_ALPHA, GL_DST_COLOR);
		}

		//enable the vertex array states
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);
		glEnableVertexAttribArray(5);

		//bind Texture
		//fleshing out the clock
		if (timer == 1 || timer == 2 || timer == 3 || timer == 4)
		{
			glBindTexture(GL_TEXTURE_2D, uiTextureID);
		}

		else if (timer == 5 || timer == 6 || timer == 7 || timer == 8)
		{
			glBindTexture(GL_TEXTURE_2D, uiTextureID2);
		}

		else if (timer == 9 || timer == 10 || timer == 11 || timer == 12)
		{
			glBindTexture(GL_TEXTURE_2D, uiTextureID3);
		}

		else if (timer == 13 || timer == 14 || timer == 15 || timer == 16)
		{
			glBindTexture(GL_TEXTURE_2D, uiTextureID4);
			if (isMoving == false)
				timer = 0;
		}

		else if (timer == 17 || timer == 18 || timer == 19 || timer == 20)
		{
			if (isMoving == true)
			glBindTexture(GL_TEXTURE_2D, uiTextureID5);
			if (isMoving == false)
				timer = 0;
		}

		else if (timer == 21 || timer == 22 || timer == 23 || timer == 24)
		{
			if (isMoving == true)
			glBindTexture(GL_TEXTURE_2D, uiTextureID6);
			if (isMoving == false)
				timer = 0;
		}

		else if (timer == 25 || timer == 26 || timer == 27 || timer == 28)
		{
			if (isMoving == true)
			glBindTexture(GL_TEXTURE_2D, uiTextureID7);
			if (isMoving == false)
				timer = 0;
		}

		else if (timer == 29 || timer == 30 || timer == 31 || timer == 32)
		{
			if (isMoving == true)
			{
				glBindTexture(GL_TEXTURE_2D, uiTextureID8);
			}
				timer = 0;
		}

		//glBindTexture(GL_TEXTURE_2D, uiTextureID);
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Entity::QuadVertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Entity::QuadVertex), (void*)(sizeof(float)* 4));
		//now to worry about the UVs and send that info to the graphics card as well
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Entity::QuadVertex), (void*)(sizeof(float)* 8));


		//Draw to screen
		glDrawElements(GL_QUADS, 8, GL_UNSIGNED_BYTE, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

			timer += 1;

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

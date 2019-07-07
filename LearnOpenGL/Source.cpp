//always make sure to include glad before glfw
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

void initGLFW()
{
	if (!glfwInit())
		exit(-1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//if we press the escape key set the 'should close' to true so the window will close
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//if it's not pressed, it returns GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
}

//Function for reading a shader file given the path

static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ") : " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}
int main()
{
	
	//make sure that we're using version 3 fir both minor and major
	initGLFW();

	//Generate the Window Object
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);//we should make this directly after creating the window
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//initialize GLAD before any OpenGL call but 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	glViewport(0, 0, 800, 600);//parameters : x,y for the lower left corner of the window, last 2 are width and height

	/*
	*Note that processed coordinates in OpenGL are between -1 and 1 
	*so we effectively map from the range (-1 to 1) to (0, 800) and (0, 600). 
	*/

	//register so the function so that it gets called everytime we resize the window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	//test
	//defining a buffer using modern OpenGL
	//use docs.gl for reference
	float positions[] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		0.5f, -0.5f
	};
	unsigned int buffer;//to store the buffer id
	glGenBuffers(1, &buffer);//generate 1 buffer and store its ID in variable 'buffer'
	glBindBuffer(GL_ARRAY_BUFFER, buffer);//bind buffer => select buffer, also the target is an array buffer and its id is stored in 'buffer'
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//Important : count is number of 'vertices' (pairs)
		glDrawArrays(GL_TRIANGLES, 0, 3);//we use it because we don't have index buffer yet

		while (GLenum error = glGetError())
		{
			std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
			return -1;
		}
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	return 0;
}
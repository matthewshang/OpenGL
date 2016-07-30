#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include <iostream>

#include "Shader.h"
#include "Mat4.h"
#include "Vec3.h"
#include "Quaternion.h"
#include "MathUtils.h"

GLfloat mixValue = 0.5f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		mixValue += 0.05f;
		if (mixValue >= 1.0f)
		{
			mixValue = 1.0f;
		}
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		mixValue -= 0.05f;
		if (mixValue <= 0.0f)
		{
			mixValue = 0.0f;
		}
	}
}

void run(GLFWwindow* window)
{
	Shader shader("res/vertex_shader.vert", "res/fragment_shader.frag");

	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.5f, 1.0f, 1.0f,
		 0.5f,  0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

		-0.5f,  0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	 	 0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
	};

	Vec3 cubes[] = {
		Vec3(0.0f, 0.0f, 0.0f),
		Vec3(2.0f, 5.0f, -15.0f),
		Vec3(-1.5f, -2.2f, -2.5f),
		Vec3(-3.8f, -2.0f, -12.3f),
		Vec3(2.4f, -0.4f, -3.5f),
		Vec3(-1.7f, 3.0f, -7.5f),
		Vec3(1.3f, -2.0f, -2.5f),
		Vec3(1.5f, 2.0f, -2.5f),
		Vec3(1.5f, 0.2f, -1.5f),
		Vec3(-1.3f, 1.0f, -1.5f)
	};

	//GLfloat vertices[] = {
	//	 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
	//	 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
	//	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
	//	-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f
	//};

	//GLfloat vertices[] = {
	//	-0.5f, -0.5f, 0.0f,
	//	 0.5f, -0.5f, 0.0f,
	//	 0.0f,  0.5f, 0.0f
	//}

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	//GLfloat texCoords[] = {
	//	0.0f, 0.0f,
	//	1.0f, 0.0f,
	//	0.5f, 1.0f
	//};

	int width, height;
	unsigned char* image = SOIL_load_image("res/container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	image = SOIL_load_image("res/awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
	GLuint texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint EBO;
	glGenBuffers(1, &EBO);

	GLuint VBO;
	glGenBuffers(1, &VBO);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	GLint ourMixLocation = glGetUniformLocation(shader.getProgram(), "ourMix");
	GLuint transformLocation = glGetUniformLocation(shader.getProgram(), "transform");
	GLint modelLoc = glGetUniformLocation(shader.getProgram(), "model");
	GLint viewLoc = glGetUniformLocation(shader.getProgram(), "view");
	GLint projLoc = glGetUniformLocation(shader.getProgram(), "projection");

	Mat4 view = Mat4::translate(Vec3(0.0f, 0.0f, -3.0f));
	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	Mat4 projection = Mat4::perspective(45.0f, (float) windowWidth / (float) windowHeight, 0.1f, 100.0f);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

		glUniformMatrix4fv(viewLoc, 1, GL_TRUE, view.getInternal());
		glUniformMatrix4fv(projLoc, 1, GL_TRUE, projection.getInternal());

		GLfloat time = glfwGetTime();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(shader.getProgram(), "ourTexture"), 0);
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(shader.getProgram(), "ourTexture2"), 1);

		GLfloat mix = sin(2 * time) / 2 + 0.5;
		glUniform1f(ourMixLocation, mixValue);

		glBindVertexArray(VAO);
		for (int i = 0; i < 10; i++)
		{
			Mat4 model = Mat4::translate(cubes[i]) *
				         Mat4::rotate(Quaternion::fromAxisAngle(Vec3(0.5f, 1.0f, 0.0f), MathUtils::toRadians(((GLfloat) glfwGetTime() + 1000.0f) * (40.0f + (float) i))));
			glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model.getInternal());
			glDrawArrays(GL_TRIANGLES, 0, 36);

		}
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteTextures(1, &texture);
	glDeleteTextures(1, &texture2);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Error: failed to create GLFWwindow" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "Error: failed to initialize GLEW" << std::endl;
		return -1;
	}

	int width;
	int height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	run(window);

	glfwTerminate();
	return 0;
}
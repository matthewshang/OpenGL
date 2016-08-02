#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include <iostream>

#include "Shader.h"
#include "Mat4.h"
#include "Vec3.h"
#include "Quaternion.h"
#include "MathUtils.h"
#include "Texture.h"

Vec3 camPos(0.0f, 0.0f, 3.0f);
Vec3 camFront(0.0f, 0.0f, -1.0f);
Vec3 camUp(0.0f, 1.0f, 0.0f);
GLfloat camSpeed = 5.0f;
GLfloat sens = 0.1f;
GLfloat lastX = 500.0f;
GLfloat lastY = 375.0f;
GLfloat yaw = -90.0f;
GLfloat pitch = 0.0f;
bool firstMouse = true;
bool keys[1024];
GLfloat fov = 75.0f;
int test = 0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
	{
		keys[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		keys[key] = false;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xOff = xpos - lastX;
	GLfloat yOff = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	xOff *= sens;
	yOff *= sens;

	yaw += xOff;
	pitch += yOff;
	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	else if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	Vec3 front; 
	front.x = cos(MathUtils::toRadians(pitch)) * cos(MathUtils::toRadians(yaw));
	front.y = sin(MathUtils::toRadians(pitch));
	front.z = cos(MathUtils::toRadians(pitch)) * sin(MathUtils::toRadians(yaw));
	front.normalize();
	camFront = front;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	test += yoffset;
	std::cout << test << std::endl;
}

void updateInputs(float delta, GLFWwindow* window)
{
	float speed = camSpeed * delta;
	if (keys[GLFW_KEY_W])
	{
		camPos += camFront * speed;
	}
	if (keys[GLFW_KEY_S])
	{
		camPos -= camFront * speed;
	}
	if (keys[GLFW_KEY_A])
	{
		camPos -= camFront.cross(camUp).normalize() * speed;
	}
	if (keys[GLFW_KEY_D])
	{
		camPos += camFront.cross(camUp).normalize() * speed;
	}
	if (keys[GLFW_KEY_Q])
	{
		camPos += camUp * speed;
	}
	if (keys[GLFW_KEY_E])
	{
		camPos -= camUp * speed;
	}
	if (keys[GLFW_KEY_ESCAPE])
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
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

	Texture container("res/container.jpg");
	Texture awesomeface("res/awesomeface.png");

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

	GLuint transformLocation = glGetUniformLocation(shader.getProgram(), "transform");
	GLint modelLoc = glGetUniformLocation(shader.getProgram(), "model");
	GLint viewLoc = glGetUniformLocation(shader.getProgram(), "view");
	GLint projLoc = glGetUniformLocation(shader.getProgram(), "projection");

	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	Mat4 projection = Mat4::perspective(MathUtils::toRadians(fov), (float) windowWidth / (float) windowHeight, 0.1f, 100.0f);

	GLfloat deltaTime = 0.0f;
	GLfloat lastTime = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		glfwPollEvents();
		updateInputs(deltaTime, window);


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

		//GLfloat r = 8.0f;
		//GLfloat camX = sin(glfwGetTime()) * r;
		//GLfloat camZ = cos(glfwGetTime()) * r;
		//Mat4 view = Mat4::lookAt(camPos,
		//						 Vec3(0.0f, 0.0f, 0.0f),
		//						 Vec3(0.0f, 1.0f, 0.0f));
		Mat4 view = Mat4::lookAt(camPos, camPos + camFront, camUp);
		glUniformMatrix4fv(viewLoc, 1, GL_TRUE, view.getInternal());
		glUniformMatrix4fv(projLoc, 1, GL_TRUE, projection.getInternal());

		container.bind(0);
		awesomeface.bind(1);
		glUniform1i(glGetUniformLocation(shader.getProgram(), "ourTexture"), 0);
		glUniform1i(glGetUniformLocation(shader.getProgram(), "ourTexture2"), 1);

		glBindVertexArray(VAO);
		for (int i = 0; i < 10; i++)
		{
			Mat4 model = Mat4::translate(cubes[i]) *
				         Mat4::rotate(Quaternion::fromAxisAngle(Vec3(0.5f, 1.0f, 0.0f), MathUtils::toRadians((currentTime + 1000.0f) * (40.0f + (float) i))));
			glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model.getInternal());
			glDrawArrays(GL_TRIANGLES, 0, 36);

		}
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

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

	GLFWwindow* window = glfwCreateWindow(1000, 750, "OpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Error: failed to create GLFWwindow" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
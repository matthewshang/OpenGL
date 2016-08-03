#include <GL/glew.h>

#include <iostream>

#include "Shader.h"
#include "math/Mat4.h"
#include "math/Vec3.h"
#include "math/Quaternion.h"
#include "math/MathUtils.h"
#include "Texture.h"
#include "InputState.h"
#include "Window.h"
#include "Camera.h"

void run(Window& window)
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

	Mat4 projection = Mat4::perspective(MathUtils::toRadians(75.0f), (float) window.getWidth() / (float) window.getHeight(), 0.1f, 100.0f);
	Camera camera(Vec3(0.0f, 0.0f, 3.0f), 10.0f, 8.0f);
	GLfloat lastTime = 0.0f;

	while (!window.shouldClose())
	{
		GLfloat currentTime = window.getTime();
		GLfloat deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		window.pollEvents();
		if (window.getInputState().keyPressed(InputState::KEY_ESCAPE))
		{
			window.close();
		}

		camera.update(deltaTime, window.getInputState());

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

		//GLfloat r = 8.0f;
		//GLfloat camX = sin(window.getTime()) * r;
		//GLfloat camZ = cos(window.getTime()) * r;
		//Mat4 view = Mat4::lookAt(Vec3(camX, 0.0f, camZ),
		//						 Vec3(0.0f, 0.0f, 0.0f),
		//						 Vec3(0.0f, 1.0f, 0.0f));
		Mat4 view = camera.getViewMatrix();
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

		window.swapBuffers();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

int main()
{
	Window window(1000, 750, "OpenGL");

	int width;
	int height;
	window.getFramebufferSize(width, height);
	glViewport(0, 0, width, height);

	run(window);

	return 0;
}
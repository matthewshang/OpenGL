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
	//GLfloat vertices[] = {
	//	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	//	 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	//	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
	//	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
	//	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

	//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	//	 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	//	 0.5f,  0.5f, 0.5f, 1.0f, 1.0f,
	//	 0.5f,  0.5f, 0.5f, 1.0f, 1.0f,
	//	-0.5f,  0.5f, 0.5f, 0.0f, 1.0f,
	//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

	//	-0.5f,  0.5f, 0.5f, 1.0f, 0.0f,
	//	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	//	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

	//	 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	//	 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	//	 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	//	 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	// 	 0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	//	 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

	//	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	//	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	//	 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	//	 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	//	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

	//	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	//	 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	//	 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	//	 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	//	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	//	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
	//};

	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	//Vec3 cubes[] = {
	//	Vec3(0.0f, 0.0f, 0.0f),
	//	Vec3(2.0f, 5.0f, -15.0f),
	//	Vec3(-1.5f, -2.2f, -2.5f),
	//	Vec3(-3.8f, -2.0f, -12.3f),
	//	Vec3(2.4f, -0.4f, -3.5f),
	//	Vec3(-1.7f, 3.0f, -7.5f),
	//	Vec3(1.3f, -2.0f, -2.5f),
	//	Vec3(1.5f, 2.0f, -2.5f),
	//	Vec3(1.5f, 0.2f, -1.5f),
	//	Vec3(-1.3f, 1.0f, -1.5f)
	//};

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
	//Shader shader("res/vertex_shader.vert", "res/fragment_shader.frag");
	Shader shader("res/lighting_shader.vert", "res/lighting_shader.frag");
	Shader lampShader("res/lamp_shader.vert", "res/lamp_shader.frag");

	//GLuint EBO;
	//glGenBuffers(1, &EBO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
		//glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) 0);
		glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	GLint modelLoc = glGetUniformLocation(shader.getProgram(), "model");
	GLint viewLoc = glGetUniformLocation(shader.getProgram(), "view");
	GLint projLoc = glGetUniformLocation(shader.getProgram(), "projection");
	GLint objectColorLoc = glGetUniformLocation(shader.getProgram(), "objectColor");
	GLint lightColorLoc = glGetUniformLocation(shader.getProgram(), "lightColor");
	GLint lightPosLoc = glGetUniformLocation(shader.getProgram(), "lightPos");

	shader.use();
	Mat4 objectModel = Mat4::createIdentity();
	Mat4 projection = Mat4::perspective(MathUtils::toRadians(75.0f), (float) window.getWidth() / (float) window.getHeight(), 0.1f, 100.0f);

	glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, objectModel.getInternal());
	glUniformMatrix4fv(projLoc, 1, GL_TRUE, projection.getInternal());

	GLint modelLampLoc = glGetUniformLocation(lampShader.getProgram(), "model");
	GLint viewLampLoc = glGetUniformLocation(lampShader.getProgram(), "view");
	GLint projLampLoc = glGetUniformLocation(lampShader.getProgram(), "projection");
	
	lampShader.use();
	glUniformMatrix4fv(projLampLoc, 1, GL_TRUE, projection.getInternal());



	Camera camera(Vec3(0.0f, 0.0f, 3.0f), 10.0f, 5.0f);
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
		Mat4 view = camera.getViewMatrix();
		//glUniformMatrix4fv(viewLoc, 1, GL_TRUE, view.getInternal());
		//glUniformMatrix4fv(projLoc, 1, GL_TRUE, projection.getInternal());

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Vec3 lightPos(1.2f + sin(currentTime), 1.0f, 2.0f);
		Mat4 lightModel = Mat4::translate(lightPos) *
						  Mat4::scale(Vec3(0.2f, 0.2f, 0.2f));

		shader.use();

		glUniformMatrix4fv(viewLoc, 1, GL_TRUE, view.getInternal());
		glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);

		//GLfloat r = 8.0f;
		//GLfloat camX = sin(window.getTime()) * r;
		//GLfloat camZ = cos(window.getTime()) * r;
		//Mat4 view = Mat4::lookAt(Vec3(camX, 0.0f, camZ),
		//						 Vec3(0.0f, 0.0f, 0.0f),
		//						 Vec3(0.0f, 1.0f, 0.0f));


		//container.bind(0);
		//awesomeface.bind(1);
		//glUniform1i(glGetUniformLocation(shader.getProgram(), "ourTexture"), 0);
		//glUniform1i(glGetUniformLocation(shader.getProgram(), "ourTexture2"), 1);

		glBindVertexArray(VAO);

		//for (int i = 0; i < 10; i++)
		//{
		//	Mat4 model = Mat4::translate(cubes[i]) *
		//		         Mat4::rotate(Quaternion::fromAxisAngle(Vec3(0.5f, 1.0f, 0.0f), MathUtils::toRadians((currentTime + 1000.0f) * (40.0f + (float) i))));
		//	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model.getInternal());
			glDrawArrays(GL_TRIANGLES, 0, 36);

		//}
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		lampShader.use();
		glUniformMatrix4fv(modelLampLoc, 1, GL_TRUE, lightModel.getInternal());

		glUniformMatrix4fv(viewLampLoc, 1, GL_TRUE, view.getInternal());


		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
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
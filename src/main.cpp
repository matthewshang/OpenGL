#include <vector>
#include <iostream>
#include <string>

#include <GL/glew.h>

#include "math/mat4.h"
#include "math/vec3.h"
#include "math/quaternion.h"
#include "math/mathutils.h"
#include "shader.h"
#include "texture.h"
#include "inputstate.h"
#include "window.h"
#include "camera.h"
#include "mesh.h"
#include "model.h"

void run(Window& window)
{
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

	Vec3 pointLights[] = 
	{
		Vec3(0.7f, 0.2f, 2.0f),
		Vec3(2.3f, -3.3f, -4.0f),
		Vec3(-4.0f, 2.0f, -12.0f),
		Vec3(0.0f, 0.0f, -3.0f)
	};

	GLfloat quadVertices[] = {   
        // Positions   // TexCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };	

	GLuint quadMesh;
	GLuint quadVBO;
	glGenVertexArrays(1, &quadMesh);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadMesh);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *) 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *) (2 * sizeof(GLfloat)));
	glBindVertexArray(0);
	//Model castle("res/meshes/Castle/castle01.obj");
	//Model nanosuit("res/meshes/nanosuit/nanosuit.obj");

	Model cube("res/meshes/cube/cube2.obj");
	Model plane("res/meshes/plane/plane.obj");

	Shader shader("phong");
	Shader quad("quad");
	//Shader shader("basic_shader");


	GLuint fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	GLuint texColorBuffer;
	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window.getWidth(), window.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

	GLuint rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, window.getWidth(), window.getHeight());
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Error::main: Renderbuffer not complete" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	quad.bind();
	quad.addUniform("screenTexture");
	quad.setInt("screenTexture", 0);

	shader.bind();

	shader.addUniform("model");
	shader.addUniform("view");
	shader.addUniform("projection");

	//shader.addUniform("tex");
	//shader.setInt("tex", 0);

	shader.addUniform("viewPos");
	shader.addUniform("material.diffuse");
	shader.addUniform("material.specular");
	shader.addUniform("material.shininess");

	shader.addUniform("dirLight.direction");
	shader.addUniform("dirLight.base.ambient");
	shader.addUniform("dirLight.base.color");

	shader.setInt("material.diffuse", 0);
	shader.setInt("material.specular", 1);
	shader.setFloat("material.shininess", 32.0f);

	shader.setVec3("dirLight.direction", Vec3(-0.2f, -1.0f, -0.3f));
	shader.setFloat("dirLight.base.ambient", 0.05f);
	shader.setVec3("dirLight.base.color", Vec3(0.6f, 0.6f, 0.6f));

	//for (int i = 0; i < 4; i++)
	//{
	//	shader.addUniform("pointLights[" + std::to_string(i) + "].base.color");
	//	shader.addUniform("pointLights[" + std::to_string(i) + "].base.ambient");
	//	shader.addUniform("pointLights[" + std::to_string(i) + "].position");
	//	shader.addUniform("pointLights[" + std::to_string(i) + "].atten.constant");
	//	shader.addUniform("pointLights[" + std::to_string(i) + "].atten.linear");
	//	shader.addUniform("pointLights[" + std::to_string(i) + "].atten.quadratic");

	//	shader.setVec3("pointLights[" + std::to_string(i) + "].base.color", Vec3(0.8f, 0.8f, 0.8f));
	//	shader.setFloat("pointLights[" + std::to_string(i) + "].base.ambient", 0.05f);
	//	shader.setVec3("pointLights[" + std::to_string(i) + "].position", pointLights[i]);
	//	shader.setFloat("pointLights[" + std::to_string(i) + "].atten.constant", 1.0f);
	//	shader.setFloat("pointLights[" + std::to_string(i) + "].atten.linear", 0.09f);
	//	shader.setFloat("pointLights[" + std::to_string(i) + "].atten.quadratic", 0.032f);
	//}

	//shader.addUniform("spotLight.position");
	//shader.addUniform("spotLight.direction");
	//shader.addUniform("spotLight.innerCutoff");
	//shader.addUniform("spotLight.outerCutoff");
	//shader.addUniform("spotLight.atten.constant");
	//shader.addUniform("spotLight.atten.linear");
	//shader.addUniform("spotLight.atten.quadratic");
	//shader.addUniform("spotLight.base.ambient");
	//shader.addUniform("spotLight.base.color");

	//shader.setVec3("spotLight.position", Vec3(-3.5f, 8.0f, 3.0f));
	//shader.setVec3("spotLight.direction", Vec3(0.7f, -0.45f, -0.55f));
	//shader.setFloat("spotLight.innerCutoff", cos(MathUtils::toRadians(17.5f)));
	//shader.setFloat("spotLight.outerCutoff", cos(MathUtils::toRadians(22.5f)));
	//shader.setFloat("spotLight.atten.constant", 1.0f);
	//shader.setFloat("spotLight.atten.linear", 0.09f);
	//shader.setFloat("spotLight.atten.quadratic", 0.032f);
	//shader.setFloat("spotLight.base.ambient", 0.05f);
	//shader.setVec3("spotLight.base.color", Vec3(1.0f, 1.0f, 1.0f));

	Mat4 projection = Mat4::perspective(MathUtils::toRadians(75.0f), (float) window.getWidth() / (float) window.getHeight(), 0.1f, 100.0f);
	shader.setMat4("projection", projection);
	
	Camera camera(Vec3(0.0f, 0.0f, 3.0f), 10.0f, 10.0f);
	GLfloat lastTime = 0.0f;

	while (!window.shouldClose())
	{
		GLfloat currentTime = window.getTime();
		GLfloat deltaTime = currentTime - lastTime;
		//std::cout << 1.0f / deltaTime << std::endl;
		lastTime = currentTime;

		window.pollEvents();
		if (window.getInputState().keyPressed(InputState::KEY_ESCAPE))
		{
			window.close();
		}

		camera.update(deltaTime, window.getInputState());
		Mat4 view = camera.getViewMatrix();

		// First pass
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, window.getWidth(), window.getHeight());

		shader.bind();

		shader.setMat4("view", view);
		shader.setVec3("viewPos", camera.getPosition());

		glEnable(GL_CULL_FACE);

		Mat4 model = Mat4::translate(Vec3(-1.0f, 0.0f, -1.0f)) *
					 Mat4::scale(Vec3(1.0f, 1.0f, 1.0f));
		shader.setMat4("model", model);
		cube.render();

		model = Mat4::translate(Vec3(2.0f, 0.0f, 0.0f)) *
				Mat4::scale(Vec3(1.0f, 1.0f, 1.0f));
		shader.setMat4("model", model);
		cube.render();

		glDisable(GL_CULL_FACE);

		model = Mat4::translate(Vec3(0.0f, -1.0f, 0.0f)) * Mat4::scale(Vec3(10.0f, 10.0f, 10.0f));
		shader.setMat4("model", model);
		plane.render();

		// Second pass
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);

		quad.bind();

		glBindVertexArray(quadMesh);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texColorBuffer);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindVertexArray(0);

		window.swapBuffers();
	}

	glDeleteFramebuffers(1, &fbo);
	glDeleteTextures(1, &texColorBuffer);
	glDeleteRenderbuffers(1, &rbo);
}

int main()
{
	Window window(1000, 750, "OpenGL");

	run(window);

	return 0;
}
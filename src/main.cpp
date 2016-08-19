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
	//GLfloat vertices[] = 
	//{
	//	 // Positions         // Normals           // Texture Coords
	//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	//	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	//	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	//	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	//	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	//	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	//	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	//	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	//	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	//	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	//	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	//	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	//	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	//	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	//	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	//	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	//	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	//	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	//	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	//	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	//	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	//	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	//	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	//	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	//	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	//	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	//	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	//	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	//	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	//};

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

	//Texture container2("res/container2.png", Texture::Type::TEXTURE_DIFFUSE);
	//Texture container2Specular("res/container2_specular.png", Texture::Type::TEXTURE_SPECULAR);
	//std::vector<Vertex> vertices;
	//std::vector<int> indices;
	//vertices.push_back(Vertex(Vec3(0.5f, 0.5f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec2(1.0f, 1.0f)));
	//vertices.push_back(Vertex(Vec3(0.5f, -0.5f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec2(1.0f, 0.0f)));
	//vertices.push_back(Vertex(Vec3(-0.5f, -0.5f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec2(0.0f, 0.0f)));
	//vertices.push_back(Vertex(Vec3(-0.5f, 0.5f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec2(0.0f, 1.0f)));
	//indices.push_back(0);
	//indices.push_back(1);
	//indices.push_back(3);
	//indices.push_back(1);
	//indices.push_back(2);
	//indices.push_back(3);

	Model model("res/nanosuit/nanosuit.obj");
	//Mesh mesh(vertices, indices);
	Shader shader("phong");

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	shader.bind();

	shader.addUniform("model");
	shader.addUniform("view");
	shader.addUniform("projection");

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
	shader.setVec3("dirLight.base.color", Vec3(0.4f, 0.4f, 0.4f));

	for (int i = 0; i < 4; i++)
	{
		shader.addUniform("pointLights[" + std::to_string(i) + "].base.color");
		shader.addUniform("pointLights[" + std::to_string(i) + "].base.ambient");
		shader.addUniform("pointLights[" + std::to_string(i) + "].position");
		shader.addUniform("pointLights[" + std::to_string(i) + "].atten.constant");
		shader.addUniform("pointLights[" + std::to_string(i) + "].atten.linear");
		shader.addUniform("pointLights[" + std::to_string(i) + "].atten.quadratic");

		shader.setVec3("pointLights[" + std::to_string(i) + "].base.color", Vec3(0.8f, 0.8f, 0.8f));
		shader.setFloat("pointLights[" + std::to_string(i) + "].base.ambient", 0.05f);
		shader.setVec3("pointLights[" + std::to_string(i) + "].position", pointLights[i]);
		shader.setFloat("pointLights[" + std::to_string(i) + "].atten.constant", 1.0f);
		shader.setFloat("pointLights[" + std::to_string(i) + "].atten.linear", 0.09f);
		shader.setFloat("pointLights[" + std::to_string(i) + "].atten.quadratic", 0.032f);
	}

	shader.addUniform("spotLight.position");
	shader.addUniform("spotLight.direction");
	shader.addUniform("spotLight.innerCutoff");
	shader.addUniform("spotLight.outerCutoff");
	shader.addUniform("spotLight.atten.constant");
	shader.addUniform("spotLight.atten.linear");
	shader.addUniform("spotLight.atten.quadratic");
	shader.addUniform("spotLight.base.ambient");
	shader.addUniform("spotLight.base.color");

	shader.setVec3("spotLight.position", Vec3(-3.5f, 8.0f, 3.0f));
	shader.setVec3("spotLight.direction", Vec3(0.7f, -0.45f, -0.55f));
	shader.setFloat("spotLight.innerCutoff", cos(MathUtils::toRadians(17.5f)));
	shader.setFloat("spotLight.outerCutoff", cos(MathUtils::toRadians(22.5f)));
	shader.setFloat("spotLight.atten.constant", 1.0f);
	shader.setFloat("spotLight.atten.linear", 0.09f);
	shader.setFloat("spotLight.atten.quadratic", 0.032f);
	shader.setFloat("spotLight.base.ambient", 0.05f);
	shader.setVec3("spotLight.base.color", Vec3(1.0f, 1.0f, 1.0f));

	Mat4 projection = Mat4::perspective(MathUtils::toRadians(75.0f), (float) window.getWidth() / (float) window.getHeight(), 0.1f, 100.0f);
	shader.setMat4("projection", projection);
	
	Camera camera(Vec3(0.0f, 0.0f, 3.0f), 10.0f, 4.0f);
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

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.bind();

		shader.setMat4("view", view);
		Vec3 camPos = camera.getPosition();

		shader.setVec3("viewPos", camPos);

		//shader.setVec3("spotLight.position", camPos);
		//shader.setVec3("spotLight.direction", camera.getFront());

		//container2.bind(0);
		//container2Specular.bind(1);

		//for (int i = 0; i < 10; i++)
		//{
		//	Mat4 objectModel = Mat4::translate(cubes[i]) *
		//		Mat4::rotate(Quaternion::fromAxisAngle(Vec3(1.0f, 0.3f, 0.5f), MathUtils::toRadians(20.0f * i)));
		//	shader.setMat4("model", objectModel);
		//	mesh.render();
		//}

		Mat4 objectModel = Mat4::scale(Vec3(0.5f, 0.5f, 0.5f));
		shader.setMat4("model", objectModel);
		model.render();

		window.swapBuffers();
	}
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
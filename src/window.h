#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "inputstate.h"

class Window
{
public:
	Window(int width, int height, char* title);
	~Window();

	int getWidth();
	int getHeight();
	InputState& getInputState();
	bool shouldClose();
	float getTime();

	void close();
	void pollEvents();
	void swapBuffers();

private:
	GLFWwindow* m_window;
	InputState m_inputState;
	int m_width;
	int m_height;

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
};
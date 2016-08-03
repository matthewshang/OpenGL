#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <exception>
#include <iostream>

#include "InputState.h"

class WindowInitException : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Error: failed to create GLFWwindow";
	}
};

class Window
{
public:
	Window(int width, int height, char* title);
	~Window();

	void getFramebufferSize(int& width, int& height);
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

#endif
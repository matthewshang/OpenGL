#include "window.h"

#include <iostream>

Window::Window(int width, int height, char* title) : 
	m_inputState(width, height), m_width(width), m_height(height)
{
	if (!glfwInit())
	{
		std::cout << "Error: failed to initialize GLFW" << std::endl;
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (m_window == nullptr)
	{
		std::cout << "Error: failed to create window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetWindowUserPointer(m_window, this);
	glfwSetKeyCallback(m_window, keyCallback);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwMakeContextCurrent(m_window);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "Error: failed to initialize GLEW" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Window::getFramebufferSize(int& width, int& height)
{
	glfwGetFramebufferSize(m_window, &width, &height);
}

int Window::getWidth()
{
	return m_width;
}

int Window::getHeight()
{
	return m_height;
}

InputState& Window::getInputState()
{
	return m_inputState;
}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(m_window);
}

float Window::getTime()
{
	return glfwGetTime();
}

void Window::close()
{
	glfwSetWindowShouldClose(m_window, GL_TRUE);
}

void Window::pollEvents()
{
	glfwPollEvents();
	double xpos, ypos;
	glfwGetCursorPos(m_window, &xpos, &ypos);
	m_inputState.updateMouse(xpos, ypos);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(m_window);
}

void Window::keyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mode)
{
	Window* window = static_cast<Window*> (glfwGetWindowUserPointer(glfwWindow));
	window->getInputState().updateKey(key, action);
}
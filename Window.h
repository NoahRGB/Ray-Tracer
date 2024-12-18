#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "Square.h"
#include "RayTracer.h"

class Window {
private:
	int width, height;
	char* title;
	GLFWwindow* window;

	Square square;

	void display();
	void setup();
	static void reshape(GLFWwindow* window, int width, int height);


public:
	Window(int width, int height, char* title);

	int init();
	void run();
};
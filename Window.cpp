#include "Window.h"
#include "RayTracer.h"

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <iostream>

RayTracer rt;


Window::Window(int width, int height, char* title) {
	this->width = width;
	this->height = height;
	this->title = title;
}

void Window::reshape(GLFWwindow* window, int width, int height) {
	//this->width = width;
	//this->height = height;

	glViewport(0.0, 0.0, width, height);
}

int Window::init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL) {
		std::cout << "GLFW window creation failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cout << " GLEW ERROR" << std::endl;
		return -1;
	}

	setup();

	glfwSetFramebufferSizeCallback(window, reshape);
	reshape(window, width, height);

	return 0;
}

void Window::setup() {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	rt.addLight(glm::vec3(20.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 0.7, 0.0), 5, glm::vec3(0.0, 0.0, 0.7), 2, 10);
	rt.addSphere(glm::vec3(0.0, 0.0, -70.0), 15.0f, { glm::vec3(1, 1, 0), 0.1, 0.9, 0.5, 200 });
	rt.addSphere(glm::vec3(0.0, 35.0, -70.0), 15.0f, { glm::vec3(0, 1, 0), 0.1, 0.9, 0.5, 200 });
	rt.addSphere(glm::vec3(0.0, -35.0, -70.0), 15.0f, { glm::vec3(0, 0, 1), 0.1, 0.9, 0.5, 200 });
	rt.addSphere(glm::vec3(-300.0, 0.0, -320.0), 300.0f, { glm::vec3(1, 0, 0), 0.7, 0.5, 0.0, 200 });

	auto time1 = std::chrono::high_resolution_clock::now();
	rt.rayTrace();
	auto time2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> timeTaken = time2 - time1;
	std::cout << "Time taken: " << timeTaken.count() << std::endl;

	square.init(width, height, rt.getPixels());
}

void Window::run() {
	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();

		display();
	}

	glfwTerminate();
}

void Window::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	square.render();
}


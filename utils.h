#pragma once

#include <vector>

#include "glm\glm.hpp"
#include <gl/glew.h>

struct Light {
	glm::vec3 position;
	glm::vec3 colour;
	glm::vec3 uvec;
	int usteps;
	glm::vec3 vvec;
	int vsteps;
	int samples;
};

struct Material {
	glm::vec3 colour;
	float ambient;
	float diffuse;
	float specular;
	float shininess;
};

struct RayHit {
	float t = 999;
	Material mat = {};
	glm::vec3 hitPoint = glm::vec3();
	glm::vec3 normal = glm::vec3();
	glm::vec3 objectPos;
};

bool solveQuadratic(const float& a, const float& b, const float& c, float& x0, float& x1);
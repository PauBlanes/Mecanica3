#pragma once
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <GL\glew.h>
using namespace glm;

extern float gravity;

class Cubo {
public:
	Cubo(vec3 inicialPos, GLfloat massa);
	void Update(GLfloat deltaTime);
	void Draw();
	void DetectCollision();
private:
	vec3 P; //angular momentum
	vec3 position;
	vec3 v; //velocidad linera
	vec3 pointOfApplication;//on apliquem la força
	vec3 force;
	vec3 torque;
	vec3 w;
	vec3 L;
	mat3 rotation;
	mat3 Ibody;
	mat3 I; //rensor d'inercia	
	GLfloat mass;
};
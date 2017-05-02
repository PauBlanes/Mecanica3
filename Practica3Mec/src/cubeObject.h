#pragma once
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <GL\glew.h>
#include <iostream>
#include <time.h>   
using namespace glm;

//Per pitnar el cub
extern bool renderCaixa;
namespace Caixa {
	extern void setupCaixa(glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f), float length = 0.5f, glm::vec3 color = glm::vec3(1.f, 0.54902f, 0.f));
	extern void cleanupCaixa();
	extern void updateCaixa(glm::mat4 modelMat);
	extern void DrawCaixa();
}

class Cubo {
public:
	Cubo(vec3 inicialPos, GLfloat massa);
	void Update(GLfloat deltaTime);
	void Reset();
	void DetectCollision();

	float gravity;
private:
	vec3 P; //angular momentum
	vec3 position;
	vec3 v; //velocidad linera
	vec3 pointOfApplication;//on apliquem la força
	vec3 force;
	vec3 torque;
	vec3 w;
	vec3 L;
	quat q;
	mat3 Ibody;
	mat3 Iinverse; //rensor d'inercia	
	GLfloat mass;
	
	
};



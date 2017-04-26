#include "cubeObject.h"

float gravity = -9.8f;
bool renderCaixa = true;

Cubo::Cubo(vec3 inicialPos, GLfloat massa) {
	mass = massa;
	position = inicialPos;
	Reset();
}

void Cubo::Update(GLfloat deltaTime) {
	
	position += deltaTime*v;
	v = P / mass;
	P += deltaTime*force;
	force = { 0,mass * gravity,0 };

	//Pintar
	mat4 prova = mat4(1.f);
	prova = translate(prova, position);
	//prova = glm::rotate(prova, glm::radians(60.f), glm::vec3(1.f, 0.f, 0.f));
	Caixa::updateCaixa(prova);
		
}

void Cubo::Reset() {
	
	srand(time(NULL));
	
	P = { 0,0,0 };
	position = { rand() % 4 + 1,rand() % 9 + 1,rand() % 4 + 1 };
	v = { 0,0,0 };
	torque = { 0,0,0 };
	w = { 0,0,0 };
	L = { 0,0,0 };
	rotation = mat3(1.f);
	I = mat3(1.f);
	
	Ibody = mat3(1.f);
	Ibody[0][0] = (1 / 12)*mass*(pow(.5f, 2)* pow(.5f, 2));
	Ibody[1][1] = (1 / 12)*mass*(pow(.5f, 2)* pow(.5f, 2));
	Ibody[2][2] = (1 / 12)*mass*(pow(.5f, 2)* pow(.5f, 2));
	force = { rand()%150+50,rand() % 150 + 50,rand() % 150 + 50 };
}

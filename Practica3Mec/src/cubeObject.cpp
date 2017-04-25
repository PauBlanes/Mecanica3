#include "cubeObject.h"

Cubo::Cubo(vec3 incialPos, GLfloat massa) {
	position = incialPos;
	P = {0,0,0};
	position = incialPos;
	v = { 0,0,0 };
	force = { 0,0,0 };
	torque = { 0,0,0 };
	w = { 0,0,0 };
	L = { 0,0,0 };
	rotation = mat3(1.f);	
	I = mat3(1.f);
	mass = massa;

	Ibody; //calcular la matriz esta
}
#include "cubeObject.h"


bool renderCaixa = true;

Cubo::Cubo(vec3 inicialPos, GLfloat massa) {
	mass = massa;
	position = inicialPos;
	Reset();
}

void Cubo::Update(GLfloat deltaTime) {
	
	//movimiento
	position += deltaTime*v;
	v = P / mass;
	P += deltaTime*force;
	force = { 0,mass * gravity,0 };

	//rotacion
		//calculamos torque
		//calculamos L
		//mat3 temporal R a partir de q
		//calculamos I-1
		//calculamos w
		//q += deltaTime*((1/2)* (w pasada a quaternion con 0 en la primera coordenada) * q)
		//normalizamos q		

	//Actualizamos cubo
	mat4 temp = mat4(1.f);
	temp = translate(temp, position);
	//temp = mat4_cast(q)
	Caixa::updateCaixa(temp);
		
}

void Cubo::Reset() {
	
	srand(time(NULL));
	
	P = { 0,0,0 };
	position = { rand() % 3 + 1,rand() % 8 + 1,rand() % 3 + 1 };
	pointOfApplication = { rand() % (position + 0.5) - 0.25, position - 0.25, rand() % (position + 0.5) - 0.25 }; //https://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful
	v = { 0,0,0 };
	torque = { 0,0,0 };
	w = { 0,0,0 };
	L = { 0,0,0 };
	q = mat3(1.f);
	I = mat3(1.f);
	
	Ibody = mat3(1.f);
	Ibody[0][0] = (1 / 12)*mass*(pow(.5f, 2)* pow(.5f, 2));
	Ibody[1][1] = (1 / 12)*mass*(pow(.5f, 2)* pow(.5f, 2));
	Ibody[2][2] = (1 / 12)*mass*(pow(.5f, 2)* pow(.5f, 2));
	force = { 0,rand() % 150 + 50,0 };
}

#include "cubeObject.h"


bool renderCaixa = true;

Cubo::Cubo(vec3 inicialPos, GLfloat massa) {
	mass = massa;
	position = inicialPos;
	Reset();
}

void Cubo::Update(GLfloat deltaTime) {
	
	//movimiento	
	P += deltaTime*force;
	v = P / mass;
	position += deltaTime*v;	

	//rotacion	
		//mat3 temporal R a partir de q
		mat3 R = mat3_cast(q);
		//calculamos I-1
		Iinverse = R * inverse(Ibody) * transpose(R);
		//calculamos w
		w = Iinverse * L;
		//q += deltaTime*((1/2)* (w pasada a quaternion con 0 en la primera coordenada) * q)
		quat tempW = quat(0,w);
		q += deltaTime*(0.5f*(tempW*q));
		//normalizamos q
		q = normalize(q);
		
	force = { 0,mass * gravity,0 };
	//Pasamos matrices al cubo
	mat4 temp = mat4(1.f);
	temp = translate(temp, position);
	temp *= mat4_cast(q);
	
	//Actualizamos el sahder
	Caixa::updateCaixa(temp);
		
}

void Cubo::Reset() {
	
	srand(time(NULL));
	
	P = { 0,0,0 };
	position = { rand() % 3 + 1,rand() % 8 + 1,rand() % 3 + 1 };
	//pointOfApplication = { rand() % (position + 0.5) - 0.25, position - 0.25, rand() % (position + 0.5) - 0.25 };
	pointOfApplication = { position.x - 0.25, position.y - 0.25, position.z + 0.25 };
	v = { 0,0,0 };
	torque = { 0,0,0 };
	w = { 0,0,0 };
	L = { 0,0,0 };
	q = quat(1, 0,0,0);
	Iinverse = mat3(1.f);
	
	float prova = (mass*0.5) / 12;
	Ibody = mat3(prova);
	force = { 0, 25 + rand()%75,0 };
	//calculamos torque
	torque = cross((pointOfApplication - position), force);
	//calculamos L
	L = torque*0.033f;
}

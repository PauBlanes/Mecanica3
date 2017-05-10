#include "cubeObject.h"


bool renderCaixa = true;

Cubo::Cubo(vec3 inicialPos, GLfloat massa) {
	mass = massa;
	position = inicialPos;
	elastic = 1;
	Reset();
}

void Cubo::Update(GLfloat deltaTime) {
	
	//Pasamos matrices al cubo
	mat4 temp = mat4(1.f);
	temp = translate(temp, position);
	temp *= mat4_cast(q);

	//Actualizamos el shader
	Caixa::updateCaixa(temp);
	
	//RECALCULEM TOT
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
}

void Cubo::Reset() {
	
	srand(time(NULL));
	
	P = { 0,0,0 };
	position = { rand() % 3 + 1,rand() % 8 + 1,rand() % 3 + 1 };
	pointOfApplication = { position.x - 0.25, position.y + 0.25, position.z + 0.25 };
	/*int randVertex = rand() % 3;
	switch (randVertex) {
	case 0:
		pointOfApplication = { position.x - 0.25, position.y - 0.25, position.z + 0.25 };
		break;
	case 1:
		pointOfApplication = { position.x + 0.25, position.y - 0.25, position.z + 0.25 };
		break;
	case 2:
		pointOfApplication = { position.x + 0.25, position.y - 0.25, position.z - 0.25 };
		break;
	case 3:
		pointOfApplication = { position.x - 0.25, position.y - 0.25, position.z - 0.25 };
		break;
	}*/
	
	v = { 0,0,0 };
	torque = { 0,0,0 };
	w = { 0,0,0 };
	L = { 0,0,0 };
	q = quat(1, 0,0,0);
	Iinverse = mat3(1.f);
	
	float prova = (mass*0.5) / 12;
	Ibody = mat3(prova);
	force = { 100, 0,0 };
	//calculamos torque
	torque = cross((pointOfApplication - position), force);
	//calculamos L
	L = torque*0.033f;
}

void Cubo::DetectCollision(vec3 normal, GLfloat d, GLfloat dt) {

	//actualitzem posicions dels vertexs
	verticesPositions[0] = vec3(position.x + 0.25f, position.y + 0.25f, position.z + 0.25f);
	verticesPositions[1] = vec3(position.x + 0.25f, position.y + 0.25f, position.z - 0.25f);
	verticesPositions[2] = vec3(position.x + 0.25f, position.y - 0.25f, position.z + 0.25f);
	verticesPositions[3] = vec3(position.x + 0.25f, position.y - 0.25f, position.z - 0.25f);
	verticesPositions[4] = vec3(position.x - 0.25f, position.y + 0.25f, position.z + 0.25f);
	verticesPositions[5] = vec3(position.x - 0.25f, position.y + 0.25f, position.z - 0.25f);
	verticesPositions[6] = vec3(position.x - 0.25f, position.y - 0.25f, position.z + 0.25f);
	verticesPositions[7] = vec3(position.x - 0.25f, position.y - 0.25f, position.z - 0.25f);

	
	//calculem quina seria la seva seguent posicio per a cada un dels vertexs
	for (int i = 0; i < 8; i++) {
		
		vec3 posCreuada = verticesPositions[i] + dt*v; //simulem nova pos
		if ((dot(normal, verticesPositions[i]) + d) * (dot(normal, posCreuada) + d) <= 0) { //PRIMERA VEGADA QUE COLISONEM
			
			//TROBEM EL TEMPS EXACTE
			GLfloat newdt = dt/2;
			GLfloat lastNewDt = 0;
			GLfloat multiple = 4;
			while (multiple < 4096) {				
				vec3 posCreuada = verticesPositions[i] + newdt*v; //simulem nova pos
				lastNewDt = newdt;
				if ((dot(normal, verticesPositions[i]) + d) * (dot(normal, posCreuada) + d) <= 0) {
					newdt -= dt / multiple;
				}
				else {
					newdt += dt / multiple;
				}
				multiple *= 2;
								
			}
			
			//CALCULEM pa
				vec3 P_t0 = P + newdt*force;
				vec3 v_t0 = P_t0 / mass;
				vec3 position_t0 = position + newdt*v_t0;
				//mat3 temporal R a partir de q
				mat3 lastR = mat3_cast(q);
				//calculamos I-1
				mat3 lastIinverse = mat3(1.f);
				lastIinverse = lastR * inverse(Ibody) * transpose(lastR);
				//calculamos w
				vec3 w_t0 = lastIinverse * L;
				//actualitzem posicions dels vertexs
				vec3 tempVertexs[8];
				tempVertexs[0] = vec3(position_t0.x + 0.25f, position_t0.y + 0.25f, position_t0.z + 0.25f);
				tempVertexs[1] = vec3(position_t0.x + 0.25f, position_t0.y + 0.25f, position_t0.z - 0.25f);
				tempVertexs[2] = vec3(position_t0.x + 0.25f, position_t0.y - 0.25f, position_t0.z + 0.25f);
				tempVertexs[3] = vec3(position_t0.x + 0.25f, position_t0.y - 0.25f, position_t0.z - 0.25f);
				tempVertexs[4] = vec3(position_t0.x - 0.25f, position_t0.y + 0.25f, position_t0.z + 0.25f);
				tempVertexs[5] = vec3(position_t0.x - 0.25f, position_t0.y + 0.25f, position_t0.z - 0.25f);
				tempVertexs[6] = vec3(position_t0.x - 0.25f, position_t0.y - 0.25f, position_t0.z + 0.25f);
				tempVertexs[7] = vec3(position_t0.x - 0.25f, position_t0.y - 0.25f, position_t0.z - 0.25f);
			//fem pa
			vec3 ra = (tempVertexs[i] - position_t0);
			vec3 pa_t0 = v_t0 + cross(w_t0, ra);

			//CALCULEM vrel			
			GLfloat vrel = dot(normal, pa_t0);
			
			//CALCULEM j i J
			GLfloat j = -((1 + elastic)*vrel);
			j /= ((1 / mass) + dot(normal, cross((lastIinverse * cross(ra, normal)), ra)));
			
			vec3 J = j * normal;
			
			//CALCULEM torque
			torque = cross(ra, J);			
			//RECLAULEM TOT/
			P = J;						
			v = J / mass;			
			position = position_t0 + v*dt;
			L += torque;
			w = Iinverse * torque;
			quat tempW = quat(0, w);
			q += dt*(0.5f*(tempW*q));
			//normalizamos q
			q = normalize(q);
			
		}
		
	}
	
}

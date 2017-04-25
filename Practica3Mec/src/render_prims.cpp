#include <GL\glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <cstdio>

//Boolean variables allow to show/hide the primitives
bool renderSphere = true;
bool renderCaixa = true;
bool renderCapsule = false;
bool renderParticles = false;
bool renderCloth = true;

namespace Sphere {
	extern void setupSphere(glm::vec3 pos = glm::vec3(0.f, 1.f, 0.f), float radius = 1.f);
	extern void cleanupSphere();
	extern void updateSphere(glm::vec3 pos, float radius = 1.f);
	extern void drawSphere();
}
namespace Caixa {
	extern void setupCaixa(glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f), float length = 1.f, glm::vec3 color = glm::vec3(1.f, 0.54902f, 0.f));
	extern void cleanupCaixa();
	extern void updateCaixa(glm::mat4 modelMat);
	extern void DrawCaixa();
}
namespace Capsule {
	extern void setupCapsule(glm::vec3 posA = glm::vec3(-3.f, 2.f, -2.f), glm::vec3 posB = glm::vec3(-4.f, 2.f, 2.f), float radius = 1.f);
	extern void cleanupCapsule();
	extern void updateCapsule(glm::vec3 posA, glm::vec3 posB, float radius = 1.f);
	extern void drawCapsule();
}
namespace LilSpheres {
	extern const int maxParticles;
	extern void setupParticles(int numTotalParticles, float radius = 0.05f);
	extern void cleanupParticles();
	extern void updateParticles(int startIdx, int count, float* array_data);
	extern void drawParticles(int startIdx, int count);
}
namespace ClothMesh {
	extern void setupClothMesh();
	extern void cleanupClothMesh();
	extern void updateClothMesh(float* array_data);
	extern void drawClothMesh();
}

void setupPrims() {
	Sphere::setupSphere();
	Caixa::setupCaixa();
	Capsule::setupCapsule();
	LilSpheres::setupParticles(LilSpheres::maxParticles);
	ClothMesh::setupClothMesh();
}
void cleanupPrims() {
	Sphere::cleanupSphere();
	Caixa::cleanupCaixa();
	Capsule::cleanupCapsule();
	LilSpheres::cleanupParticles();
	ClothMesh::cleanupClothMesh();
}

void renderPrims() {
	/*if (renderSphere)
		Sphere::drawSphere();
	if (renderCapsule)
		Capsule::drawCapsule();

	if (renderParticles) {
		LilSpheres::drawParticles(0, LilSpheres::maxParticles);
	}*/

	if (renderCaixa) {
		glm::mat4 prova=glm::mat4(1.f);
		prova = glm::translate(prova, glm::vec3(0.f, 5.f, 0.f));
		prova = glm::rotate(prova, glm::radians(60.f), glm::vec3(1.f, 0.f, 0.f));
		Caixa::updateCaixa(prova);
		Caixa::DrawCaixa();
	}
	
	/*if (renderCloth)
		ClothMesh::drawClothMesh();*/
}

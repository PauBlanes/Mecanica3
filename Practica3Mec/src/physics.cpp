#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>
#include <iostream>
using namespace std;
float Second;
#include "cubeObject.h"

bool show_test_window = false;
static bool Play_simulation = true;
static bool Reset = false;
static bool Collisions = true;
static float resertTime = 5;
static float GravityAccel[3] = { 0.0f, -9.81f,0.0f };
static float Torelance = 0;
static float elastic = 0;


Cubo myCube (vec3 (0.f,5.f,0.f),1.f);

void GUI() {
	{	//FrameRate
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		Second += 1 / ImGui::GetIO().Framerate;

		//TODO
		//for play & stop
		ImGui::Checkbox("Play simulation", &Play_simulation);
		//for resert
		if (ImGui::Button("Reset simulation")) {
			Reset ^= 1;
		}
		//Resert Time
		ImGui::DragFloat("Resert Time", &resertTime, 5);
		//Gravity
		ImGui::InputFloat3("Gravity Accel", GravityAccel);
		
		if (ImGui::CollapsingHeader("Collisions")) {
			//Use Sphere collider
			ImGui::Checkbox("Use Collisions", &Collisions);
			ImGui::DragFloat("Torelance", &Torelance);
			ImGui::DragFloat("Elastic Coefficient", &elastic);
		}
	}

	// ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
	if(show_test_window) {
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
	}
}

void PhysicsInit() {
	Caixa::setupCaixa();
	myCube.Reset();
}
void PhysicsUpdate(float dt) {
	//TODO
	
	if (Play_simulation) {
		if (Second >= resertTime) {
			Second = 0;
			Reset = true;
		}
	}
	if (Reset) {
		Second = 0;
		Second += 1 / ImGui::GetIO().Framerate;
		PhysicsInit();
		Reset = false;
		Play_simulation = true;
	}
	myCube.Update(dt);
	

}
void PhysicsCleanup() {
	//TODO
}
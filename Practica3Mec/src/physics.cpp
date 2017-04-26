#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>
#include "cubeObject.h"

bool show_test_window = false;

Cubo myCube (vec3 (0.f,5.f,0.f),1.f);

void GUI() {
	{	//FrameRate
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		//TODO
	}

	// ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
	if(show_test_window) {
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
	}
}

void PhysicsInit() {
	Caixa::setupCaixa();
	
}
void PhysicsUpdate(float dt) {
	myCube.Update(dt);
	

}
void PhysicsCleanup() {
	//TODO
}
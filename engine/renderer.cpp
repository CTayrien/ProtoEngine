/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "engine.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <FreeImage.h>

shader renderer::theshader;
shader renderer::shader_skybox;

material renderer::thematerial;

bool renderer::start()
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(.45f, .45f, .9f, 1.f);

	shader_skybox = shader("engine/shaders/vshader_skybox.glsl", "engine/shaders/fshader_skybox.glsl");
	if (!shader_skybox.load()) return false;
	if (!theshader.load()) return false;
	
	theshader.use();

	thematerial.use();


	// Init imgui
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize.x = window::w;
	io.DisplaySize.y = window::h;
	io.IniFilename = "imgui.ini";
	// default null render function
	// default texture atlas
	
	unsigned char* pixels;
	int width, height;
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
	
	GLuint texid;
	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_2D, texid);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_SRGB_ALPHA,
		width,
		height,
		0,
		GL_BGRA,
		GL_UNSIGNED_BYTE,
		pixels);
	
	io.Fonts->TexID = (void*)&texid;

	ImGui::NewFrame();

	return true;
}

void renderer::update()
{
	// 1) get low-level inputs (e.g. on Win32, GetKeyboardState(), or poll your events, etc.)
	// TODO: fill all fields of IO structure and call NewFrame
	//ImGuiIO& io = ImGui::GetIO();
	//io.DeltaTime = 1.0f / 60.0f;
	//io.MousePos = mouse_pos;
	//io.MouseDown[0] = mouse_button_0;
	//io.MouseDown[1] = mouse_button_1;
	//io.KeysDown[i] = ...

	// 4) render & swap video buffers
	ImGui::Render();
	
	// Send color buffer to screen, clear new frame buffers
	glfwSwapBuffers(window::ptr);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// 2) call NewFrame(), after this point you can use ImGui::* functions anytime
	ImGui::NewFrame();

	// should this be somewhere else?
	engine::skybox.render();

	// no is work!
	//if (ImGui::BeginMainMenuBar())
	//{
	//	if (ImGui::BeginMenu("File"))
	//	{
	//		//ShowExampleMenuFile();
	//		ImGui::EndMenu();
	//	}
	//	if (ImGui::BeginMenu("Edit"))
	//	{
	//		if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
	//		if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
	//		ImGui::Separator();
	//		if (ImGui::MenuItem("Cut", "CTRL+X")) {}
	//		if (ImGui::MenuItem("Copy", "CTRL+C")) {}
	//		if (ImGui::MenuItem("Paste", "CTRL+V")) {}
	//		ImGui::EndMenu();
	//	}
	//	ImGui::EndMainMenuBar();
	//}
}

void renderer::stop()
{
	theshader.unload();
	shader_skybox.unload();
}
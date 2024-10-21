#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <AtGfx/GraphicsDevice.h>
#include <AtGfx/Shader.h>
#include <AtGfx/Pipeline.h>
#include <AtGfx/Buffer.h>

#include <stdio.h>

#include "Test/TestMenu.h"
#include "Test/Tests/ClearColorTest.h"
#include "Test/LearnOpenGL/GettingStarted/HelloWindowTest.h"
#include "Test/LearnOpenGL/GettingStarted/HelloTriangleP1_VBO.h"
#include "Test/LearnOpenGL/GettingStarted/HelloTriangleP2_IBO.h"
#include "Test/LearnOpenGL/GettingStarted/ShadersP1_Uniforms.h"
#include "Test/LearnOpenGL/GettingStarted/ShadersP2_MoreAttributes.h"
#include "Test/LearnOpenGL/GettingStarted/TexturesP1_Container.h"
#include "Test/LearnOpenGL/GettingStarted/TexturesP2_TextureUnits.h"

void AtGfxMessageCallback(AtGfx::MessageSeverity severity, const char* message)
{
	printf("%s\n", message);
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1600, 900, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	ImGui::StyleColorsDark();

	AtGfx::GraphicsDevice* graphicsDevice = AtGfx::GraphicsDevice::Create(AtGfx::GraphicsAPI::OpenGL, {
		.GLGetAddressProc = (void* (*)(const char* name))glfwGetProcAddress,
		.MessageCallback = AtGfxMessageCallback
		});
	graphicsDevice->Initialize();

	Test* currentTest = nullptr;
	TestMenu testMenu(graphicsDevice, currentTest);

	{
		std::string testsCategory = testMenu.RegisterCategory("Tests");
		testMenu.RegisterTest<Tests::ClearColorTest>(testsCategory, "Clear Color");
	}

	{
		std::string learnOpenGLCategory = testMenu.RegisterCategory("LearnOpenGL");
		testMenu.RegisterTest<LearnOpenGL::HelloWindowTest>(learnOpenGLCategory, "Hello Window (Clear Color)");
		testMenu.RegisterTest<LearnOpenGL::HelloTriangleP1_VBO>(learnOpenGLCategory, "Hello Triangle (P1 - VBO)");
		testMenu.RegisterTest<LearnOpenGL::HelloTriangleP2_IBO>(learnOpenGLCategory, "Hello Triangle (P2 - IBO/EBO)");
		testMenu.RegisterTest<LearnOpenGL::ShadersP1_Uniforms>(learnOpenGLCategory, "Shaders (P1 - Uniforms)");
		testMenu.RegisterTest<LearnOpenGL::ShadersP2_MoreAttributes>(learnOpenGLCategory, "Shaders (P2 - More Attributes)");
		testMenu.RegisterTest<LearnOpenGL::TexturesP1_Container>(learnOpenGLCategory, "Textures (P1 - Wooden Container)");
		testMenu.RegisterTest<LearnOpenGL::TexturesP2_TextureUnits>(learnOpenGLCategory, "Textures (P2 - Texture Units)");
	}

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		// should the test be responsible for clearing?
		graphicsDevice->Clear(1.0f, 1.0f, 1.0f, 1.0f);

		if (currentTest)
		{
			currentTest->Perform((float)glfwGetTime());
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		testMenu.ImGuiRender();

		ImGui::ShowDemoWindow();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	if (currentTest != nullptr)
	{
		currentTest->Deinitialize();
	}

	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}


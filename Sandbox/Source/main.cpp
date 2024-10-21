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
#include "Test/LearnOpenGL/HelloWindowTest.h"
#include "Test/LearnOpenGL/HelloTriangleP1_VBO.h"
#include "Test/LearnOpenGL/HelloTriangleP2_IBO.h"

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
	}

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		// should the test be responsible for clearing?
		graphicsDevice->Clear(1.0f, 1.0f, 1.0f, 1.0f);

		if (currentTest)
		{
			currentTest->Perform();
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


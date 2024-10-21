#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <AtGfx/GraphicsDevice.h>
#include <AtGfx/Shader.h>
#include <AtGfx/Pipeline.h>
#include <AtGfx/Buffer.h>

#include <stdio.h>

#include "Test/ClearColorTest.h"
#include "Test/Tests/ClearColorTest.h"
#include "Test/LearnOpenGL/HelloWindowTest.h"
#include "Test/LearnOpenGL/HelloTriangleP1.h"

void AtGfxMessageCallback(AtGfx::MessageSeverity severity, const char* message)
{
	printf("%s\n", message);
}

void RenderImGuiMenu()
{
	if (ImGui::Begin("Tests"))
	{
	}
	ImGui::End();
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1366, 768, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	ImGui::StyleColorsDark();

	AtGfx::GraphicsDevice* graphicsDevice = AtGfx::GraphicsDevice::Create(AtGfx::GraphicsAPI::OpenGL, {
		.GLGetAddressProc = (void* (*)(const char* name))glfwGetProcAddress,
		.MessageCallback = AtGfxMessageCallback
		});
	graphicsDevice->Initialize();

	//Test* currentTest = new ClearColorTest(graphicsDevice);
	//Test* currentTest = new LearnOpenGL::HelloWindowTest(graphicsDevice);
	Test* currentTest = new LearnOpenGL::HelloTriangleP1(graphicsDevice);

	currentTest->Initialize();

	//AtGfx::Pipeline* pipeline = AtGfx::Pipeline::Create(graphicsDevice, {
	//    .VertexAttributeLayout = {
	//        { AtGfx::ShaderDataType::Float3, "POSITION" }
	//    }
	//});

	//float vertices[] = {
	//    -0.5f, -0.5f, 0.0f,
	//     0.5f, -0.5f, 0.0f,
	//     0.0f,  0.5f, 0.0f
	//};

	//AtGfx::Buffer* vertexBuffer = AtGfx::Buffer::Create(graphicsDevice, AtGfx::BufferSpecification::CreateVertexBufferSpecification(sizeof(vertices), AtGfx::BufferUsage::StaticDraw, vertices));

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		// should the test be responsible for clearing?
		//glClear(GL_COLOR_BUFFER_BIT);

		currentTest->Perform();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		RenderImGuiMenu();
		currentTest->ImGuiRender();

		ImGui::ShowDemoWindow();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//graphicsDevice->Draw(pipeline, vertexBuffer);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	currentTest->Deinitialize();

	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}
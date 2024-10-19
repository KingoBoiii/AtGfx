#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <AtGfx/GraphicsDevice.h>
#include <AtGfx/Shader.h>
#include <AtGfx/Pipeline.h>
#include <AtGfx/Buffer.h>

#include <stdio.h>

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
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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

    AtGfx::Pipeline* pipeline = AtGfx::Pipeline::Create(graphicsDevice, {
        .VertexAttributeLayout = {
            { AtGfx::ShaderDataType::Float3, "POSITION" }
        }
    });

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    AtGfx::Buffer* vertexBuffer = AtGfx::Buffer::Create(graphicsDevice, AtGfx::BufferSpecification::CreateVertexBufferSpecification(sizeof(vertices), AtGfx::BufferUsage::StaticDraw, vertices));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        graphicsDevice->Draw(pipeline, vertexBuffer);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}
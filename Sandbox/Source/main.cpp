#include <GLFW/glfw3.h>

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

        graphicsDevice->Draw(pipeline, vertexBuffer);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
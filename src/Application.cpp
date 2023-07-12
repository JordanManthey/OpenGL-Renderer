#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "tests/TestClearColor.h"
#include "tests/TestDynamicBatchRendering2D.h"
#include "tests/TestDiffuseLighting3D.h"

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(960, 540, "OpenGL Demo", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    /* Must init glew after window context is created */
    if (glewInit() != GLEW_OK)
        std::cout << "GLEW did not initialize!" << std::endl;
    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        Renderer renderer;
        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        test::Test* currentTest = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        testMenu->RegisterTest<test::TestDynamicBatchRendering2D>("Dynamic Batch Rendering 2D");
        testMenu->RegisterTest<test::TestDiffuseLighting3D>("Diffuse Lighting 3D");

        double prevTime = glfwGetTime();

        while (!glfwWindowShouldClose(window))
        {
            double deltaTime = glfwGetTime() - prevTime;
            prevTime = glfwGetTime();

            GLCall(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
            renderer.Clear();

            ImGui_ImplGlfwGL3_NewFrame();
            if (currentTest)
            {
                currentTest->OnUpdate(deltaTime);
                currentTest->OnRender(deltaTime);
                ImGui::Begin("Test");
                if (currentTest != testMenu && ImGui::Button("<-"))
                {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest->OnImGuiRender();
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        if (currentTest != testMenu)
            delete currentTest;
        delete testMenu;
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
#include "TestDiffuseLighting3D.h"
#include "Renderer.h"
#include "Vertex.h";
#include "ModelGeneration.h"

#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <Array>

namespace test {

    TestDiffuseLighting3D::TestDiffuseLighting3D()
        : m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1000.0f, 1000.0f)), 
          m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), 
          m_PyramidPosition{ 0.0f, 0.0f, 0.0f },
          m_GlobalTranslation{ 470.0f, 150.0f, 0.0f }
	{

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_VAO = std::make_unique<VertexArray>();
        //m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices), GL_STATIC_DRAW);
        m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, sizeof(Vertex) * 1000, GL_DYNAMIC_DRAW);

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(4);
        layout.Push<float>(2);
        layout.Push<float>(1);
        layout.Push<float>(3);

        unsigned int pyramidIndices[18];
        unsigned int pyramidIndicesCount;
        GetPyramidIndices(pyramidIndices, pyramidIndicesCount);

        /*unsigned int cubeIndices[36];
        unsigned int cubeIndicesCount;
        GetCubeIndices(cubeIndices, cubeIndicesCount);*/

        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_IndexBuffer = std::make_unique<IndexBuffer>(nullptr, pyramidIndicesCount);

        m_Shader = std::make_unique<Shader>("res/shaders/Basic3D.shader");
        m_Shader->Bind();

        // lighting
        m_Shader->SetUniform4f("u_LightColor", 1.0f, 1.0f, 1.0f, 1.0f);
        m_Shader->SetUniform3f("u_LightPos", 200.0f, 100.0f, -100.0f);

        m_Texture0 = std::make_unique<Texture>("res/textures/MossyCobbleTexture_512.png");
        m_Texture1 = std::make_unique<Texture>("res/textures/SampleTexture_256.png");
        int textureSlots[2] = { 0, 1 };
        m_Shader->SetUniform1iv("u_Textures", 2, textureSlots);
	}

    TestDiffuseLighting3D::~TestDiffuseLighting3D()
	{
	}

    void TestDiffuseLighting3D::OnUpdate(double deltaTime)
    {
    }

	void TestDiffuseLighting3D::OnRender(double deltaTime)
    {
		GLCall(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        GLCall(glEnable(GL_DEPTH_TEST));

        /* Culling setup */
        //glFrontFace(GL_CW); // GL_CCW
        //GLCall(glEnable(GL_CULL_FACE));
        //GLCall(glCullFace(GL_BACK));

        Renderer renderer;

        m_Texture0->Bind(0);
        m_Texture1->Bind(1);

        {
            unsigned int indices[18];
            unsigned int indicesCount;
            GetPyramidIndices(indices, indicesCount);

            /*unsigned int indices[36];
            unsigned int indicesCount;
            GetCubeIndices(indices, indicesCount);*/

            m_IndexBuffer->UpdateData(indices, indicesCount);

            glm::vec3 convertedPyramidPosition(m_PyramidPosition[0], m_PyramidPosition[1], m_PyramidPosition[2]);
            std::array<Vertex, 16> pyramid = GetPyramidVertices(convertedPyramidPosition, 100);

            Vertex vertices[16];
            memcpy(vertices, pyramid.data(), pyramid.size() * sizeof(Vertex));

            /*std::array<Vertex, 8> cube = GetCubeVertices(glm::vec3(0, 0, 0), 100);
            Vertex vertices[8];
            memcpy(vertices, cube.data(), cube.size() * sizeof(Vertex));*/

            m_VAO->UpdateBufferData(sizeof(vertices), vertices);
            glm::vec3 convertedGlobalTranslation(m_GlobalTranslation[0], m_GlobalTranslation[1], m_GlobalTranslation[2]);
            glm::mat4 model = glm::translate(glm::mat4(1.0f), convertedGlobalTranslation);
            
            // Try to rotate only pyramid?
            model = glm::rotate(model, m_GlobalRotation, glm::vec3(0, 1, 0));
            m_GlobalRotation += m_RotationRate * deltaTime;

            glm::mat4 pvm = m_Proj * m_View * model;

            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_Model", model);
            m_Shader->SetUniformMat4f("u_View", m_View);
            m_Shader->SetUniformMat4f("u_Projection", m_Proj);
            //m_Shader->SetUniformMat4f("u_PVM", pvm);

            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }

        {
            /*unsigned int indices[36];
            unsigned int indicesCount;
            GetCubeIndices(indices, indicesCount);

            m_IndexBuffer->UpdateData(indices, indicesCount);

            auto cube = GetCubeVertices(glm::vec3(200, 0, 0), 200);
            Vertex vertices[8];
            memcpy(vertices, cube.data(), cube.size() * sizeof(Vertex));
            m_VAO->UpdateBufferData(sizeof(vertices), vertices);

            glm::vec3 convertedGlobalTranslation = glm::vec3(m_GlobalTranslation[0], m_GlobalTranslation[1], 0);
            glm::mat4 model = glm::translate(glm::mat4(1.0f), convertedGlobalTranslation);

            model = glm::rotate(model, m_GlobalRotation, glm::vec3(0, 1, 0));
            m_GlobalRotation += m_RotationRate * deltaTime;

            glm::mat4 mvp = m_Proj * m_View * model;

            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);*/
        }
	}

	void TestDiffuseLighting3D::OnImGuiRender()
	{
        ImGui::DragFloat3("Cube Position", m_PyramidPosition, 1.0f);
        ImGui::DragFloat3("Global Translation", m_GlobalTranslation, 1.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}
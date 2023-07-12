#include "TestDynamicBatchRendering2D.h"
#include "Renderer.h"
#include "Vertex.h";
#include "ModelGeneration.h"

#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <Array>

namespace test {

    TestDynamicBatchRendering2D::TestDynamicBatchRendering2D()
        : m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)), 
          m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), 
          m_QuadPositionA{ 150.0f, 150.0f },
          m_QuadPositionB{ 350.0f, 150.0f },
          m_GlobalTranslation{ 0.0f, 0.0f }
	{

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        GLCall(glDisable(GL_DEPTH_TEST));

        m_VAO = std::make_unique<VertexArray>();
        //m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices), GL_STATIC_DRAW);
        m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, sizeof(Vertex) * 1000, GL_DYNAMIC_DRAW);

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(4);
        layout.Push<float>(2);
        layout.Push<float>(1);
        layout.Push<float>(3);

        unsigned int indices[12];
        unsigned int indicesCount;
        GetQuadIndices(indices, indicesCount);

        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, indicesCount);

        m_Shader = std::make_unique<Shader>("res/shaders/Basic2D.shader");
        m_Shader->Bind();
        //m_Shader->SetUniform4f("u_Color", 0.9f, 0.3f, 0.8f, 1.0f);

        m_Texture0 = std::make_unique<Texture>("res/textures/MarioTexture.png");
        m_Texture1 = std::make_unique<Texture>("res/textures/LuigiTexture.png");
        int textureSlots[2] = { 0, 1 };
        m_Shader->SetUniform1iv("u_Textures", 2, textureSlots);
	}

    TestDynamicBatchRendering2D::~TestDynamicBatchRendering2D()
	{
	}

    void TestDynamicBatchRendering2D::OnUpdate(double deltaTime)
    {
    }

	void TestDynamicBatchRendering2D::OnRender(double deltaTime)
    {
        auto q0 = GetQuadVertices(m_QuadPositionA[0], m_QuadPositionA[1], 100.0f, 0);
        auto q1 = GetQuadVertices(m_QuadPositionB[0], m_QuadPositionB[1], 200.0f, 1);
        Vertex vertices[8];
        memcpy(vertices, q0.data(), q0.size() * sizeof(Vertex));
        memcpy(vertices + q0.size(), q1.data(), q1.size() * sizeof(Vertex));
        m_VAO->UpdateBufferData(sizeof(vertices), vertices);

		GLCall(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        m_Texture0->Bind(0);
        m_Texture1->Bind(1);

        {
            glm::vec3 convertedGlobalTranslation = glm::vec3(m_GlobalTranslation[0], m_GlobalTranslation[1], 0);
            glm::mat4 model = glm::translate(glm::mat4(1.0f), convertedGlobalTranslation);
            glm::mat4 pvm = m_Proj * m_View * model;
            
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_PVM", pvm);

            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }

        {
            /*glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);*/
        }
	}

	void TestDynamicBatchRendering2D::OnImGuiRender()
	{
        ImGui::DragFloat2("Quad_A Position", m_QuadPositionA, 1.0f);
        ImGui::DragFloat2("Quad_B Position", m_QuadPositionB, 1.0f);
        ImGui::DragFloat2("Global Translation", m_GlobalTranslation, 1.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}
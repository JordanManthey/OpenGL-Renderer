#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <memory>

namespace test {

	class TestDiffuseLighting3D : public Test
	{
	public:
		TestDiffuseLighting3D();
		~TestDiffuseLighting3D();

		void OnUpdate(double deltaTime) override;
		void OnRender(double deltaTime) override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr <IndexBuffer> m_IndexBuffer;
		std::unique_ptr <VertexBuffer> m_VertexBuffer;
		std::unique_ptr <Shader> m_Shader;
		std::unique_ptr <Texture> m_Texture0;
		std::unique_ptr <Texture> m_Texture1;

		glm::mat4 m_Proj, m_View;
		float m_GlobalTranslation[3];
		float m_PyramidPosition[3];
		float m_GlobalRotation = 0;
		float m_RotationRate = 1.0f;
	};
}



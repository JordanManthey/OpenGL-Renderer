#pragma once

#include "Test.h"

namespace test {

	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(double deltaTime) override;
		void OnRender(double deltaTime) override;
		void OnImGuiRender() override;
	private:
		float m_ClearColor[4];
	};
}



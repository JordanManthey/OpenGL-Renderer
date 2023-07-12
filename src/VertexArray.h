#pragma once

#include "VertexBuffer.h"
#include "Vertex.h"

class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void UpdateBufferData(unsigned int size, const void* data) const;

	void Bind() const;
	void Unbind() const;
};

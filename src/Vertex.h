#pragma once

#include "glm/glm.hpp"

struct Vertex
{
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TexCoords;
    float TexSlot;
    glm::vec3 Normal = glm::vec3(0.0f, 0.0f, 0.0f);
};
#pragma once

#include "Vertex.h"
#include <array>

/* 
Primitive model generation functions that return the vertices and indices in a pair. 
*/

static std::array<Vertex, 4> GetQuadVertices(float x, float y, float size, float textureSlot)
{
    Vertex v0;
    v0.Position = glm::vec3(x, y, 0.0f);
    v0.Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    v0.TexCoords = glm::vec2(0.0f, 0.0f);
    v0.TexSlot = textureSlot;

    Vertex v1;
    v1.Position = glm::vec3(x + size, y, 0.0f);
    v1.Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    v1.TexCoords = glm::vec2(1.0f, 0.0f);
    v1.TexSlot = textureSlot;

    Vertex v2;
    v2.Position = glm::vec3(x + size, y + size, 0.0f);
    v2.Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    v2.TexCoords = glm::vec2(1.0f, 1.0f);
    v2.TexSlot = textureSlot;

    Vertex v3;
    v3.Position = glm::vec3(x, y + size, 0.0f);
    v3.Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    v3.TexCoords = glm::vec2(0.0f, 1.0f);
    v3.TexSlot = textureSlot;

    return { v0, v1, v2, v3 };
};

static void GetQuadIndices(unsigned int (&indicesOut)[12], unsigned int& countOut)
{
    unsigned int indices[12] = {
            0, 1, 2,
            2, 3, 0,

            4, 5, 6,
            6, 7, 4
    };

    memcpy(indicesOut, indices, sizeof(indices));
    countOut = 12;
    return;
}

static std::array<Vertex, 8> GetCubeVertices(glm::vec3 position, float size)
{
    // F1
    Vertex v0;
    v0.Position = position;
    v0.Color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    v0.TexCoords = glm::vec2(0.0f, 0.0f);
    v0.TexSlot = 0;

    Vertex v1;
    v1.Position = glm::vec3(position.x, position.y + size, position.z);
    v1.Color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    v1.TexCoords = glm::vec2(0.0f, 1.0f);
    v1.TexSlot = 0;

    Vertex v2;
    v2.Position = glm::vec3(position.x + size, position.y + size, position.z);
    v2.Color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    v2.TexCoords = glm::vec2(1.0f, 1.0f);
    v2.TexSlot = 0;

    Vertex v3;
    v3.Position = glm::vec3(position.x + size, position.y, position.z);
    v3.Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    v3.TexCoords = glm::vec2(1.0f, 0.0f);
    v3.TexSlot = 0;

    // F2
    Vertex v4;
    v4.Position = glm::vec3(position.x + size, position.y, position.z + size);
    v4.Color = glm::vec4(0.0f, 1.0f, 0.5f, 1.0f);
    v4.TexCoords = glm::vec2(0.0f, 0.0f);
    v4.TexSlot = 0;

    Vertex v5;
    v5.Position = glm::vec3(position.x + size, position.y + size, position.z + size);
    v5.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    v5.TexCoords = glm::vec2(0.0f, 1.0f);
    v5.TexSlot = 0;

    Vertex v6;
    v6.Position = glm::vec3(position.x, position.y + size, position.z + size);
    v6.Color = glm::vec4(0.0f, 0.5f, 1.0f, 1.0f);
    v6.TexCoords = glm::vec2(1.0f, 1.0f);
    v6.TexSlot = 0;

    Vertex v7;
    v7.Position = glm::vec3(position.x, position.y, position.z + size);
    v7.Color = glm::vec4(1.0f, 0.25f, 0.25f, 1.0f);
    v7.TexCoords = glm::vec2(1.0f, 0.0f);
    v7.TexSlot = 0;

    return { v0, v1, v2, v3, v4, v5, v6, v7 };

};

static void GetCubeIndices(unsigned int (&indicesOut)[36], unsigned int& countOut)
{
    unsigned int indices[36] = {
        //front
        0,1,2,
        2,3,0,
        //back
        4,5,6,
        6,7,4,
        //top
        1,6,5,
        5,2,1,
        //bottom
        7,0,3,
        3,4,7,
        //right
        3,2,5,
        5,4,3,
        //left
        7,6,1,
        1,0,7
    };

    memcpy(indicesOut, indices, sizeof(indices));
    countOut = 36;
    return;
}

static std::array<Vertex, 16> GetPyramidVertices(glm::vec3 position, float size)
{
    // Bottom
    Vertex v0;
    v0.Position = glm::vec3(position.x - size, position.y, position.z + size);
    v0.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    v0.TexCoords = glm::vec2(0.0f, 0.0f);
    v0.TexSlot = 0;
    v0.Normal = glm::vec3(0.0f, -1.0f, 0.0f);

    Vertex v1;
    v1.Position = glm::vec3(position.x - size, position.y, position.z - size);
    v1.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    v1.TexCoords = glm::vec2(0.0f, 1.0f);
    v1.TexSlot = 0;
    v1.Normal = glm::vec3(0.0f, -1.0f, 0.0f);

    Vertex v2;
    v2.Position = glm::vec3(position.x + size, position.y, position.z - size);
    v2.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    v2.TexCoords = glm::vec2(1.0f, 1.0f);
    v2.TexSlot = 0;
    v2.Normal = glm::vec3(0.0f, -1.0f, 0.0f);

    Vertex v3;
    v3.Position = glm::vec3(position.x + size, position.y, position.z + size);
    v3.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    v3.TexCoords = glm::vec2(1.0f, 0.0f);
    v3.TexSlot = 0;
    v3.Normal = glm::vec3(0.0f, -1.0f, 0.0f);

    // Left
    Vertex v4;
    v4.Position = glm::vec3(position.x - size, position.y, position.z + size);
    v4.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    v4.TexCoords = glm::vec2(0.0f, 0.0f);
    v4.TexSlot = 0;
    v4.Normal = glm::vec3(-0.8f, 0.5f, 0.0f);

    Vertex v5;
    v5.Position = glm::vec3(position.x - size, position.y, position.z - size);
    v5.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    v5.TexCoords = glm::vec2(1.0f, 0.0f);
    v5.TexSlot = 0;
    v5.Normal = glm::vec3(-0.8f, 0.5f, 0.0f);

    Vertex v6;
    v6.Position = glm::vec3(position.x, position.y + (1.75 * size), position.z);
    v6.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    v6.TexCoords = glm::vec2(0.5f, 1.0f);
    v6.TexSlot = 0;
    v6.Normal = glm::vec3(-0.8f, 0.5f, 0.0f);
    
    // Non-facing
    Vertex v7;
    v7.Position = glm::vec3(position.x - size, position.y, position.z - size);
    v7.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    v7.TexCoords = glm::vec2(1.0f, 0.0f);
    v7.TexSlot = 0;
    v7.Normal = glm::vec3(0.0f, 0.5f, -0.8f);

    Vertex v8;
    v8.Position = glm::vec3(position.x + size, position.y, position.z - size);
    v8.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    v8.TexCoords = glm::vec2(0.0f, 0.0f);
    v8.TexSlot = 0;
    v8.Normal = glm::vec3(0.0f, 0.5f, -0.8f);

    Vertex v9;
    v9.Position = glm::vec3(position.x, position.y + (1.75 * size), position.z);
    v9.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    v9.TexCoords = glm::vec2(0.5f, 1.0f);
    v9.TexSlot = 0;
    v9.Normal = glm::vec3(0.0f, 0.5f, -0.8f);

    // Right
    Vertex v10;
    v10.Position = glm::vec3(position.x + size, position.y, position.z - size);
    v10.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    v10.TexCoords = glm::vec2(0.0f, 0.0f);
    v10.TexSlot = 0;
    v10.Normal = glm::vec3(0.8f, 0.5f, 0.0f);

    Vertex v11;
    v11.Position = glm::vec3(position.x + size, position.y, position.z + size);
    v11.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    v11.TexCoords = glm::vec2(1.0f, 0.0f);
    v11.TexSlot = 0;
    v11.Normal = glm::vec3(0.8f, 0.5f, 0.0f);

    Vertex v12;
    v12.Position = glm::vec3(position.x, position.y + (1.75 * size), position.z);
    v12.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    v12.TexCoords = glm::vec2(0.5f, 1.0f);
    v12.TexSlot = 0;
    v12.Normal = glm::vec3(0.8f, 0.5f, 0.0f);

    // Facing
    Vertex v13;
    v13.Position = glm::vec3(position.x + size, position.y, position.z + size);
    v13.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    v13.TexCoords = glm::vec2(1.0f, 0.0f);
    v13.TexSlot = 0;
    v13.Normal = glm::vec3(0.0f, 0.5f, 0.8f);

    Vertex v14;
    v14.Position = glm::vec3(position.x - size, position.y, position.z + size);
    v14.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    v14.TexCoords = glm::vec2(0.0f, 0.0f);
    v14.TexSlot = 0;
    v14.Normal = glm::vec3(0.0f, 0.5f, 0.8f);

    Vertex v15;
    v15.Position = glm::vec3(position.x, position.y + (1.75 * size), position.z);
    v15.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    v15.TexCoords = glm::vec2(0.5f, 1.0f);
    v15.TexSlot = 0;
    v15.Normal = glm::vec3(0.0f, 0.5f, 0.8f);

    return { v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15 };
};

static void GetPyramidIndices(unsigned int (&indicesOut)[18], unsigned int& countOut)
{
    unsigned int indices[18] = {
        0, 1, 2,     // bottom
        0, 2, 3,     // bottom
        4, 6, 5,     // left
        7, 9, 8,     // non-facing
        10, 12, 11,  // right
        13, 15, 14   // facing
    };

    memcpy(indicesOut, indices, sizeof(indices));
    countOut = 18;
    return;
}

//static std::array<Vertex, 5> GetPyramidVertices(glm::vec3 position, float size)
//{
//    Vertex v0;
//    v0.Position = glm::vec3(position.x - size, position.y, position.z + size);
//    v0.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
//    v0.TexCoords = glm::vec2(0.0f, 0.0f);
//    v0.TexSlot = 0;
//    //v0.Normal = glm::vec3(0.0f, -1.0f, 0.0f);
//
//    Vertex v1;
//    v1.Position = glm::vec3(position.x - size, position.y, position.z - size);
//    v1.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
//    v1.TexCoords = glm::vec2(1.0f, 0.0f);
//    v1.TexSlot = 0;
//    //v1.Normal = glm::vec3(0.0f, -1.0f, 0.0f);
//
//    Vertex v2;
//    v2.Position = glm::vec3(position.x + size, position.y, position.z - size);
//    v2.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
//    v2.TexCoords = glm::vec2(0.0f, 0.0f);
//    v2.TexSlot = 0;
//    //v2.Normal = glm::vec3(0.0f, -1.0f, 0.0f);
//
//    Vertex v3;
//    v3.Position = glm::vec3(position.x + size, position.y, position.z + size);
//    v3.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
//    v3.TexCoords = glm::vec2(1.0f, 0.0f);
//    v3.TexSlot = 0;
//    //v3.Normal = glm::vec3(0.0f, -1.0f, 0.0f);
//
//    Vertex v4;
//    v4.Position = glm::vec3(position.x, position.y + (1.75 * size), position.z);
//    v4.Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
//    v4.TexCoords = glm::vec2(0.5f, 1.0f);
//    v4.TexSlot = 0;
//    //v4.Normal = glm::vec3(-0.8f, 0.5f, 0.0f);
//
//    return { v0, v1, v2, v3, v4 };
//};
//
//static void GetPyramidIndices(unsigned int(&indicesOut)[18], unsigned int& countOut)
//{
//    unsigned int indices[18] = {
//        0, 1, 2,     // bottom
//        0, 2, 3,     // bottom
//        0, 1, 4,     // left
//        1, 2, 4,     // non-facing
//        2, 3, 4,     // right
//        3, 0, 4      // facing
//    };
//
//    memcpy(indicesOut, indices, sizeof(indices));
//    countOut = 18;
//    return;
//}
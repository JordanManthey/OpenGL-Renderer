#shader vertex
#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float texIndex;
layout(location = 4) in vec3 normal;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;

uniform mat4 u_PVM;

void main()
{
    gl_Position = u_PVM * vec4(position, 1.0f);
    v_Color = color;
    v_TexCoord = texCoord;
    v_TexIndex = texIndex;
}

#shader fragment
#version 450 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;

uniform vec4 u_Color;
uniform sampler2D u_Textures[2];

void main()
{ 
    int texIndex = int(v_TexIndex);
    color = texture(u_Textures[texIndex], v_TexCoord);
    //color = v_Color;
}
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
out vec3 v_Normal;
out vec3 v_CurrentPos;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;
//uniform mat4 u_PVM;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0f);
    //gl_Position = u_PVM * vec4(position, 1.0f);
    
    v_CurrentPos = vec3(u_Model * vec4(position, 1.0f));
    
    v_Color = color;
    v_TexCoord = texCoord;
    v_TexIndex = texIndex;
    v_Normal = normal;
}

#shader fragment
#version 450 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;
in vec3 v_Normal;
in vec3 v_CurrentPos;

uniform vec4 u_Color;
uniform sampler2D u_Textures[2];
uniform vec4 u_LightColor;
uniform vec3 u_LightPos;

void main()
{
    float ambient = 0.35f;
    
    vec3 normal = normalize(v_Normal);
    vec3 lightDirection = normalize(u_LightPos - v_CurrentPos);
    float diffuse = max(dot(normal, lightDirection), 0.0f);
    
    int texIndex = int(v_TexIndex);
    color = texture(u_Textures[texIndex], v_TexCoord) * u_LightColor * (diffuse + ambient);
    color.a = 1.0f;
    //color = v_Color;
}
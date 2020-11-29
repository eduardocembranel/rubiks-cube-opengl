#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 arcball;

out vec3 pos;
out vec3 normal;
out vec2 texCoord;

void main()
{
    pos = vec3(arcball * model * vec4(aPos, 1.0f));
    normal = mat3(transpose(inverse(arcball * model))) * aNormal;
    texCoord = aTexCoord;

    gl_Position = projection * view * arcball * model * vec4(aPos, 1.0f);  
}

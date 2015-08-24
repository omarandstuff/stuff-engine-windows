#version 330 core
layout(location = 0) in vec3 positionCoord;
layout(location = 1) in vec2 textureCoord;

out vec2 finalTextureCoord;

void main()
{
    gl_Position = vec4(positionCoord, 1.0);
    finalTextureCoord = textureCoord;
}

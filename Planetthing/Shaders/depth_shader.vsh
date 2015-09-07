#version 400
in vec4 positionCoord;

uniform mat4 modelMatrix;
uniform mat4 viewProjectionMatrix;

void main()
{
    gl_Position = viewProjectionMatrix * modelMatrix * positionCoord;
}
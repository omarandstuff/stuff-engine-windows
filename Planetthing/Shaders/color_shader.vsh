#version 400
in vec3 positionCoord;

uniform mat4 modelMatrix;
uniform mat4 viewProjectionMatrix;

void main()
{
    gl_Position = viewProjectionMatrix * modelMatrix * vec4(positionCoord, 1.0);
}
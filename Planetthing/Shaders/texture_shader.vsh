#version 400
in vec3 positionCoord;
in vec2 textureCoord;

uniform mat4 modelMatrix;
uniform mat4 viewProjectionMatrix;
uniform vec2 textureCompression;

out vec2 finalTextureCoord;

void main(void)
{
	// Calculate the position of the vertex against the world, view, and projection matrices.
    gl_Position = viewProjectionMatrix * modelMatrix * vec4(positionCoord, 1.0);

    // Store the texture coordinates for the pixel shader.
    finalTextureCoord = textureCoord * textureCompression;
}

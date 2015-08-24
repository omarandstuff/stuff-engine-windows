#version 400
in vec3 positionCoord;
in vec2 textureCoord;

out vec2 texCoord;

void main(void)
{
	// Calculate the position of the vertex against the world, view, and projection matrices.
	gl_Position = vec4(positionCoord, 1.0);

	// Store the texture coordinates for the pixel shader.
	texCoord = textureCoord;
}
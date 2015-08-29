#version 400
uniform sampler2D textureSampler;
uniform float opasity;

in vec2 finalTextureCoord;

out vec4 outputColor;

void main()
{
	vec4 textureColor;

	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColor = texture(textureSampler, finalTextureCoord);

	// Forced opasity
	textureColor.a *= opasity;

	outputColor = textureColor;
}

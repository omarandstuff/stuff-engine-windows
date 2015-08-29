uniform sampler2D textureSampler;
uniform float opasity;

in vec2 finalTextureCoord;

out vec4 finalColor;

void main()
{
    finalColor = texture2D(textureSampler, finalTextureCoord);
    finalColor.a *= opasity;
}

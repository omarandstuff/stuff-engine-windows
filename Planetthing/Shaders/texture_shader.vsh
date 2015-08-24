in vec3 positionCoord;
in vec2 textureCoord;

uniform mat4 modelViewProjectionMatrix;
uniform vec2 textureCompression;

out vec2 finalTextureCoord;

void main()
{
    gl_Position = modelViewProjectionMatrix * vec4(positionCoord, 1.0);
    finalTextureCoord = textureCoord * textureCompression;
}

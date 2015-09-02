#version 400
layout (location = 0) in vec3 positionCoord;
layout (location = 1) in vec2 textureCoord;
layout (location = 2) in vec3 normalCoord;

uniform mat4 modelViewProjectionMatrix;
uniform vec2 materialTextureCompression;
uniform mat4 lightModelViewProjectionMatrices[8];
uniform int numberOfLights;

out vec3 finalPositionCoord;
out vec2 finalTextureCoord;
out vec3 finalNormalCoord;

out vec3 finalPositionLightSpaceCoord[8];

void main()
{
    gl_Position = modelViewProjectionMatrix * vec4(positionCoord, 1.0);
    finalPositionCoord = positionCoord;
    finalTextureCoord = textureCoord * materialTextureCompression;
    finalNormalCoord = normalCoord;

    // Calculate the light space position of this vertex.
    for(int i = 0; i < 1; i++)
    {
        vec4 lightPosCoord = lightModelViewProjectionMatrices[i] * vec4(positionCoord, 1.0);
        
        // perform perspective divide.
        finalPositionLightSpaceCoord[i] = lightPosCoord.xyz / lightPosCoord.w;
        
        // Transform to [0,1] range.
        finalPositionLightSpaceCoord[i] = finalPositionLightSpaceCoord[i] * 0.5 + 0.5;
    }
}

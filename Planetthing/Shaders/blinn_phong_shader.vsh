#version 400
layout (location = 0) in vec3 positionCoord;
layout (location = 1) in vec2 textureCoord;
layout (location = 2) in vec3 normalCoord;

uniform mat4 modelMatrix;
uniform mat4 viewProjectionMatrix;
uniform mat4 normalMatrix;
uniform vec2 materialTextureCompression;
uniform mat4 lightViewProjectionMatrices[8];
uniform int numberOfLights;

out vec3 finalPositionCoord;
out vec2 finalTextureCoord;
out vec3 finalNormalCoord;

out vec3 finalPositionLightSpaceCoord[8];

void main()
{
    gl_Position = viewProjectionMatrix * modelMatrix * vec4(positionCoord, 1.0);
    finalPositionCoord = (modelMatrix * vec4(positionCoord, 1.0f)).xyz;
    finalTextureCoord = textureCoord * materialTextureCompression;
    finalNormalCoord = (normalMatrix * vec4(normalCoord, 1.0)).xyz;

    // Calculate the light space position of this vertex.
    for(int i = 0; i < 1; i++)
    {
        vec4 lightPosCoord = lightViewProjectionMatrices[i] * modelMatrix * vec4(positionCoord, 1.0);
        
        // perform perspective divide.
        finalPositionLightSpaceCoord[i] = lightPosCoord.xyz / lightPosCoord.w;
        
        // Transform to [0,1] range.
        finalPositionLightSpaceCoord[i] = finalPositionLightSpaceCoord[i] * 0.5 + 0.5;
    }
}

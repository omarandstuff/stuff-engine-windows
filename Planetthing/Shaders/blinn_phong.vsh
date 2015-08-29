in vec3 positionCoord;
in vec2 textureCoord;
in vec3 normalCoord;

uniform mat4 modelViewProjectionMatrix;
uniform vec2 materialTextureCompression;

out vec3 finalPositionCoord;
out vec2 finalTextureCoord;
out vec3 finalNormalCoord;

out vec3 finalPositionLightSpaceCoord[8];

out mat4 lightModelViewProjectionMatrices[8];
out int numberOfVertexLights;

void main()
{
    gl_Position = modelViewProjectionMatrix * vec4(positionCoord, 1.0);
    finalPositionCoord = positionCoord;
    finalTextureCoord = textureCoord * materialTextureCompression;
    finalNormalCoord = normalCoord;
    
    // Calculate the light space position of this vertex.
    for(int i = 0; i < numberOfVertexLights; i++)
    {
        vec4 lightPosCoord = lightModelViewProjectionMatrices[i] * vec4(positionCoord, 1.0);
        
        // perform perspective divide.
        finalPositionLightSpaceCoord[i] = lightPosCoord.xyz / lightPosCoord.w;
        
        // Transform to [0,1] range.
        finalPositionLightSpaceCoord[i] = finalPositionLightSpaceCoord[i] * 0.5 + 0.5;
    }
    
}

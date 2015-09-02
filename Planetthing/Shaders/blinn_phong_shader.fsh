#version 400
in vec3 finalPositionCoord;
in vec2 finalTextureCoord;
in vec3 finalNormalCoord;
in vec3 finalPositionLightSpaceCoord[8];

uniform sampler2D materialDiffuceMapSampler;
uniform bool materialDiffuceMapEnabled;
uniform sampler2D materialSpecularMapSampler;
uniform bool materialSpecularMapEnabled;
uniform vec3 materialDiffuceColor;
uniform vec3 materialAmbientColor;
uniform vec3 materialSpecularColor;
uniform float materialShininess;
uniform float materialOpasity;

struct Light
{
    int type;
    vec3 position;
    vec3 direction;
    float cutOff;
    vec3 diffuseColor;
    vec3 ambientColor;
    vec3 specularColor;
    float intensity;
    sampler2D shadowMapSampler;
    bool shadowsEnabled;
    float shadowMapTextelSize;
};

uniform Light lights[8];
uniform int numberOfLights;

out vec4 outputColor;

void main()
{
    // Final color combining lights and shadows.
    vec3 finalColor = vec3(0.0);
    vec3 perLightColor;
    
    // Material properties.
    vec3 surfaceColor;
    float surfaceOpasity = 1.0;
    vec3 surfaceSpecular;
    
    // Light calculations.
    vec3 normal;
    vec3 viewDir;
    vec3 lightDir;
    float lightFace = 0.0;
    vec3 diffuse = vec3(0.0);
    vec3 ambient = vec3(0.0);
    vec3 specular = vec3(0.0);
    float spec;
    vec3 reflectDir;
    float shadow;
    float normalDir;
    
    
    // Surfice color from sampling the diffuse texture or taking the diffuce color.
    if(materialDiffuceMapEnabled)
    {
        surfaceColor = texture(materialDiffuceMapSampler, finalTextureCoord).rgb;
        surfaceOpasity = texture(materialDiffuceMapSampler, finalTextureCoord).a;
    }
    else
        surfaceColor = materialDiffuceColor;
    
    // Specular surface factor.
    if(materialSpecularMapEnabled)
        surfaceSpecular = texture(materialSpecularMapSampler, finalTextureCoord).rgb;
    else
        surfaceSpecular = materialSpecularColor;

    // Normal vector for this fragment.
    normal = normalize(finalNormalCoord);
    
    // View vector for this fragment.
    viewDir = normalize(vec3(0.0, 90.0, 120.0) - finalPositionCoord);

        // Calculate the contribution of every light.
    for(int i = 0; i < 1; i++)
    {
        // Calculate the light to surfice direction.
        if(lights[i].type == 0) // Directional light.
            lightDir = normalize(lights[i].position);
        else
            lightDir = normalize(lights[i].position - finalPositionCoord);

        // Ambient contribution of this light.
        ambient += lights[i].ambientColor;
        
        // Normal light direction vector.
        normalDir = dot(normal, lightDir);
        
        shadow = 0.0;
        
        // Shadow calculations.
        if(lights[i].shadowsEnabled)
        {
            // Keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
            if(finalPositionLightSpaceCoord[i].z > 1.0)
                shadow = 0.0;
            else
            {
                // Get depth of current fragment from light's perspective.
                float currentDepth = finalPositionLightSpaceCoord[i].z;
                
                // Check whether current frag pos is in shadow.
                float bias = max(0.001 * (1.0 - normalDir), 0.001);
                
                for(int x = -2; x <= 2; x++)
                {
                    for(int y = -2; y <= 2; y++)
                    {
                        float pcfDepth = texture(lights[i].shadowMapSampler, finalPositionLightSpaceCoord[i].xy + vec2(x, y) * lights[i].shadowMapTextelSize).r;
                        shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
                    }
                }
                shadow /= 16.0;
            }
        }
        
        // How much the fragment is facing the light
        lightFace += max(normalDir, 0.0);
        
        // Spot Light.
        if(lights[i].type == 2)
        {
            float theta = dot(lightDir, normalize(lights[i].position));
            if(theta < lights[i].cutOff)
                continue;
        }
        
        // This light can be not calculated.
        if(lightFace == 0.0)
            continue;
        
        // Diffuce contribution base color light and facing.
        diffuse += lights[i].diffuseColor * lightFace * (1.0 - shadow);
        
        // Specular color base camera and light positions.
        highp vec3 halfwayDir = normalize(lightDir + viewDir);
        reflectDir = reflect(-lightDir, normal);
        specular += lights[i].specularColor * pow(max(dot(normal, halfwayDir), 0.0), materialShininess);
    }

    // Final ambient color.
    ambient *= materialAmbientColor * surfaceColor;
    
    // Final diffuce color.
    diffuse *= surfaceColor;
    
    // Final specular color.
    specular *= surfaceSpecular;
    
    outputColor = vec4(ambient + diffuse + specular, surfaceOpasity);
}

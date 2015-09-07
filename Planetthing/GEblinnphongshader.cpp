#include "GEblinnphongshader.h"

// ------------------------------------------------------------------------------ //
// -----------------------------  Singleton - Set up ---------------------------- //
// ------------------------------------------------------------------------------ //

GEBlinnPhongShader* GEBlinnPhongShader::sharedInstance()
{
	static GEBlinnPhongShader sharedInstance;

	return &sharedInstance;
}

void GEBlinnPhongShader::setUpSahder()
{
	// Get uniform locations.
	m_uniforms[GE_UNIFORM_MODEL_MATRIX] = glGetUniformLocation(m_programID, "modelMatrix");
	m_uniforms[GE_UNIFORM_VIEWPROJECTION_MATRIX] = glGetUniformLocation(m_programID, "viewProjectionMatrix");
	m_uniforms[GE_UNIFORM_NORMAL_MATRIX] = glGetUniformLocation(m_programID, "normalMatrix");
	m_uniforms[GE_UNIFORM_MATERIAL_TEXTURE_COMPRESSION] = glGetUniformLocation(m_programID, "materialTextureCompression");
	m_uniforms[GE_UNIFORM_MATERIAL_DIFFUSE_MAP] = glGetUniformLocation(m_programID, "materialDiffuceMapSampler");
	m_uniforms[GE_UNIFORM_MATERIAL_DIFFUSE_MAP_ENABLED] = glGetUniformLocation(m_programID, "materialDiffuceMapEnabled");
	m_uniforms[GE_UNIFORM_MATERIAL_SPECULAR_MAP] = glGetUniformLocation(m_programID, "materialSpecularMapSampler");
	m_uniforms[GE_UNIFORM_MATERIAL_SPECULAR_MAP_ENABLED] = glGetUniformLocation(m_programID, "materialSpecularMapEnabled");
	m_uniforms[GE_UNIFORM_MATERIAL_DIFFUSE_COLOR] = glGetUniformLocation(m_programID, "materialDiffuceColor");
	m_uniforms[GE_UNIFORM_MATERIAL_AMBIENT_COLOR] = glGetUniformLocation(m_programID, "materialAmbientColor");
	m_uniforms[GE_UNIFORM_MATERIAL_SPECULAR_COLOR] = glGetUniformLocation(m_programID, "materialSpecularColor");
	m_uniforms[GE_UNIFORM_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "materialShininess");
	m_uniforms[GE_UNIFORM_MATERIAL_OPASITY] = glGetUniformLocation(m_programID, "materialOpasity");

	// Uniform locations for all possible 10 lights.
	m_uniforms[GE_UNIFORM_NUMBER_OF_LIGHTS] = glGetUniformLocation(m_programID, "numberOfLights");
	for (int i = 0; i < 8; i++)
	{
		m_lightUniforms[i][GE_UNIFORM_LIGHT_TYPE] = glGetUniformLocation(m_programID, ("lights[" + to_string(i) + "].type").data());
		m_lightUniforms[i][GE_UNIFORM_LIGHT_POSITION] = glGetUniformLocation(m_programID, ("lights[" + to_string(i) + "].position").data());
		m_lightUniforms[i][GE_UNIFORM_LIGHT_DIRECTION] = glGetUniformLocation(m_programID, ("lights[" + to_string(i) + "].direction").data());
		m_lightUniforms[i][GE_UNIFORM_LIGHT_CUTOFF] = glGetUniformLocation(m_programID, ("lights[" + to_string(i) + "].cutOff").data());
		m_lightUniforms[i][GE_UNIFORM_LIGHT_DIFFUSE_COLOR] = glGetUniformLocation(m_programID, ("lights[" + to_string(i) + "].diffuseColor").data());
		m_lightUniforms[i][GE_UNIFORM_LIGHT_AMBIENT_COLOR] = glGetUniformLocation(m_programID, ("lights[" + to_string(i) + "].ambientColor").data());
		m_lightUniforms[i][GE_UNIFORM_LIGHT_SPECULAR_COLOR] = glGetUniformLocation(m_programID, ("lights[" + to_string(i) + "].specularColor").data());
		m_lightUniforms[i][GE_UNIFORM_LIGHT_SHADOW_MAP] = glGetUniformLocation(m_programID, ("lights[" + to_string(i) + "].shadowMapSampler").data());
		m_lightUniforms[i][GE_UNIFORM_LIGHT_SHADOWS_ENABLED] = glGetUniformLocation(m_programID, ("lights[" + to_string(i) + "].shadowsEnabled").data());
		m_lightUniforms[i][GE_UNIFORM_LIGHT_SHADOW_MAP_TEXTEL_SIZE] = glGetUniformLocation(m_programID, ("lights[" + to_string(i) + "].shadowMapTextelSize").data());
		m_lightUniforms[i][GE_UNIFORM_LIGHT_VIEWPROJECTION_MATRIX] = glGetUniformLocation(m_programID, ("lightViewProjectionMatrices[" + to_string(i) + "]").data());
	}
}

// ------------------------------------------------------------------------------ //
// ---------------------------------- Use Program ------------------------------- //
// ------------------------------------------------------------------------------ //

void GEBlinnPhongShader::useProgram()
{
	glUseProgram(m_programID);

	// In case there is not textures.
	glActiveTexture(0);

	// Number of textures;
	unsigned int m_textureNum = 0;

	// Set the Projection View Model and Normal matrices to the shader.
	glUniformMatrix4fv(m_uniforms[GE_UNIFORM_MODEL_MATRIX], 1, 0, &(*ModelMatrix)[0].x);
	glUniformMatrix4fv(m_uniforms[GE_UNIFORM_VIEWPROJECTION_MATRIX], 1, 0, &(*ViewProjectionMatrix)[0].x);
	glUniformMatrix4fv(m_uniforms[GE_UNIFORM_NORMAL_MATRIX], 1, 0, &(*NormalMatrix)[0].x);

	// Material texture compression.
	glUniform2fv(m_uniforms[GE_UNIFORM_MATERIAL_TEXTURE_COMPRESSION], 1, &Material->TextureCompression.x);

	// Material ambient color.
	glUniform3fv(m_uniforms[GE_UNIFORM_MATERIAL_AMBIENT_COLOR], 1, &Material->AmbientColor.x);

	// Materialshininess.
	glUniform1f(m_uniforms[GE_UNIFORM_MATERIAL_SHININESS], Material->Shininess);

	// Material diffuce based of existance of a texture.
	bool diffuceEnabled = Material->DiffuseMap != 0 && DiffuceMapEnabled;
	glUniform1i(m_uniforms[GE_UNIFORM_MATERIAL_DIFFUSE_MAP_ENABLED], diffuceEnabled);
	if (diffuceEnabled)
	{
		// Material diffuce texture.
		glActiveTexture(GL_TEXTURE0 + m_textureNum);
		glBindTexture(GL_TEXTURE_2D, Material->DiffuseMap->TextureID);
		glUniform1i(m_uniforms[GE_UNIFORM_MATERIAL_DIFFUSE_MAP], m_textureNum++);
	}
	else
	{
		// Material diffuce color.
		glUniform3fv(m_uniforms[GE_UNIFORM_MATERIAL_DIFFUSE_COLOR], 1, &Material->DiffuseColor.x);
	}

	// Material specular based of existence of a texture.
	bool specularEnabled = Material->SpecularMap != 0 && SpecularMapEnabled;
	glUniform1i(m_uniforms[GE_UNIFORM_MATERIAL_SPECULAR_MAP_ENABLED], specularEnabled);
	if (specularEnabled)
	{
		// Material specular texture.
		glActiveTexture(GL_TEXTURE0 + m_textureNum);
		glBindTexture(GL_TEXTURE_2D, Material->SpecularMap->TextureID);
		glUniform1i(m_uniforms[GE_UNIFORM_MATERIAL_SPECULAR_MAP], m_textureNum++);
	}
	else
	{
		// Material specular color.
		glUniform3fv(m_uniforms[GE_UNIFORM_MATERIAL_SPECULAR_COLOR], 1, &Material->SpecularColor.x);
	}

	// Lights.
	glUniform1i(m_uniforms[GE_UNIFORM_NUMBER_OF_LIGHTS], (GLint)Lights->size());
	for (vector<GELight*>::iterator light = Lights->begin(); light != Lights->end(); light++)
	{
		int index = light - Lights->begin();
		glUniform1i(m_lightUniforms[index][GE_UNIFORM_LIGHT_TYPE], (*light)->LightType);
		glUniform3fv(m_lightUniforms[index][GE_UNIFORM_LIGHT_POSITION], 1, &(*light)->Position.x);
		glm::vec3 auxVec3 = (*light)->Position - (*light)->Direction;
		glUniform3fv(m_lightUniforms[index][GE_UNIFORM_LIGHT_DIRECTION], 1, &auxVec3.x);
		glUniform1f(m_lightUniforms[index][GE_UNIFORM_LIGHT_CUTOFF], (*light)->CutOff);
		auxVec3 = (*light)->DiffuseColor * (*light)->Intensity;
		glUniform3fv(m_lightUniforms[index][GE_UNIFORM_LIGHT_DIFFUSE_COLOR], 1, &auxVec3.x);
		auxVec3 = (*light)->AmbientColor * (*light)->Ambient;
		glUniform3fv(m_lightUniforms[index][GE_UNIFORM_LIGHT_AMBIENT_COLOR], 1, &auxVec3.x);
		glUniform3fv(m_lightUniforms[index][GE_UNIFORM_LIGHT_SPECULAR_COLOR], 1, &(*light)->SpecularColor.x);
		glUniform1i(m_lightUniforms[index][GE_UNIFORM_LIGHT_SHADOWS_ENABLED], (*light)->CastShadows);
		glUniform1f(m_lightUniforms[index][GE_UNIFORM_LIGHT_SHADOW_MAP_TEXTEL_SIZE], 1.0f / (*light)->ShadowMapSize);

		glUniformMatrix4fv(m_lightUniforms[index][GE_UNIFORM_LIGHT_VIEWPROJECTION_MATRIX], 1, 0, &(*light)->ShadowMapViewProjectionMatrix[0].x);

		// Shadow map for this light.
		glActiveTexture(GL_TEXTURE0 + m_textureNum);
		glBindTexture(GL_TEXTURE_2D, (*light)->ShadowMapFBO->DepthTextureID);
		glUniform1i(m_lightUniforms[index][GE_UNIFORM_LIGHT_SHADOW_MAP], m_textureNum++);
	}
}

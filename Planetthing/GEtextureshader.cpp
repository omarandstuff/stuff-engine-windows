#include "GEtextureshader.h"

// ------------------------------------------------------------------------------ //
// -----------------------------  Singleton - Set up ---------------------------- //
// ------------------------------------------------------------------------------ //

GETextureShader* GETextureShader::sharedInstance()
{
	static GETextureShader sharedInstance;

	return &sharedInstance;
}

void GETextureShader::setUpSahder()
{
	// Get uniform locations.
	m_uniforms[GE_UNIFORM_MODEL_MATRIX] = glGetUniformLocation(m_programID, "modelMatrix");
	m_uniforms[GE_UNIFORM_VIEWPROJECTION_MATRIX] = glGetUniformLocation(m_programID, "ViewProjectionMatrix");
	m_uniforms[GE_UNIFORM_MATERIAL_TEXTURE_COMPRESSION] = glGetUniformLocation(m_programID, "textureCompression");
	m_uniforms[GE_UNIFORM_MATERIAL_DIFFUSE_MAP] = glGetUniformLocation(m_programID, "textureSampler");
	m_uniforms[GE_UNIFORM_MATERIAL_OPASITY] = glGetUniformLocation(m_programID, "opasity");
}

// ------------------------------------------------------------------------------ //
// ---------------------------------- Use Program ------------------------------- //
// ------------------------------------------------------------------------------ //

void GETextureShader::useProgram()
{
	glUseProgram(m_programID);

	// Set the Projection View Model Matrix to the shader.
	glUniformMatrix4fv(m_uniforms[GE_UNIFORM_MODEL_MATRIX], 1, 0, &(*ModelMatrix)[0].x);
	glUniformMatrix4fv(m_uniforms[GE_UNIFORM_VIEWPROJECTION_MATRIX], 1, 0, &(*ViewProjectionMatrix)[0].x);

	// Material texture compression.
	glUniform2fv(m_uniforms[GE_UNIFORM_MATERIAL_TEXTURE_COMPRESSION], 1, &Material->TextureCompression.x);

	// Opasity
	glUniform1f(m_uniforms[GE_UNIFORM_MATERIAL_OPASITY], Material->Opasity);

	// Material diffuce texture.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Material->DiffuseMap->TextureID);
	glUniform1i(m_uniforms[GE_UNIFORM_MATERIAL_DIFFUSE_MAP], 0);
}

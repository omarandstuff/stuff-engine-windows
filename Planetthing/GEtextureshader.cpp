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
	m_uniforms[GE_UNIFORM_MODELVIEWPROJECTION_MATRIX] = glGetUniformLocation(m_programID, "modelViewProjectionMatrix");
	m_uniforms[GE_UNIFORM_MATERIAL_TEXTURE_COMPRESSION] = glGetUniformLocation(m_programID, "materialTextureCompression");
	m_uniforms[GE_UNIFORM_MATERIAL_DIFFUSE_MAP] = glGetUniformLocation(m_programID, "materialDifficeMapSampler");
}

// ------------------------------------------------------------------------------ //
// ---------------------------------- Use Program ------------------------------- //
// ------------------------------------------------------------------------------ //

void GETextureShader::useProgram()
{
	glUseProgram(m_programID);

	// Set the Projection View Model Matrix to the shader.
	glUniformMatrix4fv(m_uniforms[GE_UNIFORM_MODELVIEWPROJECTION_MATRIX], 1, 0, &(*ModelViewProjectionMatrix)[0].x);

	// Material texture compression.
	glUniform2fv(m_uniforms[GE_UNIFORM_MATERIAL_TEXTURE_COMPRESSION], 1, &Material->TextureCompression.x);

	// Material diffuce texture.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Material->DiffuseMap->TextureID);
	glUniform1i(m_uniforms[GE_UNIFORM_MATERIAL_DIFFUSE_MAP], 0);
}

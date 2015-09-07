#include "GEdepthshader.h"

// ------------------------------------------------------------------------------ //
// -----------------------------  Singleton - Set up ---------------------------- //
// ------------------------------------------------------------------------------ //

GEDepthShader* GEDepthShader::sharedInstance()
{
	static GEDepthShader sharedInstance;

	return &sharedInstance;
}

void GEDepthShader::setUpSahder()
{
	// Get uniform locations.
	m_uniforms[GE_UNIFORM_MODEL_MATRIX] = glGetUniformLocation(m_programID, "modelMatrix");
	m_uniforms[GE_UNIFORM_VIEWPROJECTION_MATRIX] = glGetUniformLocation(m_programID, "viewProjectionMatrix");
}

// ------------------------------------------------------------------------------ //
// ---------------------------------- Use Program ------------------------------- //
// ------------------------------------------------------------------------------ //

void GEDepthShader::useProgram()
{
	glUseProgram(m_programID);

	// Set the Projection View Model Matrix to the shader.
	glUniformMatrix4fv(m_uniforms[GE_UNIFORM_MODEL_MATRIX], 1, 0, &(*ModelMatrix)[0].x);
	glUniformMatrix4fv(m_uniforms[GE_UNIFORM_VIEWPROJECTION_MATRIX], 1, 0, &(*ViewProjectionMatrix)[0].x);

	// No texture
	glActiveTexture(0);
}
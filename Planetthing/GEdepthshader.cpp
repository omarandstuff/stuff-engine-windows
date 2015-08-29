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
	m_uniforms[GE_UNIFORM_MODELVIEWPROJECTION_MATRIX] = glGetUniformLocation(m_programID, "modelViewProjectionMatrix");
}

// ------------------------------------------------------------------------------ //
// ---------------------------------- Use Program ------------------------------- //
// ------------------------------------------------------------------------------ //

void GEDepthShader::useProgram()
{
	glUseProgram(m_programID);

	// Set the Projection View Model Matrix to the shader.
	glUniformMatrix4fv(m_uniforms[GE_UNIFORM_MODELVIEWPROJECTION_MATRIX], 1, 0, &(*ModelViewProjectionMatrix)[0].x);

	// No texture
	glActiveTexture(0);
}
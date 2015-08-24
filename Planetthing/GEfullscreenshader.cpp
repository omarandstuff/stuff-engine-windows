#include "GEfullscreenshader.h"

// ------------------------------------------------------------------------------ //
// -----------------------------  Singleton - Set up ---------------------------- //
// ------------------------------------------------------------------------------ //

GEFullScreenShader* GEFullScreenShader::sharedInstance()
{
	static GEFullScreenShader sharedInstance;

	return &sharedInstance;
}

void GEFullScreenShader::setUpSahder()
{
	// Get uniform locations.
	uniforms[GE_UNIFORM_MATERIAL_DIFFUSE_MAP] = glGetUniformLocation(m_programID, "textureSampler");
}

// ------------------------------------------------------------------------------ //
// ---------------------------------- Use Program ------------------------------- //
// ------------------------------------------------------------------------------ //

void GEFullScreenShader::useProgram()
{
	glUseProgram(m_programID);

	// Set one texture to render and the current texture to render.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glUniform1i(uniforms[GE_UNIFORM_MATERIAL_DIFFUSE_MAP], 0);
}

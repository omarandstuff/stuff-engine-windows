#include "GEcolorshader.h"

// ------------------------------------------------------------------------------ //
// -----------------------------  Singleton - Set up ---------------------------- //
// ------------------------------------------------------------------------------ //

GEColorShader* GEColorShader::sharedInstance()
{
	static GEColorShader sharedInstance;

	return &sharedInstance;
}

void GEColorShader::setUpSahder()
{
	// Get uniform locations.
	m_uniforms[GE_UNIFORM_MODEL_MATRIX] = glGetUniformLocation(m_programID, "modelMatrix");
	m_uniforms[GE_UNIFORM_VIEWPROJECTION_MATRIX] = glGetUniformLocation(m_programID, "viewProjectionMatrix");
	m_uniforms[GE_UNIFORM_MATERIAL_DIFFUSE_COLOR] = glGetUniformLocation(m_programID, "diffuceColor");
}

// ------------------------------------------------------------------------------ //
// ---------------------------------- Use Program ------------------------------- //
// ------------------------------------------------------------------------------ //

void GEColorShader::useProgram()
{
	glUseProgram(m_programID);

	// Set the Projection View Model Matrix to the shader.
	glUniformMatrix4fv(m_uniforms[GE_UNIFORM_MODEL_MATRIX], 1, 0, &(*ModelMatrix)[0].x);
	glUniformMatrix4fv(m_uniforms[GE_UNIFORM_VIEWPROJECTION_MATRIX], 1, 0, &(*ViewProjectionMatrix)[0].x);

	// diffuce Color
	glm::vec4 color(Material->DiffuseColor, Material->Opasity);
	glUniform4fv(m_uniforms[GE_UNIFORM_MATERIAL_DIFFUSE_COLOR], 1, &color.r);

	// No texture.
	glActiveTexture(0);
}

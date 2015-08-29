#include "GEfbo.h"

// ------------------------------------------------------------------------------ //
// -------------------------------- Initialization ------------------------------ //
// ------------------------------------------------------------------------------ //

GEFBO::GEFBO()
{
}

GEFBO::GEFBO(GLsizei width, GLsizei height)
{
	generate(width, height);
}

GEFBO::~GEFBO()
{
}

// ------------------------------------------------------------------------------ //
// ---------------------------------- FBO Control ------------------------------- //
// ------------------------------------------------------------------------------ //

void GEFBO::generate(GLsizei width, GLsizei height)
{
	Width = width;
	Height = height;

	// Depth texture.
	glGenTextures(1, &DepthTextureID);
	glBindTexture(GL_TEXTURE_2D, DepthTextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, Width, Height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);

	// Generate the frame buffer.
	glGenFramebuffers(1, &FrameBufferID);

	// Bind that frame buffer.
	glBindFramebuffer(GL_FRAMEBUFFER, FrameBufferID);

	//Attach 2D texture to this FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, DepthTextureID, 0);

	// Check for completness.
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		return;
	}
}

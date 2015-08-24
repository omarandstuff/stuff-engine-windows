#include "GEfullscreen.h"

// ------------------------------------------------------------------------------ //
// -----------------------------  Singleton - Set up ---------------------------- //
// ------------------------------------------------------------------------------ //

GEFullScreen* GEFullScreen::sharedInstance()
{
	static GEFullScreen sharedInstance;

	return &sharedInstance;
}

void GEFullScreen::createFullScreenVO()
{
	GLfloat vertexBuffer[20] =
	{
		-1.0f,	 1.0f,	0.0f,	0.0f,	1.0f, // Top left
		 1.0f,	 1.0f,	0.0f,	1.0f,	1.0f, // Top right
		-1.0f,	-1.0f,	0.0f,	0.0f,	0.0f, // Bottom left
		 1.0f,	-1.0f,	0.0f,	1.0f,	0.0f  // Bottom right
	};

	unsigned int indexbuffer[6] =
	{
		2, 0, 3,
		0, 1, 3
	};

	// Generate a vertex array id that keep both the vertex buffer and the indexbiffer.
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Genreate the vertex buffer and fill it with the vertex buffer data.
	glGenBuffers(1, &m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (unsigned char*)NULL + (3 * sizeof(float)));

	// Generate the index buffer and fill it with the index buffer data.
	glGenBuffers(1, &m_indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexbuffer), indexbuffer, GL_STATIC_DRAW);

	// Unbind everything.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

// ------------------------------------------------------------------------------ //
// -----------------------------------  Render ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GEFullScreen::render()
{
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendEquation(GL_FUNC_ADD);
	glDisable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT_AND_BACK);

	// Full screen parameters.
	m_fullScreenShader->TextureID = TextureID;
	m_fullScreenShader->useProgram();

	// Bind the vertex array object that stored all the information about the vertex and index buffers.
	glBindVertexArray(m_vertexArrayID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}
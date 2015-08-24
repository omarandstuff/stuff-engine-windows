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
	GLfloat vertices[30] =
	{
		-1.0f,	-1.0f,	0.0f,	0.0f,	0.0f,
		-1.0f,	 1.0f,	0.0f,	0.0f,	1.0f,
		 1.0f,	-1.0f,	0.0f,	1.0f,	0.0f,
		-1.0f,	 1.0f,	0.0f,	0.0f,	1.0f,
		 1.0f,	 1.0f,	0.0f,	1.0f,	1.0f,
		 1.0f,	-1.0f,	0.0f,	1.0f,	0.0f
	};

	glGenVertexArrays(1, &m_vertexArrayId);
	glBindVertexArray(m_vertexArrayId);

	glGenBuffers(1, &m_vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Enable the three vertex array attributes.
	glEnableVertexAttribArray(0);  // Vertex position.
	glEnableVertexAttribArray(1);  // Texture coordinates.

	// Specify the location and format of the position portion of the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices), 0);

	// Specify the location and format of the texture coordinate portion of the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices), (unsigned char*)NULL + (3 * sizeof(float)));

	glBindVertexArray(0);
}

// ------------------------------------------------------------------------------ //
// -----------------------------------  Render ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GEFullScreen::render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);
	glDisable(GL_DEPTH_TEST);

	// Full screen parameters.
	//m_fullScreenShader.TextureID = TextureID;
	//[m_fullScreenShader useProgram];

	// Bind the vertex array object that stored all the information about the vertex and index buffers.
	glBindVertexArray(m_vertexArrayId);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	// Draw call.
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
#include "GEboundingbox.h"

// ------------------------------------------------------------------------------ //
// -----------------------------  Singleton - Set up ---------------------------- //
// ------------------------------------------------------------------------------ //

GEBoundingBox* GEBoundingBox::sharedInstance()
{
	static GEBoundingBox sharedInstance;

	return &sharedInstance;
}

// ------------------------------------------------------------------------------ //
// ----------------------------------- Render ----------------------------------- //
// ------------------------------------------------------------------------------ //

void GEBoundingBox::render()
{
	glBindVertexArray(m_vertexArrayID);

	glEnableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, NULL);
}

// ------------------------------------------------------------------------------ //
// -------------------------- Generate - Update Lines --------------------------- //
// ------------------------------------------------------------------------------ //

void GEBoundingBox::generateBoundingLines()
{
	// Create the dynamic vertex data and the static index data.
	float vertexBuffer[24] = {
		1.0f,  1.0f, 1.0f, // Right, Top, Back
		-1.0f,  1.0f, 1.0f, // Left, Top, Back
		1.0f, -1.0f, 1.0f, // Right, Bottom, Back
		-1.0f, -1.0f, 1.0f, // Left, Bottom, Back

		1.0f,  1.0f, -1.0f, // Right, Top, Front
		-1.0f,  1.0f, -1.0f, // Left, Top, Front
		1.0f, -1.0f, -1.0f, // Right, Bottom, Front
		-1.0f, -1.0f, -1.0f // Left, Bottom, Front
	};

	unsigned int indexbuffer[24] = {
		0, 1,
		1, 3,
		3, 2,
		2, 0,

		4, 5,
		5, 7,
		7, 6,
		6, 4,

		0, 4,
		1, 5,
		2, 6,
		3, 7
	};

	// Generate a vertex array id that keep both the vertex buffer and the indexbiffer.
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Genreate the vertex buffer and fill it with the dynamic data.
	glGenBuffers(1, &m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_DYNAMIC_DRAW);

	// Set the offset in the dynamic data that represent the vertex information.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	// Generate the index buffer and fill it with the static data.
	glGenBuffers(1, &m_indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexbuffer), indexbuffer, GL_STATIC_DRAW);

	// Unbind everything.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GEBoundingBox::updateBoundingLines(GEBound* bound)
{
	// Create the dynamic vertex data from bound.
	float vertexBuffer[24] = {
		bound->MaxBound.x, bound->MaxBound.y, bound->MaxBound.z, // Right, Top, Back
		bound->MinBound.x, bound->MaxBound.y, bound->MaxBound.z, // Left, Top, Back
		bound->MaxBound.x, bound->MinBound.y, bound->MaxBound.z, // Right, Bottom, Back
		bound->MinBound.x, bound->MinBound.y, bound->MaxBound.z, // Left, Bottom, Back

		bound->MaxBound.x, bound->MaxBound.y, bound->MinBound.z, // Right, Top, Front
		bound->MinBound.x, bound->MaxBound.y, bound->MinBound.z, // Left, Top, Front
		bound->MaxBound.x, bound->MinBound.y, bound->MinBound.z, // Right, Bottom, Front
		bound->MinBound.x, bound->MinBound.y, bound->MinBound.z  // Left, Bottom, Front
	};

	// Bind the vertex buffer and refill it with data.
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexBuffer), vertexBuffer);
}

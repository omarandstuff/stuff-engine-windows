#include "GEplane.h"

// ------------------------------------------------------------------------------ //
// ------------------------------- Initialization ------------------------------- //
// ------------------------------------------------------------------------------ //

GEPlane::GEPlane()
{
}

GEPlane::GEPlane(float width, float height, GE_DIRECTION direction, unsigned int segment_w, unsigned int segment_h)
{
	generate(width, height, direction, segment_w, segment_h);
}

GEPlane::~GEPlane()
{
}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Render ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GEPlane::render(GE_RENDER_MODE mode)
{
	// If it's not supouse to be visible don't render at all.
	if (!Visible) return;

	if (mode == GE_RENDER_MODE_NORMAL)
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_blinnPhongShader->Material = &Material;
		m_blinnPhongShader->useProgram();
	}
	else if (mode == GE_RENDER_MODE_DEPTH)
	{
		// Disable blend.
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		m_depthShader->useProgram();
	}

	glBindVertexArray(m_vertexArrayID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, NULL);
}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Load ------------------------------------ //
// ------------------------------------------------------------------------------ //

void GEPlane::generate(float width, float height, GE_DIRECTION direction, unsigned int segment_w, unsigned int segment_h)
{
	// Vertex and index count of mesh.
	m_vertexCount = (segment_w + 1) * (segment_h + 1) * 8;
	m_indexCount = segment_w * segment_h * 6;

	// Generate the data holders.
	m_vertexBuffer = new float[m_vertexCount];
	m_indexBuffer = new unsigned int[m_indexCount];

	// Size of every segment in the sides.
	float w_stride = width / segment_w;
	float h_stride = height / segment_h;

	// Where begin to calculate the vertices.
	float w_origin = -width / 2.0;
	float h_origin = -height / 2.0;

	// Calculate every vertex of the plane.
	for (int i = 0; i <= segment_h; i++)
	{
		for (int j = 0; j <= segment_w; j++)
		{
			int index = i * (segment_w + 1) + j;

			m_vertexBuffer[index * 8] = w_origin + w_stride * (float)j;
			m_vertexBuffer[index * 8 + 1] = 0.0f;
			m_vertexBuffer[index * 8 + 2] = h_origin + h_stride * (float)i;

			m_vertexBuffer[index * 8 + 3] = (w_stride * (float)j) / width;
			m_vertexBuffer[index * 8 + 4] = (h_stride * (float)i) / height;

			m_vertexBuffer[index * 8 + 5] = 0.0f;
			m_vertexBuffer[index * 8 + 6] = 1.0f;
			m_vertexBuffer[index * 8 + 7] = 0.0f;
		}
	}

	// Calculate every index of every triangle in the plane.
	for (int i = 0; i < segment_h; i++)
	{
		for (int j = 0; j < segment_w; j++)
		{
			int index = i * segment_w + j;

			m_indexBuffer[index * 6] = index * (segment_w + 1);
			m_indexBuffer[index * 6 + 1] = (index + 1) * (segment_w + 1);
			m_indexBuffer[index * 6 + 2] = index + 1;
			m_indexBuffer[index * 6 + 3] = (index + 1) * (segment_w + 1);
			m_indexBuffer[index * 6 + 4] = (index + 1) * (segment_w + 1) + 1;
			m_indexBuffer[index * 6 + 5] = index + 1;
		}
	}

	generateBuffers();
}

void GEPlane::generateBuffers()
{
	// Generate a vertex array id that keep both the vertex buffer and the indexbiffer.
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Genreate the vertex buffer and fill it with the dynamic data.
	glGenBuffers(1, &m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertexCount, m_vertexBuffer, GL_STATIC_DRAW);

	// Set the offset in the dynamic data that represent the vertex information.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);

	// Set the offset tn the dynamic data that represent the texture coordinates information.
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (unsigned char*)NULL + (3 * sizeof(float)));

	// Set the offset tn the dynamic data that represent the normal information.
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (unsigned char*)NULL + (5 * sizeof(float)));

	// Generate the index buffer and fill it with the static data.
	glGenBuffers(1, &m_indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indexCount, m_indexBuffer, GL_STATIC_DRAW);

	delete[] m_vertexBuffer;
	delete[] m_indexBuffer;

	// Unbind everything.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
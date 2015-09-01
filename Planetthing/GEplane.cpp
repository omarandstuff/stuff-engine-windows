#include "GEplane.h"

// ------------------------------------------------------------------------------ //
// ------------------------------- Initialization ------------------------------- //
// ------------------------------------------------------------------------------ //

GEPlane::GEPlane(float width, float height, unsigned int segment_w, unsigned int segment_h)
{
	generate(width, height, segment_w, segment_h);
}

GEPlane::~GEPlane()
{
}


// ------------------------------------------------------------------------------ //
// ------------------------------------ Load ------------------------------------ //
// ------------------------------------------------------------------------------ //

void GEPlane::generate(float width, float height, unsigned int segment_w, unsigned int segment_h)
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
	float w_origin = -width / 2.0f;
	float h_origin = -height / 2.0f;

	// Calculate every vertex of the plane.
	for (unsigned int i = 0; i <= segment_h; i++)
	{
		for (unsigned int j = 0; j <= segment_w; j++)
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
	for (unsigned int i = 0; i < segment_h; i++)
	{
		for (unsigned int j = 0; j < segment_w; j++)
		{
			int index = i * segment_w + j;

			m_indexBuffer[index * 6] = (segment_w + 1) * i + j;
			m_indexBuffer[index * 6 + 1] = (segment_w + 1) * (i + 1) + j;
			m_indexBuffer[index * 6 + 2] = (segment_w + 1) * (i + 1) + j + 1;
			m_indexBuffer[index * 6 + 3] = (segment_w + 1) * i + j;
			m_indexBuffer[index * 6 + 4] = (segment_w + 1) * (i + 1) + j + 1;
			m_indexBuffer[index * 6 + 5] = (segment_w + 1) * i + j + 1;
		}
	}

	generateBuffers();
}

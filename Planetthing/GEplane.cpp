#include "GEplane.h"

// ------------------------------------------------------------------------------ //
// ------------------------------- Initialization ------------------------------- //
// ------------------------------------------------------------------------------ //

GEPlane::GEPlane(float width, float height, unsigned int segments_w, unsigned int segments_h, float offsetOrigin, glm::vec3 direction)
{
	generate(width, height, segments_w, segments_h, offsetOrigin, direction);
}

GEPlane::~GEPlane()
{
}


// ------------------------------------------------------------------------------ //
// ------------------------------------ Load ------------------------------------ //
// ------------------------------------------------------------------------------ //

void GEPlane::generate(float width, float height, unsigned int segments_w, unsigned int segments_h, float offsetOrigin, glm::vec3 direction)
{
	// Vertex and index count of mesh.
	m_vertexCount = (segments_w + 1) * (segments_h + 1) * 8;
	m_indexCount = segments_w * segments_h * 6;

	// Generate the data holders.
	m_vertexBuffer = new float[m_vertexCount];
	m_indexBuffer = new unsigned int[m_indexCount];

	float wOrigin = 1.0f / 2.0f;
	float hOrigin = 1.0f / 2.0f;

	float wStride = 1.0f / segments_w;
	float hStride = 1.0f / segments_h;

	for (unsigned int i = 0; i <= segments_h; i++)
	{
		for (unsigned int j = 0; j <= segments_w; j++)
		{
			unsigned int index = (segments_w + 1) * i + j;

			if (direction.y != 0)
			{
				m_vertexBuffer[index * 8] = direction.y < 0.0f ? -wOrigin + wStride * j : wOrigin - wStride * j;
				m_vertexBuffer[index * 8 + 1] = offsetOrigin * direction.y;
				m_vertexBuffer[index * 8 + 2] = hOrigin - hStride * i;

				m_vertexBuffer[index * 8 + 3] = direction.y > 0.0f ? 1.0f - wStride * j / width : wStride * j / width;
				m_vertexBuffer[index * 8 + 4] = direction.y > 0.0f ? 1.0f - hStride * i / height : hStride * i / height;
			}
			else if (direction.x != 0)
			{
				m_vertexBuffer[index * 8] = offsetOrigin * direction.x;
				m_vertexBuffer[index * 8 + 1] = hOrigin - hStride * i;
				m_vertexBuffer[index * 8 + 2] = direction.x < 0.0f ? -wOrigin + wStride * j : wOrigin - wStride * j;

				m_vertexBuffer[index * 8 + 3] = wStride * j / width;
				m_vertexBuffer[index * 8 + 4] = hStride * i / height;
			}
			else if (direction.z != 0)
			{
				m_vertexBuffer[index * 8] = direction.z > 0.0f ? -wOrigin + wStride * j : wOrigin - wStride * j;
				m_vertexBuffer[index * 8 + 1] = hOrigin - hStride * i;
				m_vertexBuffer[index * 8 + 2] = offsetOrigin * direction.z;

				m_vertexBuffer[index * 8 + 3] = wStride * j / width;
				m_vertexBuffer[index * 8 + 4] = hStride * i / height;
			}

			m_vertexBuffer[index * 8 + 5] = direction.x;
			m_vertexBuffer[index * 8 + 6] = direction.y;
			m_vertexBuffer[index * 8 + 7] = direction.z;
		}
	}

	for (unsigned int i = 0; i < segments_h; i++)
	{
		for (unsigned int j = 0; j < segments_w; j++)
		{
			unsigned int index = segments_w * i + j;

			m_indexBuffer[index * 6] = (segments_w + 1) * i + j;
			m_indexBuffer[index * 6 + 1] = (segments_w + 1) * i + j + 1;
			m_indexBuffer[index * 6 + 2] = (segments_w + 1) * (i + 1) + j;
			m_indexBuffer[index * 6 + 3] = (segments_w + 1) * (i + 1) + j;
			m_indexBuffer[index * 6 + 4] = (segments_w + 1) * i + j + 1;
			m_indexBuffer[index * 6 + 5] = (segments_w + 1) * (i + 1) + j + 1;
		}
	}

	if (direction.y != 0)
		m_scale = { width, 0.0f, height };
	else if (direction.x != 0)
		m_scale = { 0.0f, height, width };
	else if (direction.z != 0)
		m_scale = { width, height, 0.0f };

	m_scaleChanged = true;

	generateBuffers();
}

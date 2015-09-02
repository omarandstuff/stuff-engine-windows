#include "GEsphere.h"

// ------------------------------------------------------------------------------ //
// ------------------------------- Initialization ------------------------------- //
// ------------------------------------------------------------------------------ //

GESphere::GESphere(float radious, unsigned int segments_u, unsigned int segments_v)
{
	generate(radious, segments_u, segments_v);
}

GESphere::~GESphere()
{
}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Load ------------------------------------ //
// ------------------------------------------------------------------------------ //

void GESphere::generate(float radious, unsigned int segments_u, unsigned int segments_v)
{
	// Vertex and index count of mesh.
	m_vertexCount = (segments_u * (segments_v - 1) + 2) * 8;
	m_indexCount = (segments_u * (segments_v - 2) * 6) + segments_u * 6;

	// Generate the data holders.
	m_vertexBuffer = new float[m_vertexCount];
	m_indexBuffer = new unsigned int[m_indexCount];

	// North pole vertex position coordinates.
	m_vertexBuffer[0] = 0.0f;
	m_vertexBuffer[1] = radious;
	m_vertexBuffer[2] = 0.0f;

	// North pole texture coordinates.
	m_vertexBuffer[3] = 0.5f;
	m_vertexBuffer[4] = 1.0f;

	// North pole normal coordinates.
	m_vertexBuffer[5] = 0.0f;
	m_vertexBuffer[6] = 1.0f;
	m_vertexBuffer[7] = 0.0f;

	int lastVertexIndex = (segments_u * (segments_v - 1) + 2) - 1;

	// South pole vertex position coordinates.
	m_vertexBuffer[lastVertexIndex * 8] = 0.0f;
	m_vertexBuffer[lastVertexIndex * 8 + 1] = -radious;
	m_vertexBuffer[lastVertexIndex * 8 + 2] = 0.0f;

	// South pole texture coordinates.
	m_vertexBuffer[lastVertexIndex * 8 + 3] = 0.5f;
	m_vertexBuffer[lastVertexIndex * 8 + 4] = 1.0f;

	// South pole normal coordinates.
	m_vertexBuffer[lastVertexIndex * 8 + 5] = 0.0f;
	m_vertexBuffer[lastVertexIndex * 8 + 6] = -1.0f;
	m_vertexBuffer[lastVertexIndex * 8 + 7] = 0.0f;

	float pi = glm::pi<float>();
	float angleStride = glm::two_pi<float>() / segments_u;
	float verticalAnlgeStride = pi / segments_v;

	for (int i = 0; i < segments_v - 1; i++)
	{
		float currentYAngled = radious * glm::cos(verticalAnlgeStride * (i + 1));
		float currentRadious = glm::sqrt(glm::pow(radious, 2.0f) - glm::pow(glm::abs(currentYAngled), 2.0f));
		for (int j = 0; j < segments_u; j++)
		{
			int index = segments_u * i + j + 1;

			m_vertexBuffer[index * 8] = currentRadious * glm::sin(angleStride * j);
			m_vertexBuffer[index * 8 + 1] = currentYAngled;
			m_vertexBuffer[index * 8 + 2] = currentRadious * glm::cos(angleStride * j);

			m_vertexBuffer[index * 8 + 3] = 0.0f;
			m_vertexBuffer[index * 8 + 4] = 0.0f;

			m_vertexBuffer[index * 8 + 5] = 0.0f;
			m_vertexBuffer[index * 8 + 6] = 1.0f;
			m_vertexBuffer[index * 8 + 7] = 0.0f;
		}
	}

	// North pole trianlges.
	for (int i = 0; i < segments_u - 1; i++)
	{
		m_indexBuffer[i * 3] = i + 1;
		m_indexBuffer[i * 3 + 1] = 0;
		m_indexBuffer[i * 3 + 2] = i + 2;
	}
	m_indexBuffer[(segments_u - 1) * 3] = segments_u;
	m_indexBuffer[(segments_u - 1) * 3 + 1] = 0;
	m_indexBuffer[(segments_u - 1) * 3 + 2] = 1;

	// Ecuador triangles.
	int indexOffset = segments_u * 3;
	for (int i = 0; i < segments_v - 2; i++)
	{
		for (int j = 0; j < segments_u - 1; j++)
		{
			int index = segments_u * i + j;

			m_indexBuffer[index * 6 + indexOffset] = (segments_u * i) + j + 1;
			m_indexBuffer[index * 6 + indexOffset + 1] = (segments_u * i) + j + 2;
			m_indexBuffer[index * 6 + indexOffset + 2] = segments_u * (i + 1) + j + 1;
			m_indexBuffer[index * 6 + indexOffset + 3] = segments_u * (i + 1) + j + 1;
			m_indexBuffer[index * 6 + indexOffset + 4] = (segments_u * i) + j + 2;
			m_indexBuffer[index * 6 + indexOffset + 5] = segments_u * (i + 1) + j + 2;
		}

		m_indexBuffer[segments_u * i * 6 + (segments_u - 1) * 6 + indexOffset] = segments_u * i + segments_u;
		m_indexBuffer[segments_u * i * 6 + (segments_u - 1) * 6 + indexOffset + 1] = segments_u * i + 1;
		m_indexBuffer[segments_u * i * 6 + (segments_u - 1) * 6 + indexOffset + 2] = segments_u * (i + 1) + segments_u;
		m_indexBuffer[segments_u * i * 6 + (segments_u - 1) * 6 + indexOffset + 3] = segments_u * (i + 1) + segments_u;
		m_indexBuffer[segments_u * i * 6 + (segments_u - 1) * 6 + indexOffset + 4] = segments_u * i + 1;
		m_indexBuffer[segments_u * i * 6 + (segments_u - 1) * 6 + indexOffset + 5] = segments_u * (i + 1) + 1;

	}

	// South pole triangles.
	indexOffset = m_indexCount - (segments_u * 3);
	int vertexOffset = lastVertexIndex - segments_u - 1;

	for (int i = 0; i < segments_u - 1; i++)
	{
		m_indexBuffer[indexOffset + i * 3] = vertexOffset + i + 1;
		m_indexBuffer[indexOffset + i * 3 + 1] = lastVertexIndex;
		m_indexBuffer[indexOffset + i * 3 + 2] = vertexOffset + i + 2;
	}
	m_indexBuffer[indexOffset + (segments_u - 1) * 3] = vertexOffset + segments_u;
	m_indexBuffer[indexOffset + (segments_u - 1) * 3 + 1] = lastVertexIndex;
	m_indexBuffer[indexOffset + (segments_u - 1) * 3 + 2] = vertexOffset + 1;


	generateBuffers();
}

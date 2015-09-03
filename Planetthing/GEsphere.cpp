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
	// Vertex and index mesh count.
	m_vertexCount = ((segments_u + 1) * (segments_v - 1) + segments_u * 2) * 8;
	m_indexCount = segments_u * (segments_v - 2) * 6 + segments_u * 6;

	// Generate the data holders.
	m_vertexBuffer = new float[m_vertexCount];
	m_indexBuffer = new unsigned int[m_indexCount];

	// Middle verteices coordinates.
	float pi = glm::pi<float>();
	float angleStride = glm::two_pi<float>() / segments_u;
	float verticalAnlgeStride = pi / segments_v;

	for (unsigned int i = 0; i < segments_v - 1; i++)
	{
		float currentYAngled = radious * glm::cos(verticalAnlgeStride * (i + 1));
		float currentRadious = glm::sqrt(glm::pow(radious, 2.0f) - glm::pow(glm::abs(currentYAngled), 2.0f));

		for (unsigned int j = 0; j <= segments_u; j++)
		{
			unsigned int index = (segments_u + 1) * i + j;

			m_vertexBuffer[index * 8] = currentRadious * glm::sin(angleStride * j);
			m_vertexBuffer[index * 8 + 1] = currentYAngled;
			m_vertexBuffer[index * 8 + 2] = currentRadious * glm::cos(angleStride * j);

			glm::vec3 currentNormal = glm::normalize(glm::vec3(m_vertexBuffer[index * 8], m_vertexBuffer[index * 8 + 1], m_vertexBuffer[index * 8 + 2]));

			m_vertexBuffer[index * 8 + 5] = currentNormal.x;
			m_vertexBuffer[index * 8 + 6] = currentNormal.y;
			m_vertexBuffer[index * 8 + 7] = currentNormal.z;

			float uCoord = glm::atan(currentNormal.x, currentNormal.z) / pi;
			bool uCoordCut = uCoord < 0.0f;
			m_vertexBuffer[index * 8 + 3] = j != segments_u ? ((uCoordCut ? 2.0f : 0.0f) + uCoord) * 0.5f : 1.0f;
			m_vertexBuffer[index * 8 + 4] = glm::asin(-currentNormal.y / pi) + 0.5f;
		}
	}

	// North pole vertices.
	unsigned int vertexOffset = (segments_u + 1) * (segments_v - 1);
	angleStride = 1.0f / (segments_u + 1);
	for (unsigned int i = 0; i < segments_u; i++)
	{
		m_vertexBuffer[(vertexOffset + i) * 8] = 0.0f;
		m_vertexBuffer[(vertexOffset + i) * 8 + 1] = radious;
		m_vertexBuffer[(vertexOffset + i) * 8 + 2] = 0.0f;

		m_vertexBuffer[(vertexOffset + i) * 8 + 3] = glm::cos(angleStride * (i + 1));
		m_vertexBuffer[(vertexOffset + i) * 8 + 4] = 0.0f;

		m_vertexBuffer[(vertexOffset + i) * 8 + 5] = 0.0f;
		m_vertexBuffer[(vertexOffset + i) * 8 + 6] = 1.0f;
		m_vertexBuffer[(vertexOffset + i) * 8 + 7] = 0.0f;
	}

	// South pole vertices.
	vertexOffset = (segments_u + 1) * (segments_v - 1) + segments_u;

	for (unsigned int i = 0; i < segments_u; i++)
	{
		m_vertexBuffer[(vertexOffset + i) * 8] = 0.0f;
		m_vertexBuffer[(vertexOffset + i) * 8 + 1] = -radious;
		m_vertexBuffer[(vertexOffset + i) * 8 + 2] = 0.0f;

		m_vertexBuffer[(vertexOffset + i) * 8 + 5] = 0.0f;
		m_vertexBuffer[(vertexOffset + i) * 8 + 6] = -1.0f;
		m_vertexBuffer[(vertexOffset + i) * 8 + 7] = 0.0f;
	}

	// Middle triangles indices.
	for (unsigned int i = 0; i < segments_v - 2; i++)
	{
		for (unsigned int j = 0; j < segments_u; j++)
		{
			unsigned int index = segments_u * i + j;

			m_indexBuffer[index * 6] = (segments_u + 1) * i + j;
			m_indexBuffer[index * 6 + 1] = (segments_u + 1) * i + j + 1;
			m_indexBuffer[index * 6 + 2] = (segments_u + 1) * (i + 1) + j;
			m_indexBuffer[index * 6 + 3] = (segments_u + 1) * (i + 1) + j;
			m_indexBuffer[index * 6 + 4] = (segments_u + 1) * i + j + 1;
			m_indexBuffer[index * 6 + 5] = (segments_u + 1) * (i + 1) + j + 1;
		}
	}

	// North pole triangles indices.
	unsigned int indexOffset = m_indexCount - segments_u * 6;
	vertexOffset = (segments_u + 1) * (segments_v - 1);
	for (unsigned int i = 0; i < segments_u; i++)
	{
		m_indexBuffer[indexOffset + i * 3] = i;
		m_indexBuffer[indexOffset + i * 3 + 1] = vertexOffset + i;
		m_indexBuffer[indexOffset + i * 3 + 2] = i + 1;
	}

	// South pole triangles indices.
	indexOffset = m_indexCount - segments_u * 3;
	vertexOffset = (segments_u + 1) * (segments_v - 1) + segments_u;
	for (unsigned int i = 0; i < segments_u; i++)
	{
		m_indexBuffer[indexOffset + i * 3] = vertexOffset - segments_u - 1 - i;
		m_indexBuffer[indexOffset + i * 3 + 1] = vertexOffset - segments_u + i;
		m_indexBuffer[indexOffset + i * 3 + 2] = vertexOffset + i;
	}

	generateBuffers();
}

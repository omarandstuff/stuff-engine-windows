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
	m_vertexCount = (segments_u + 1) * (segments_v + 1) * 8;
	m_indexCount = segments_u * segments_v * 6;

	// Generate the data holders.
	m_vertexBuffer = new float[m_vertexCount];
	m_indexBuffer = new unsigned int[m_indexCount];


	// Generathe the actal rectangle waraping a sphere.
	float pi = glm::pi<float>();
	float pi2 = glm::two_pi<float>();
	float angleStride = pi2 / segments_u;
	float verticalAnlgeStride = pi / segments_v;

	for (unsigned int i = 0; i <= segments_v; i++)
	{
		float currentYAngled = radious * glm::cos(verticalAnlgeStride * i);
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
			m_vertexBuffer[index * 8 + 4] = glm::asin(-currentNormal.y) / pi + 0.5f;
		}
	}

	// Rectangle triangles indicies.
	for (unsigned int i = 0; i < segments_v; i++)
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

	generateBuffers();
}

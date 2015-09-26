#include "GEsphere.h"

// ------------------------------------------------------------------------------ //
// ------------------------------- Initialization ------------------------------- //
// ------------------------------------------------------------------------------ //

GESphere::GESphere(float radious, unsigned int segments)
{
	generate(radious, segments);
}

GESphere::~GESphere()
{
}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Load ------------------------------------ //
// ------------------------------------------------------------------------------ //

void GESphere::generate(float radious, unsigned int segments)
{
	// Vertex and index mesh count.
	m_vertexCount = (unsigned int)(pow(segments + 1, 2) * 3 + pow((segments + 1) / 2 + 1, 2) * 12) * 8;
	m_indexCount = (unsigned int)(pow(segments, 2) * 3 + pow(segments / 2, 2) * 12) * 6;

	// Generate the data holders.
	m_vertexBuffer = new float[m_vertexCount];
	m_indexBuffer = new unsigned int[m_indexCount];

	float segmentStride = 2.0f / segments;

	// Vertex and index control
	unsigned int vertexOffset = 0;
	unsigned int indexOffset = 0;

	unsigned int segments2 = segments / 2;

	/////////////// North pole //////////////

	// Top-Left vertices.
	for (unsigned int i = 0; i <= segments2; i++)
	{
		for (unsigned int j = 0; j <= segments2; j++)
		{
			unsigned int index = (segments2 + 1) * i + j;
			processVertex(-1.0f + segmentStride * j, 1.0f, -1.0f + segmentStride * i, index, false, i == segments2 && j == segments2);
		}
	}

	processIndexArea(0, 0, segments2);

	// Top-right vertices.
	vertexOffset = (unsigned int)pow((segments + 1) / 2 + 1, 2);
	indexOffset = (unsigned int)pow(segments / 2, 2);
	for (unsigned int i = 0; i <= segments2; i++)
	{
		for (unsigned int j = segments2; j <= segments; j++)
		{
			unsigned int index = (segments2 + 1) * i + (j - segments2);
			processVertex(-1.0f + segmentStride * j, 1.0f, -1.0f + segmentStride * i, vertexOffset +  index, false, i == segments2 && j == segments2);
		}
	}

	processIndexArea(vertexOffset, indexOffset, segments2);

	// Bottom-Left vertices.
	vertexOffset = (unsigned int)pow((segments + 1) / 2 + 1, 2) * 2;
	indexOffset = (unsigned int)pow(segments / 2, 2) * 2;
	for (unsigned int i = segments2; i <= segments; i++)
	{
		for (unsigned int j = 0; j <= segments2; j++)
		{
			unsigned int index = (segments2 + 1) * (i - segments2) + j;
			processVertex(-1.0f + segmentStride * j, 1.0f, -1.0f + segmentStride * i, vertexOffset + index, j == segments2, false);
		}
	}

	processIndexArea(vertexOffset, indexOffset, segments2);

	// Bottom-right vertices.
	vertexOffset = (unsigned int)pow((segments + 1) / 2 + 1, 2) * 3;
	indexOffset = (unsigned int)pow(segments / 2, 2) * 3;
	for (unsigned int i = segments2; i <= segments; i++)
	{
		for (unsigned int j = segments2; j <= segments; j++)
		{
			unsigned int index = (segments2 + 1) * (i - segments2) + (j - segments2);
			processVertex(-1.0f + segmentStride * j, 1.0f, -1.0f + segmentStride * i, vertexOffset + index, false, false);
		}
	}

	processIndexArea(vertexOffset, indexOffset, segments2);

	/////////////// South pole //////////////

	// Top-Left vertices.
	vertexOffset = (unsigned int)pow((segments + 1) / 2 + 1, 2) * 4;
	indexOffset = (unsigned int)pow(segments / 2, 2) * 4;
	for (unsigned int i = 0; i <= segments2; i++)
	{
		for (unsigned int j = 0; j <= segments2; j++)
		{
			unsigned int index = (segments2 + 1) * i + j;
			processVertex(1.0f - segmentStride * j, -1.0f, -1.0f + segmentStride * i, vertexOffset + index, false, i == segments2 && j == segments2);
		}
	}

	processIndexArea(vertexOffset, indexOffset, segments2);

	// Top-right vertices.
	vertexOffset = (unsigned int)pow((segments + 1) / 2 + 1, 2) * 5;
	indexOffset = (unsigned int)pow(segments / 2, 2) * 5;
	for (unsigned int i = 0; i <= segments2; i++)
	{
		for (unsigned int j = segments2; j <= segments; j++)
		{
			unsigned int index = (segments2 + 1) * i + (j - segments2);
			processVertex(1.0f - segmentStride * j, -1.0f, -1.0f + segmentStride * i, vertexOffset + index, false, i == segments2 && j == segments2);
		}
	}

	processIndexArea(vertexOffset, indexOffset, segments2);

	// Bottom-Left vertices.
	vertexOffset = (unsigned int)pow((segments + 1) / 2 + 1, 2) * 6;
	indexOffset = (unsigned int)pow(segments / 2, 2) * 6;
	for (unsigned int i = segments2; i <= segments; i++)
	{
		for (unsigned int j = 0; j <= segments2; j++)
		{
			unsigned int index = (segments2 + 1) * (i - segments2) + j;
			processVertex(1.0f - segmentStride * j, -1.0f, -1.0f + segmentStride * i, vertexOffset + index, j == segments2, false);
		}
	}

	processIndexArea(vertexOffset, indexOffset, segments2);

	// Bottom-right vertices.
	vertexOffset = (unsigned int)pow((segments + 1) / 2 + 1, 2) * 7;
	indexOffset = (unsigned int)pow(segments / 2, 2) * 7;
	for (unsigned int i = segments2; i <= segments; i++)
	{
		for (unsigned int j = segments2; j <= segments; j++)
		{
			unsigned int index = (segments2 + 1) * (i - segments2) + (j - segments2);
			processVertex(1.0f - segmentStride * j, -1.0f, -1.0f + segmentStride * i, vertexOffset + index, false, false);
		}
	}

	processIndexArea(vertexOffset, indexOffset, segments2);

	//////// Left side ///////
	vertexOffset = (unsigned int)pow((segments + 1) / 2 + 1, 2) * 8;
	indexOffset = (unsigned int)pow(segments / 2, 2) * 8;
	for (unsigned int i = 0; i <= segments; i++)
	{
		for (unsigned int j = 0; j <= segments; j++)
		{
			unsigned int index = (segments + 1) * i + j;
			processVertex(-1.0f, 1.0f - segmentStride * i, -1.0f + segmentStride * j, vertexOffset + index, false, false);
		}
	}

	processIndexArea(vertexOffset, indexOffset, segments);

	//////// Right side ///////
	vertexOffset = (unsigned int)pow(segments + 1, 2) + (unsigned int)pow((segments + 1) / 2 + 1, 2) * 8;
	indexOffset = (unsigned int)pow(segments, 2) + (unsigned int)pow(segments / 2, 2) * 8;
	for (unsigned int i = 0; i <= segments; i++)
	{
		for (unsigned int j = 0; j <= segments; j++)
		{
			unsigned int index = (segments + 1) * i + j;
			processVertex(1.0f, 1.0f - segmentStride * i, 1.0f - segmentStride * j, vertexOffset + index, false, false);
		}
	}

	processIndexArea(vertexOffset, indexOffset, segments);

	//////// Back side ///////
	vertexOffset = (unsigned int)pow(segments + 1, 2) * 2 + (unsigned int)pow((segments + 1) / 2 + 1, 2) * 8;
	indexOffset = (unsigned int)pow(segments, 2) * 2 + (unsigned int)pow(segments / 2, 2) * 8;
	for (unsigned int i = 0; i <= segments; i++)
	{
		for (unsigned int j = 0; j <= segments; j++)
		{
			unsigned int index = (segments + 1) * i + j;
			processVertex(1.0f - segmentStride * j, 1.0f - segmentStride * i, -1.0f, vertexOffset + index, false, false);
		}
	}

	processIndexArea(vertexOffset, indexOffset, segments);

	//////// Front side ///////

	// Top - Left vertices
	vertexOffset = (unsigned int)pow(segments + 1, 2) * 3 + (unsigned int)pow((segments + 1) / 2 + 1, 2) * 8;
	indexOffset = (unsigned int)pow(segments, 2) * 3 + (unsigned int)pow(segments / 2, 2) * 8;
	for (unsigned int i = 0; i <= segments2; i++)
	{
		for (unsigned int j = 0; j <= segments2; j++)
		{
			unsigned int index = (segments2 + 1) * i + j;
			processVertex(-1.0f + segmentStride * j, 1.0f - segmentStride * i, 1.0f, vertexOffset + index, j == segments2, false);
		}
	}

	processIndexArea(vertexOffset, indexOffset, segments2);

	// Top-Right vertices
	vertexOffset = (unsigned int)pow(segments + 1, 2) * 3 + (unsigned int)pow((segments + 1) / 2 + 1, 2) * 9;
	indexOffset = (unsigned int)pow(segments, 2) * 3 + (unsigned int)pow(segments / 2, 2) * 9;
	for (unsigned int i = 0; i <= segments2; i++)
	{
		for (unsigned int j = segments2; j <= segments; j++)
		{
			unsigned int index = (segments2 + 1) * i + (j - segments2);
			processVertex(-1.0f + segmentStride * j, 1.0f - segmentStride * i, 1.0f, vertexOffset + index, false, false);
		}
	}

	processIndexArea(vertexOffset, indexOffset, segments2);

	// Bottom-Left vertices.
	vertexOffset = (unsigned int)pow(segments + 1, 2) * 3 + (unsigned int)pow((segments + 1) / 2 + 1, 2) * 10;
	indexOffset = (unsigned int)pow(segments, 2) * 3 + (unsigned int)pow(segments / 2, 2) * 10;
	for (unsigned int i = segments2; i <= segments; i++)
	{
		for (unsigned int j = 0; j <= segments2; j++)
		{
			unsigned int index = (segments2 + 1) * (i - segments2) + j;
			processVertex(-1.0f + segmentStride * j, 1.0f - segmentStride * i, 1.0f, vertexOffset + index, j == segments2, false);
		}
	}

	processIndexArea(vertexOffset, indexOffset, segments2);

	// Bottom-right vertices.
	vertexOffset = (unsigned int)pow(segments + 1, 2) * 3 + (unsigned int)pow((segments + 1) / 2 + 1, 2) * 11;
	indexOffset = (unsigned int)pow(segments, 2) * 3 + (unsigned int)pow(segments / 2, 2) * 11;
	for (unsigned int i = segments2; i <= segments; i++)
	{
		for (unsigned int j = segments2; j <= segments; j++)
		{
			unsigned int index = (segments2 + 1) * (i - segments2) + (j - segments2);
			processVertex(-1.0f + segmentStride * j, 1.0f - segmentStride * i, 1.0f, vertexOffset + index, false, false);
		}
	}

	processIndexArea(vertexOffset, indexOffset, segments2);

	m_scale = glm::vec3(radious);
	m_scaleChanged = true;

	generateBuffers();
}

void GESphere::processVertex(float x, float y, float z, unsigned int index, bool lastU, bool lastV)
{
	float pi = glm::pi<float>();

	float cubeX2 = x * x;
	float cubeY2 = y * y;
	float cubeZ2 = z * z;

	m_vertexBuffer[index * 8] = x * glm::sqrt(1.0f - cubeY2 * 0.5f - cubeZ2 * 0.5f + cubeY2 * cubeZ2 / 3.0f);
	m_vertexBuffer[index * 8 + 1] = y * glm::sqrt(1.0f - cubeZ2 * 0.5f - cubeX2 * 0.5f + cubeZ2 * cubeX2 / 3.0f);
	m_vertexBuffer[index * 8 + 2] = z * glm::sqrt(1.0f - cubeX2 * 0.5f - cubeY2  * 0.5f + cubeX2 * cubeY2 / 3.0f);

	glm::vec3 currentNormal = glm::vec3(m_vertexBuffer[index * 8], m_vertexBuffer[index * 8 + 1], m_vertexBuffer[index * 8 + 2]);

	m_vertexBuffer[index * 8 + 5] = currentNormal.x;
	m_vertexBuffer[index * 8 + 6] = currentNormal.y;
	m_vertexBuffer[index * 8 + 7] = currentNormal.z;

	float uCoord = glm::atan(currentNormal.x, currentNormal.z) / pi;
	bool uCoordCut = uCoord < 0.0f;
	m_vertexBuffer[index * 8 + 3] = !lastU ? (lastV ? 0.5f : ((uCoordCut ? 2.0f : 0.0f) + uCoord) * 0.5f) : 1.0f;
	m_vertexBuffer[index * 8 + 4] = glm::asin(-currentNormal.y) / pi + 0.5f;
}

void GESphere::processIndexArea(unsigned int vertexOffset, unsigned int indexOffset, unsigned int areaSegments)
{
	for (unsigned int i = 0; i < areaSegments; i++)
	{
		for (unsigned int j = 0; j < areaSegments; j++)
		{
			unsigned int index = i * areaSegments + j;

			m_indexBuffer[(indexOffset + index) * 6] = vertexOffset + (areaSegments + 1) * i + j;
			m_indexBuffer[(indexOffset + index) * 6 + 1] = vertexOffset + (areaSegments + 1) * i + j + 1;
			m_indexBuffer[(indexOffset + index) * 6 + 2] = vertexOffset + (i + 1) * (areaSegments + 1) + j;
			m_indexBuffer[(indexOffset + index) * 6 + 3] = vertexOffset + (i + 1) * (areaSegments + 1) + j;
			m_indexBuffer[(indexOffset + index) * 6 + 4] = vertexOffset + (areaSegments + 1) * i + j + 1;
			m_indexBuffer[(indexOffset + index) * 6 + 5] = vertexOffset + (i + 1) * (areaSegments + 1) + j + 1;
		}
	}
}
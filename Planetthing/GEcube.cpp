#include "GEcube.h"

// ------------------------------------------------------------------------------ //
// ------------------------------- Initialization ------------------------------- //
// ------------------------------------------------------------------------------ //

GECube::GECube(float width, float height, float depth, unsigned int segments_x, unsigned segments_y, unsigned int segments_z)
{
	generate(width, height, depth, segments_x, segments_y, segments_z);
}

GECube::~GECube()
{
}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Load ------------------------------------ //
// ------------------------------------------------------------------------------ //

void GECube::generate(float width, float height, float depth, unsigned int segments_x, unsigned segments_y, unsigned int segments_z)
{
	// Vertex and index mesh count.
	m_vertexCount = ((segments_x + 1) * (segments_y + 1) + (segments_z + 1) * (segments_y + 1) + (segments_x + 1) * (segments_z + 1)) * 16;
	m_indexCount = (segments_x * segments_y + segments_z * segments_y + segments_x * segments_z) * 12;

	// Generate the data holders.
	m_vertexBuffer = new float[m_vertexCount];
	m_indexBuffer = new unsigned int[m_indexCount];

	float xOrigin = 1.0 / 2.0f;
	float yOrigin = 1.0 / 2.0f;
	float zOrigin = 1.0 / 2.0f;

	unsigned int vertexOffset = 0;
	unsigned int indexOffset = 0;

	// Top
	createPlane(1.0f, 1.0, segments_x, segments_z, yOrigin, { 0.0f, 1.0f, 0.0f }, 0, 0);

	// Bottom
	vertexOffset = (segments_x + 1) * (segments_z + 1);
	indexOffset = segments_x * segments_z;
	createPlane(1.0f, 1.0f, segments_x, segments_z, yOrigin, { 0.0f, -1.0f, 0.0f }, vertexOffset, indexOffset);

	// Left
	vertexOffset = (segments_x + 1) * (segments_z + 1) * 2;
	indexOffset = segments_x * segments_z * 2;
	createPlane(1.0f, 1.0f, segments_z, segments_y, xOrigin, { -1.0f, 0.0f, 0.0f }, vertexOffset, indexOffset);

	//Right
	vertexOffset = (segments_x + 1) * (segments_z + 1) * 2 + (segments_z + 1) * (segments_y + 1);
	indexOffset = segments_x * segments_z * 2 + segments_z * segments_y;
	createPlane(1.0f, 1.0f, segments_z, segments_y, xOrigin, { 1.0f, 0.0f, 0.0f }, vertexOffset, indexOffset);

	//Back
	vertexOffset = ((segments_x + 1) * (segments_z + 1) + (segments_z + 1) * (segments_y + 1)) * 2;
	indexOffset = (segments_x * segments_z + segments_z * segments_y) * 2;
	createPlane(1.0f, 1.0f, segments_x, segments_y, zOrigin, { 0.0f, 0.0f, -1.0f }, vertexOffset, indexOffset);

	//Back
	vertexOffset = ((segments_x + 1) * (segments_z + 1) + (segments_z + 1) * (segments_y + 1)) * 2 + (segments_x + 1) * (segments_y + 1);
	indexOffset = (segments_x * segments_z + segments_z * segments_y) * 2 + segments_x * segments_y;
	createPlane(1.0f, 1.0f, segments_x, segments_y, zOrigin, { 0.0f, 0.0f, 1.0f }, vertexOffset, indexOffset);

	m_scale = { width, height, depth };
	m_scaleChanged = true;

	m_width = width;
	m_height = height;
	m_depth = depth;

	generateBuffers();
}

void GECube::createPlane(float width, float height, unsigned int segments_w, unsigned int segments_h, float offsetOrigin, glm::vec3 direction, unsigned int vertexOffset, unsigned int indexOffset)
{
	float wOrigin = width / 2.0f;
	float hOrigin = height / 2.0f;

	float wStride = width / segments_w;
	float hStride = height / segments_h;

	for (unsigned int i = 0; i <= segments_h; i++)
	{
		for (unsigned int j = 0; j <= segments_w; j++)
		{
			unsigned int index = vertexOffset + (segments_w + 1) * i + j;

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
			unsigned int index = indexOffset + segments_w * i + j;

			m_indexBuffer[index * 6] = vertexOffset + (segments_w + 1) * i + j;
			m_indexBuffer[index * 6 + 1] = vertexOffset + (segments_w + 1) * i + j + 1;
			m_indexBuffer[index * 6 + 2] = vertexOffset + (segments_w + 1) * (i + 1) + j;
			m_indexBuffer[index * 6 + 3] = vertexOffset + (segments_w + 1) * (i + 1) + j;
			m_indexBuffer[index * 6 + 4] = vertexOffset + (segments_w + 1) * i + j + 1;
			m_indexBuffer[index * 6 + 5] = vertexOffset + (segments_w + 1) * (i + 1) + j + 1;
		}
	}
}

// ------------------------------------------------------------------------------ //
// --------------------------------- Rigidbody ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GECube::makeRigidBody(bool kinematic)
{
	makeCubeRigidBody(m_width, m_height, m_depth, kinematic);
}

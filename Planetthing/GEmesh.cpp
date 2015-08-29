#include "GEmesh.h"

// ------------------------------------------------------------------------------ //
// ----------------------------------- Render ----------------------------------- //
// ------------------------------------------------------------------------------ //

void GEMesh::render(GLenum mode)
{
	glBindVertexArray(m_vertexArrayID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
	glDrawElements(mode, (GLsizei)Triangles.size() * 3, GL_UNSIGNED_INT, NULL);
}

// ------------------------------------------------------------------------------ //
// ------------------------- Generate - Compute Vertices ------------------------ //
// ------------------------------------------------------------------------------ //

void GEMesh::matchMeshWithFrame(GEFrame* frame)
{
	for (vector<GEVertex*>::iterator vertex = Vertices.begin(); vertex != Vertices.end(); vertex++)
	{
		(*vertex)->Position = { 0.0f, 0.0f, 0.0f };

		for (vector<GEWight*>::iterator weight = (*vertex)->Weights.begin(); weight != (*vertex)->Weights.end(); weight++)
		{
			GEJoint* joint = frame->Joints[(*weight)->JointID];
			glm::vec3 rotPosition = joint->Orientation * (*weight)->Position;
			(*vertex)->Position += (joint->Position + rotPosition) * (*weight)->Bias;
		}

		(*vertex)->Normal = { 0.0f, 0.0f, 0.0f };

		int index = vertex - Vertices.begin();

		m_vertexBuffer[index * 8] = (*vertex)->Position.x;
		m_vertexBuffer[index * 8 + 1] = (*vertex)->Position.z;
		m_vertexBuffer[index * 8 + 2] = -(*vertex)->Position.y;
		m_vertexBuffer[index * 8 + 3] = (*vertex)->TextureCoord.x;
		m_vertexBuffer[index * 8 + 4] = (*vertex)->TextureCoord.y;
	}

	for (vector<GETriangle*>::iterator triangle = Triangles.begin(); triangle != Triangles.end(); triangle++)
	{
		glm::vec3 normal = glm::cross((*triangle)->Vertex3->Position - (*triangle)->Vertex1->Position, (*triangle)->Vertex2->Position - (*triangle)->Vertex1->Position);

		(*triangle)->Vertex1->Normal += normal;
		(*triangle)->Vertex2->Normal += normal;
		(*triangle)->Vertex3->Normal += normal;
	}

	for (vector<GEVertex*>::iterator vertex = Vertices.begin(); vertex != Vertices.end(); vertex++)
	{
		glm::vec3 normal = glm::normalize((*vertex)->Normal);

		int index = vertex - Vertices.begin();

		m_vertexBuffer[index * 8 + 5] = (*vertex)->Normal.x;
		m_vertexBuffer[index * 8 + 6] = (*vertex)->Normal.z;
		m_vertexBuffer[index * 8 + 7] = -(*vertex)->Normal.y;
	}

	// Bind the vertex buffer and refill it with data.
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * Vertices.size() * 8, m_vertexBuffer);
}

void GEMesh::generateBuffers()
{
	// Create the dynamic vertex data and the static index data.
	m_vertexBuffer = new float[Vertices.size() * 8];
	m_indexBuffer = new unsigned int[Triangles.size() * 3];

	// Fill the index information
	for (vector<GETriangle*>::iterator triangle = Triangles.begin(); triangle != Triangles.end(); triangle++)
	{
		int index = triangle - Triangles.begin();
		m_indexBuffer[index * 3] = (*triangle)->Vertex1->Index;
		m_indexBuffer[index * 3 + 1] = (*triangle)->Vertex2->Index;
		m_indexBuffer[index * 3 + 2] = (*triangle)->Vertex3->Index;
	}

	// Generate a vertex array id that keep both the vertex buffer and the indexbiffer.
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Genreate the vertex buffer and fill it with the dynamic data.
	glGenBuffers(1, &m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Vertices.size() * 8, m_vertexBuffer, GL_DYNAMIC_DRAW);

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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Triangles.size() * 3, m_indexBuffer, GL_STATIC_DRAW);

	delete[] m_indexBuffer;

	// Unbind everything.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

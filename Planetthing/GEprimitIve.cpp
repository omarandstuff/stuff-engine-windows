#include "GEprimitive.h"

// ------------------------------------------------------------------------------ //
// ------------------------------------ Render ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GEPrimitive::render(GE_RENDER_MODE mode)
{
	// If it's not supouse to be visible don't render at all.
	if (!Visible) return;

	// Bind this model.
	glBindVertexArray(m_vertexArrayID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	if (mode == GE_RENDER_MODE_NORMAL)
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (Wireframe)
		{
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1, 1);
		}

		// Material and model matrices.
		m_blinnPhongShader->Material = &Material;
		m_blinnPhongShader->ModelMatrix = &FinalMatrix;
		m_blinnPhongShader->NormalMatrix = &m_rotationMatrix;

		m_blinnPhongShader->useProgram();

		glCullFace(GL_BACK);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, NULL);

		if (Wireframe)
		{
			glEnable(GL_DEPTH_TEST);
			glDisable(GL_BLEND);
			glDisable(GL_POLYGON_OFFSET_FILL);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			glLineWidth(1.0f);

			m_colorShader->Material = &m_wireframeMaerial;

			m_colorShader->useProgram();

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
			glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, NULL);


			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
	else if (mode == GE_RENDER_MODE_DEPTH)
	{
		// Disable blend.
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		m_depthShader->useProgram();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, NULL);
	}
}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Load ------------------------------------ //
// ------------------------------------------------------------------------------ //

void GEPrimitive::generateBuffers()
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

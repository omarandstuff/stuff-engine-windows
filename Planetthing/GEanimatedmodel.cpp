#include "GEanimatedmodel.h"

// ------------------------------------------------------------------------------ //
// ------------------------------- Initialization ------------------------------- //
// ------------------------------------------------------------------------------ //

GEMaterial GEAnimatedModel::m_boundingBoxMaterial;

GEAnimatedModel::GEAnimatedModel(wstring filename)
{
	GEAnimatedModel();
	loadModelWithFileName(filename);
}

GEAnimatedModel::GEAnimatedModel()
{
	// Get the shaders.
	//m_blinnPhongShader = [GEBlinnPhongShader sharedIntance];
	m_textureShader = GETextureShader::sharedInstance();
	//m_colorShader = [GEColorShader sharedIntance];
	//m_depthShader = [GEDepthShader sharedIntance];

	// Bounding box.
	//m_boundingBox = [GEBoundingbox sharedIntance];
	m_boundingBoxMaterial.DiffuseColor = {0.2f, 0.2f, 0.2f};

	// Ebanled and Visible by default.
	Enabled = true;
	Visible = true;
}

GEAnimatedModel::~GEAnimatedModel()
{
}

// ------------------------------------------------------------------------------ //
// ---------------------------------- Animation --------------------------------- //
// ------------------------------------------------------------------------------ //

void GEAnimatedModel::resetPose()
{
	// Bind pose and bounds.
	m_currentBound = &m_bindBound;
	for (vector<GEMesh>::iterator mesh = m_meshes.begin(); mesh != m_meshes.end(); mesh++)
		mesh->matchMeshWithFrame(&m_bindPose);
}

void GEAnimatedModel::poseForFrameDidFinish(GEFrame* frame)
{
	// If it is not enabled for animations not update the frame pose
	if (!Enabled) return;

	// Get the bound from the frame.
	m_currentBound = &frame->Bounds;

	// Updtae every mesh.
	for (vector<GEMesh>::iterator mesh = m_meshes.begin(); mesh != m_meshes.end(); mesh++)
		mesh->matchMeshWithFrame(frame);
}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Render ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GEAnimatedModel::render()
{
	// If it's not supouse to be visible don't render at all.
	if (!Visible) return;

	glEnable(GL_DEPTH_TEST);

	// Draw each mesh.
	for (vector<GEMesh>::iterator mesh = m_meshes.begin(); mesh != m_meshes.end(); mesh++)
	{
		m_textureShader->Material = &mesh->Material;

		m_textureShader->useProgram();
		mesh->render(GL_TRIANGLES);
	}

	// Draw bounding box
	if (RenderBoundingBox)
	{
		//m_boundingBox.Bound = m_currentBound;

		glLineWidth(2.0f);

		// Ware frame pass.
		//m_colorShader.Material = m_boundingBoxMaterial;

		//[m_colorShader useProgram];

		//[m_boundingBox render];
	}
}

void GEAnimatedModel::renderDepth()
{
	// If it's not supouse to be visible don't render at all.
	if (!Visible) return;

	// Disable blend.
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	// Draw each mesh.
	for (vector<GEMesh>::iterator mesh = m_meshes.begin(); mesh != m_meshes.end(); mesh++)
	{
		//[m_depthShader useProgram];
		mesh->render(GL_TRIANGLES);
	}
}

// ------------------------------------------------------------------------------ //
// --------------------------- Load - Import - Export --------------------------- //
// ------------------------------------------------------------------------------ //

void GEAnimatedModel::loadModelWithFileName(wstring filename)
{
	if (filename == L"") return;

	wstring fileType = filename.substr(filename.find_last_of(L".") + 1);
	wstring filePath = filename.substr(0, filename.find_last_of(L"."));

	FileName = filename;

	// Decide what load method to use.
	if (fileType == L"md5mesh")
		Ready = loadMD5WithFileName(filePath);

	// If the file was loaded duccessfully prepare all the meshes buffers.
	if (Ready)
	{
		for (vector<GEMesh>::iterator mesh = m_meshes.begin(); mesh != m_meshes.end(); mesh++)
			mesh->generateBuffers();

		resetPose();
	}

}

bool GEAnimatedModel::loadMD5WithFileName(wstring filename)
{
	wfstream wStream((filename + L".md5mesh").c_str());

	if (!wStream)
		return false;

	// MD5 file counters
	int numberOfJoints = 0;
	int numberOfMeshes = 0;

	// Temporal Wight Information
	struct weightInf
	{
		unsigned int startWight;
		unsigned int weightCount;
	};
	vector<weightInf> verticesWightInf;
	// Get path
	wstring filePath = filename.substr(0, filename.find_last_of(L"/"));

	vector<GEMesh>::iterator currentMesh;

	// Do work until reach all the content
	wchar_t line[256];
	while (wStream.getline(line, 256))
	{
		wistringstream newLine(line, wistringstream::in);

		wstring first;
		newLine >> first;

		if (first == L"numJoints") // Line with the number of joints to read,
		{
			newLine >> numberOfJoints;
			continue;
		}
		else if (first == L"numMeshes")// Line with the number of meshes to read,
		{
			newLine >> numberOfMeshes;
			continue;
		}
		else if (first == L"joints")
		{
			// Make a joint object for each joint line.
			for (int i = 0; i < numberOfJoints; i++)
			{
				// Joint line.
				wStream.getline(line, 256);
				wistringstream jointLine(line, wistringstream::in);

				// New joint.
				GEJoint* currentJoint = new GEJoint;

				// Extract the name
				wstring name, nameBuffer;
				jointLine >> nameBuffer;
				name = nameBuffer;
				while (nameBuffer.back() != L'\"')
				{
					jointLine >> nameBuffer;
					name += L" " + nameBuffer;
				}
				currentJoint->Name = name;

				// Parent
				int parentID;
				jointLine >> parentID;
				currentJoint->Parent = parentID == -1 ? 0 : m_bindPose.Joints[parentID];

				wstring junk;
				jointLine >> junk;

				// Position data.
				jointLine >> currentJoint->Position.x;
				jointLine >> currentJoint->Position.y;
				jointLine >> currentJoint->Position.z;

				jointLine >> junk;
				jointLine >> junk;

				// Orientation data.
				jointLine >> currentJoint->Orientation.x;
				jointLine >> currentJoint->Orientation.y;
				jointLine >> currentJoint->Orientation.z;
				computeWComponentOfQuaternion(currentJoint->Orientation);

				// Add new joint.
				m_bindPose.Joints.push_back(currentJoint);
			}
		}
		else if (first == L"mesh")
		{
			// New Mesh.
			m_meshes.push_back(GEMesh());
			currentMesh = m_meshes.end() - 1;
		}
		else if (first == L"shader")
		{
			wstring texturePath;
			newLine >> texturePath;

			texturePath = texturePath.substr(1, texturePath.size() - 2);

			// New texture for this mesh material.
			currentMesh->Material.DiffuseMap = GETexture::textureWithFileName(filePath + L"/" + texturePath);

			wstring textureType = texturePath.substr(texturePath.find_last_of(L".") + 1);
			wstring textureName = texturePath.substr(0, texturePath.find_last_of(L"."));

			currentMesh->Material.SpecularMap = GETexture::textureWithFileName(filePath + L"/" + textureName + L"_specular" + L"." + textureType);
		}
		else if (first == L"numverts")
		{
			// Number of vertices.
			unsigned int numberOfVertices;
			newLine >> numberOfVertices;

			// Make a new vertex object for each vertex line.
			for (unsigned int i = 0; i < numberOfVertices; i++)
			{
				// Vertex line.
				wStream.getline(line, 256);
				wistringstream vertexLine(line, wistringstream::in);

				// New vertex.
				GEVertex* currentVertex = new GEVertex;
				currentMesh->Vertices.push_back(currentVertex);

				// Verrtex index;
				currentVertex->Index = i;

				wstring junk;
				vertexLine >> junk >> junk >> junk;

				// Texture coord data.
				vertexLine >> currentVertex->TextureCoord.x;
				vertexLine >> currentVertex->TextureCoord.y;

				vertexLine >> junk;

				verticesWightInf.push_back(weightInf());
				// Wights data.
				vertexLine >> verticesWightInf[i].startWight;
				vertexLine >> verticesWightInf[i].weightCount;
			}
		}
		else if (first == L"numtris")
		{
			// Number of triangles.
			unsigned int numberOfTriangles;
			newLine >> numberOfTriangles;

			// Make a new trianlge object for each triangle line.
			for (unsigned int i = 0; i < numberOfTriangles; i++)
			{
				// Triangle line.
				wStream.getline(line, 256);
				wistringstream triangleLine(line, wistringstream::in);

				wstring junk;
				triangleLine >> junk >> junk;

				// New triangle.
				GETriangle* currentTrangle = new GETriangle;
				currentMesh->Triangles.push_back(currentTrangle);

				// Vertices data.
				unsigned int vertexIndex;
				triangleLine >> vertexIndex;
				currentTrangle->Vertex1 = currentMesh->Vertices[vertexIndex];
				triangleLine >> vertexIndex;
				currentTrangle->Vertex2 = currentMesh->Vertices[vertexIndex];
				triangleLine >> vertexIndex;
				currentTrangle->Vertex3 = currentMesh->Vertices[vertexIndex];
			}
		}
		else if (first == L"numweights")
		{
			// Number of weights.
			unsigned int numberOfWeights;
			newLine >> numberOfWeights;

			// Make a new weight object for each weight line.
			for (unsigned int i = 0; i < numberOfWeights; i++)
			{
				// Wight line.
				wStream.getline(line, 256);
				wistringstream weightLine(line, wistringstream::in);

				// New weight.
				GEWight* currentWeight = new GEWight;
				currentMesh->Weights.push_back(currentWeight);

				wstring junk;
				weightLine >> junk >> junk;

				// Joint inf.
				weightLine >> currentWeight->JointID;

				// Bias info.
				weightLine >> currentWeight->Bias;

				weightLine >> junk;

				// Weight position data.
				weightLine >> currentWeight->Position.x;
				weightLine >> currentWeight->Position.y;
				weightLine >> currentWeight->Position.z;
			}

			// Weight references for vertices base the weight inf we've got previously.
			for (vector<GEVertex*>::iterator vertex = currentMesh->Vertices.begin(); vertex != currentMesh->Vertices.end(); vertex++)
			{
				int index = vertex - currentMesh->Vertices.begin();
				for (unsigned int j = 0; j < verticesWightInf[index].weightCount; j++)
					(*vertex)->Weights.push_back(currentMesh->Weights[verticesWightInf[index].startWight + j]);
			}

			verticesWightInf.clear();
		}
	}
	return true;
}

void GEAnimatedModel::computeWComponentOfQuaternion(glm::quat& quaternion)
{
	float t = 1.0f - (quaternion.x * quaternion.x) - (quaternion.y * quaternion.y) - (quaternion.z * quaternion.z);
	quaternion.w = t < 0.0f ? 0.0f : -sqrtf(t);
}

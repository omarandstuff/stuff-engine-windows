#pragma once

#include "GErenderable.h"
#include "GEmesh.h"
#include "GEanimation.h"
#include "GEboundingbox.h"

class GEAnimatedModel : public GERenderable, public GEAnimationProtocol
{
public:
	GEAnimatedModel(wstring filename);
	GEAnimatedModel();
	~GEAnimatedModel();

	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
public:
	wstring FileName;
	bool Ready;
	bool RenderBoundingBox;

	// -------------------------------------------- //
	// ---------- Load - Import - Export ---------- //
	// -------------------------------------------- //
public:
	void loadModelWithFileName(wstring filename);

	// -------------------------------------------- //
	// ----------------- Animation ---------------- //
	// -------------------------------------------- //
public:
	void resetPose();
	void poseForFrameDidFinish(GEFrame* frame);

	// -------------------------------------------- //
	// ------------------ Render ------------------ //
	// -------------------------------------------- //
public:
	void render(GE_RENDER_MODE mode);

	// -------------------------------------------- //
	// ------------- Private members -------------- //
	// -------------------------------------------- //
private:
	bool loadMD5WithFileName(wstring filename);
	void computeWComponentOfQuaternion(glm::quat& quaternion);

private:
	GEFrame m_bindPose;
	vector<GEMesh> m_meshes;

	GEBoundingBox* m_boundingBox;

	GEBound* m_currentBound;
	GEBound m_bindBound;
	static GEMaterial m_boundingBoxMaterial;
};

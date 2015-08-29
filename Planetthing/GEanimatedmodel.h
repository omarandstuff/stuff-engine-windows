#pragma once

#include "GErenderable.h"
#include "GEtextureshader.h"
#include "GEcolorshader.h"
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
	wstring FileName;
	bool Ready;
	bool RenderBoundingBox;
	bool Visible;
	bool Enabled;

	// -------------------------------------------- //
	// ---------- Load - Import - Export ---------- //
	// -------------------------------------------- //
	void loadModelWithFileName(wstring filename);

	// -------------------------------------------- //
	// ----------------- Animation ---------------- //
	// -------------------------------------------- //
	void resetPose();
	void poseForFrameDidFinish(GEFrame* frame);

	// -------------------------------------------- //
	// ------------------ Render ------------------ //
	// -------------------------------------------- //
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

	//GEBlinnPhongShader* m_blinnPhongShader;
	GETextureShader* m_textureShader;
	//GEDepthShader* m_depthShader;
	GEColorShader* m_colorShader;
	GEBoundingBox* m_boundingBox;

	GEBound* m_currentBound;
	GEBound m_bindBound;
	static GEMaterial m_boundingBoxMaterial;
};

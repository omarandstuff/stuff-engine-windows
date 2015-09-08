#pragma once

#include "GEframe.h"
#include "GEjoint.h"
#include "GEupdatecaller.h"

class GEAnimationProtocol
{
public:
	virtual void poseForFrameDidFinish(GEFrame* frame) = 0;
};

class GEAnimation : public GEUpdateProtocol
{
	// -------------------------------------------- //
	// --------------- Initializaion -------------- //
	// -------------------------------------------- //
public:
	GEAnimation();
	GEAnimation(wstring filename);
	~GEAnimation();

	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
public:
	wstring FileName;
	unsigned int NumberOfFrames;
	unsigned int FrameRate;
	vector<GEFrame*> Frames;
	bool Ready;

	float Duration;
	bool Playing;
	float CurrentTime;
	bool Reverse;
	float PlaybackSpeed;

	// -------------------------------------------- //
	// ------------ Delegate Management ----------- //
	// -------------------------------------------- //
public:
	void addDelegate(GEAnimationProtocol* delegate);
	void removeDelegate(GEAnimationProtocol* deegate);

	// -------------------------------------------- //
	// ------------------ Update ------------------ //
	// -------------------------------------------- //
public:
	void update(float time);
	void preUpdate() {}
	void posUpdate() {}


	// -------------------------------------------- //
	// ---------- Load - Import - Export ---------- //
	// -------------------------------------------- //
public:
	void loadAnimationWithFileName(wstring filename);

	// -------------------------------------------- //
	// ------------------ Playback ---------------- //
	// -------------------------------------------- //
public:
	void play();
	void stop();
	void pause();

	// -------------------------------------------- //
	// ------------- Private members -------------- //
	// -------------------------------------------- //
private:
	bool loadMD5WithFileName(wstring filename);
	void computeWComponentOfQuaternion(glm::quat& quaternion);

	void callDelegates();

private:
	float m_frameDuration;
	vector<GEAnimationProtocol*> m_delegates;
	GEFrame* m_finalFrame;
};

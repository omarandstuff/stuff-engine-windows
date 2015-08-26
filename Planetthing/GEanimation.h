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
	GEAnimation();
	~GEAnimation();

	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
public:
	wstring FileName;
	unsigned int NumberOfFrames;
	unsigned int FrameRate;
	vector<GEFrame> Frames;
	bool Ready;

	float Duration;
	bool Playing;
	float CurrentTime;
	bool Reverse;
	float PlaybackSpeed;

	// -------------------------------------------- //
	// ------------ Selector Management ----------- //
	// -------------------------------------------- //
public:
	void addSelector(GEAnimationProtocol* selector);
	void removeSelector(void** selector);

	// -------------------------------------------- //
	// ------------------ Update ------------------ //
	// -------------------------------------------- //
public:
	void update(float time);

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
	float computeWComponentOfQuaternion(glm::quat quaternion);

	void callSelectors();

private:
	float m_frameDuration;
	vector<GEAnimationProtocol*> m_selectors;
	GEFrame m_finalFrame;


};

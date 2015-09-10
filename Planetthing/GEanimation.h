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
private:
	wstring m_filename;
	unsigned int m_numberOfFrames;
	unsigned int m_frameRate;
	vector<GEFrame*> m_frames;
	bool m_ready;

	float m_duration;
	bool m_playing;
	float m_currentTime;
	bool m_reverse;
	float m_playbackSpeed;

	// -------------------------------------------- //
	// ------------- Getters / Setters ------------ //
	// -------------------------------------------- //
public:
	wstring filename();
	unsigned int numberOfFrames();
	unsigned int frameRate();
	vector<GEFrame*> frames();
	bool ready();

	float duration();
	bool playing();
	float currentTime();
	void currentTime(float time);
	void reverse(bool value);
	float playbacSpeed();
	void playbackSpeed(float speed);

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

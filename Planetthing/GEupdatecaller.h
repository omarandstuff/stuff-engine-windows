#pragma once

#include <windows.h>
#include <mmsystem.h>
#include <vector>
using std::vector;
// -------------------------------------------- //
// ----------------- Protocols ---------------- //
// -------------------------------------------- //
class GEUpdateProtocol
{
public:
	virtual void update(float time) = 0;
	virtual void preUpdate() = 0;
	virtual void posUpdate() = 0;
};

class GERenderProtocol
{
public:
	virtual void render() = 0;
	virtual void layout(int width, int height) = 0	;

};

class GEUpdateCaller
{
	// -------------------------------------------- //
	// ----------------- Singleton ---------------- //
	// -------------------------------------------- //
public:
	static GEUpdateCaller* sharedInstance();
private:
	GEUpdateCaller()
	{
		// Check to see if this system supports high performance VETimers.
		QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);

		// Find out how many times the frequency counter ticks every millisecond.
		m_ticksPerMs = (float)(m_frequency / 1000);

		QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);

		//Set inicial values.
		UpTime = 0.0f;
	};

	GEUpdateCaller(GEUpdateCaller const&) = delete;
	void operator=(GEUpdateCaller const&) = delete;

	// -------------------------------------------- //
	// ---------------- Properties ---------------- //
	// -------------------------------------------- //
public:
	float UpTime;

	// -------------------------------------------- //
	// ------------ Selector Management ----------- //
	// -------------------------------------------- //
public:
	void addUpdateableSelector(GEUpdateProtocol* selector);
	void addRenderableSelector(GERenderProtocol* selector);
	void removeSelector(void* selector);

	// -------------------------------------------- //
	// ------------------ Update ------------------ //
	// -------------------------------------------- //
public:
	void update();
	void preUpdate();
	void posUpdate();

	// -------------------------------------------- //
	// ------------- Render - Layout -------------- //
	// -------------------------------------------- //
public:
	void render();
	void layout(int width, int height);

	// -------------------------------------------- //
	// ------------- Private members -------------- //
	// -------------------------------------------- //
private:
	INT64 m_frequency;
	float m_ticksPerMs;
	INT64 m_startTime;
	float m_frameTime;

	vector<GEUpdateProtocol*> m_updateSelectors;
	vector<GERenderProtocol*> m_renderSelectors;
};

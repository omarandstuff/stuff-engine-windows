#include "GEupdatecaller.h"

// ------------------------------------------------------------------------------ //
// -----------------------------  Singleton - Set up ---------------------------- //
// ------------------------------------------------------------------------------ //

GEUpdateCaller* GEUpdateCaller::sharedInstance()
{
	static GEUpdateCaller sharedInstance;

	return &sharedInstance;
}

// ------------------------------------------------------------------------------ //
// ----------------------------- Delegate Management ---------------------------- //
// ------------------------------------------------------------------------------ //

void GEUpdateCaller::addUpdateableDelegate(GEUpdateProtocol* delegate)
{
	m_updateDelegates.push_back(delegate);
}

void GEUpdateCaller::addRenderableDelegate(GERenderProtocol* delegate)
{
	m_renderDelegates.push_back(delegate);
}

void GEUpdateCaller::removeDelegate(void* delegate)
{
	// If selector is in update selectors.
	for (vector<GEUpdateProtocol*>::iterator it = m_updateDelegates.begin(); it != m_updateDelegates.end(); it++)
	{
		if (*it._Ptr == delegate)
		{
			m_updateDelegates.erase(it);
			return;
		}
	}

	// If selector is in render selectors.
	for (vector<GERenderProtocol*>::iterator it = m_renderDelegates.begin(); it != m_renderDelegates.end(); it++)
	{
		if (*it._Ptr == delegate)
		{
			m_renderDelegates.erase(it);
			return;
		}
	}
}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Update ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GEUpdateCaller::update()
{
	INT64 currentTime;
	float timeDifference;

	// Query the current time.
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	// Calculate the difference in time since the last time we queried for the current time.
	timeDifference = (float)(currentTime - m_startTime);

	// Calculate the frame time by the time difference over the VETimer speed resolution.
	m_frameTime = (timeDifference / m_ticksPerMs) / 1000.0f;

	// Restart the VETimer.
	m_startTime = currentTime;

	// Update every selector
	for (vector<GEUpdateProtocol*>::iterator it = m_updateDelegates.begin(); it != m_updateDelegates.end(); it++)
		(*it)->update(m_frameTime);
}

void GEUpdateCaller::preUpdate()
{
	// Pre update every selector
	for (vector<GEUpdateProtocol*>::iterator it = m_updateDelegates.begin(); it != m_updateDelegates.end(); it++)
		(*it)->preUpdate();
}

void GEUpdateCaller::posUpdate()
{
	// Pos update every selector
	for (vector<GEUpdateProtocol*>::iterator it = m_updateDelegates.begin(); it != m_updateDelegates.end(); it++)
		(*it)->posUpdate();
}

// ------------------------------------------------------------------------------ //
// ------------------------------- Render - Layout ------------------------------ //
// ------------------------------------------------------------------------------ //

void GEUpdateCaller::render()
{
	// Call render for every selector.
	for (vector<GERenderProtocol*>::iterator it = m_renderDelegates.begin(); it != m_renderDelegates.end(); it++)
		(*it)->render();
}

void GEUpdateCaller::layout(int width, int height)
{
	for (vector<GERenderProtocol*>::iterator it = m_renderDelegates.begin(); it != m_renderDelegates.end(); it++)
		(*it)->layout(width, height);
}

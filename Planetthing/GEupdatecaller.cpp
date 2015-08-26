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
// ----------------------------- Selector Management ---------------------------- //
// ------------------------------------------------------------------------------ //

void GEUpdateCaller::addUpdateableSelector(GEUpdateProtocol* selector)
{
	m_updateSelectors.push_back(selector);
}

void GEUpdateCaller::addRenderableSelector(GERenderProtocol* selector)
{
	m_renderSelectors.push_back(selector);
}

void GEUpdateCaller::removeSelector(void** selector)
{
	// If selector is in update selectors.
	for (vector<GEUpdateProtocol*>::iterator it = m_updateSelectors.begin(); it != m_updateSelectors.end(); it++)
	{
		if (it._Ptr == (GEUpdateProtocol**)selector)
		{
			m_updateSelectors.erase(it);
			return;
		}
	}

	// If selector is in render selectors.
	for (vector<GERenderProtocol*>::iterator it = m_renderSelectors.begin(); it != m_renderSelectors.end(); it++)
	{
		if (it._Ptr == (GERenderProtocol**)selector)
		{
			m_renderSelectors.erase(it);
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
	double timeDifference;

	// Query the current time.
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	// Calculate the difference in time since the last time we queried for the current time.
	timeDifference = (float)(currentTime - m_startTime);

	// Calculate the frame time by the time difference over the VETimer speed resolution.
	m_frameTime = timeDifference / m_ticksPerMs;

	// Restart the VETimer.
	m_startTime = currentTime;

	// Update every selector
	for (vector<GEUpdateProtocol*>::iterator it = m_updateSelectors.begin(); it != m_updateSelectors.end(); it++)
		(*it)->update(m_frameTime);
}

void GEUpdateCaller::preUpdate()
{
	// Pre update every selector
	for (vector<GEUpdateProtocol*>::iterator it = m_updateSelectors.begin(); it != m_updateSelectors.end(); it++)
		(*it)->preUpdate();
}

void GEUpdateCaller::posUpdate()
{
	// Pos update every selector
	for (vector<GEUpdateProtocol*>::iterator it = m_updateSelectors.begin(); it != m_updateSelectors.end(); it++)
		(*it)->posUpdate();
}

// ------------------------------------------------------------------------------ //
// ------------------------------- Render - Layout ------------------------------ //
// ------------------------------------------------------------------------------ //

void GEUpdateCaller::render()
{
	// Call render for every selector.
	for (vector<GERenderProtocol*>::iterator it = m_renderSelectors.begin(); it != m_renderSelectors.end(); it++)
		(*it)->render();
}

void GEUpdateCaller::layout(int width, int height)
{
	for (vector<GERenderProtocol*>::iterator it = m_renderSelectors.begin(); it != m_renderSelectors.end(); it++)
		(*it)->layout(width, height);
}

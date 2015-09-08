#pragma once

#include "GEwindow.h"
#include "GEcommon.h"
#include "GEupdatecaller.h"
#include <Xinput.h>

// -------------------------------------------- //
// ----------------- Protocols ---------------- //
// -------------------------------------------- //

class GEInputXBoxControllerProtocol
{
public:
	virtual void xBoxControllerButtonDown(GE_INPUT_XBOX button, int player) = 0;
	virtual void xBoxControllerButtonUp(GE_INPUT_XBOX button, int player) = 0;
	virtual void xBoxControllerTriguerChange(GE_INPUT_XBOX trigger, int player, float value) = 0;
	virtual void xBoxControllerStickChange(GE_INPUT_XBOX stick, int player, float xAxis, float yAxis) = 0;
};

class GEInputMouseProtocol
{
public:
	virtual void mouseMove(float coordX, float coordY) = 0;
	virtual void mouseChange(float deltaX, float deltaY) = 0;
};

class GEInput : public GEUpdateProtocol, public GEWindowInputProtocol
{
	// -------------------------------------------- //
	// ----------------- Singleton ---------------- //
	// -------------------------------------------- //
public:
	static GEInput* sharedInstance();
private:
	GEInput()
	{
		// Self updateable.
		GEUpdateCaller::sharedInstance()->addUpdateableDelegate(this);

		// Get Xbox at the begining.
		m_XBoxCheckElapsed = 6.0f;
	};

	GEInput(GEInput const&) = delete;
	void operator=(GEInput const&) = delete;

	// -------------------------------------------- //
	// ------------------ Update ------------------ //
	// -------------------------------------------- //
public:
	void update(float time);
	void preUpdate();
	void posUpdate();

	// -------------------------------------------- //
	// ------------ Delegate Management ----------- //
	// -------------------------------------------- //
public:
	void addXBoxContollerDelegate(GEInputXBoxControllerProtocol* delegate);
	void removeXBoxControllerDelegate(GEInputXBoxControllerProtocol* delegate);
	void addMouseDelegate(GEInputMouseProtocol* delegate);
	void removeMouseDelegate(GEInputMouseProtocol* delegate);

	// -------------------------------------------- //
	// -------------- XBox Controller ------------- //
	// -------------------------------------------- //
private:
	void readXBOXControllerState(float time);
	void doXboxButtonCheck(GE_INPUT_XBOX input, int player, bool currentCheck);
	void doXboxTriggerCheck(GE_INPUT_XBOX input, int player, float currentValue);
	void doXboxStickChange(GE_INPUT_XBOX input, int player, float currentXAxis, float currentYAxis);

	// -------------------------------------------- //
	// ---------------- Window Input -------------- //
	// -------------------------------------------- //
public:
	void mouseMove(float coordX, float coordY);

private:
	XINPUT_STATE m_XBoxController[4];
	bool m_XBoxButtons[4][GE_INPUT_XBOX_PRESIONALBLE_NUMBER];
	float m_XBoxTrggers[4][2];
	float m_XBoxSticks[4][2][2];
	bool m_XBoxActiveController[4];
	int m_XBoxActiveCount;
	float m_XBoxCheckElapsed;


	// delegates
	vector<GEInputXBoxControllerProtocol*> m_XBoxDelegates;
	vector<GEInputMouseProtocol*> m_mouseDelegtes;
};

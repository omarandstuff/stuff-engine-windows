#include "GEinput.h"

// ------------------------------------------------------------------------------ //
// -----------------------------  Singleton - Set up ---------------------------- //
// ------------------------------------------------------------------------------ //

GEInput* GEInput::sharedInstance()
{
	static GEInput sharedInstance;

	return &sharedInstance;
}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Update ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GEInput::update(float time)
{
	// Xbox 360 controllers check.
	readXBOXControllerState(time);
}

void GEInput::preUpdate()
{

}

void GEInput::posUpdate()
{

}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Update ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GEInput::readXBOXControllerState(float time)
{
	//Set the elapsed time for checking porposes.
	m_XBoxCheckElapsed += time;

	//if it is known that there is not controller just check every 5 seconds.
	for (int i = 0; i < 4; i++)
	{
		if (!(m_XBoxCheckElapsed < 5.0f && !m_XBoxActiveController[i]))
		{
			ZeroMemory(&m_XBoxController[i], sizeof(XINPUT_STATE));

			// Get the Xbox  360 controller state i.
			DWORD Result = XInputGetState(i, &m_XBoxController[i]);

			if (Result == ERROR_SUCCESS)
			{
				// This controller is connected.
				m_XBoxActiveController[i] = true;

				// Button A
				doXboxButtonCheck(GE_INPUT_XBOX_BUTTON_A, i, m_XBoxController[i].Gamepad.wButtons & XINPUT_GAMEPAD_A);
				
			}
			else
			{
				// Clear Buttons.
				if(m_XBoxActiveController[i])
					ZeroMemory(&m_XBoxButtons[i], sizeof(m_XBoxButtons[i]));

				// This controller is not conected;
				m_XBoxActiveController[i] = false;
			}
		}
	}

	if (m_XBoxCheckElapsed > 5.0f) m_XBoxCheckElapsed = 0.0f;
}

void GEInput::doXboxButtonCheck(GE_INPUT input, int player, bool currentCheck)
{
	bool recordCheck = m_XBoxButtons[player][input];
	if (recordCheck != currentCheck)
	{
		for (vector<GEInputXBoxControllerProtocol*>::iterator it = m_XBoxDelegates.begin(); it != m_XBoxDelegates.end(); it++)
		{
			if (currentCheck)
				(*it)->xBoxControllerButtonDown(input, player);
			else
				(*it)->xBoxControllerButtonUp(input, player);
		}
		m_XBoxButtons[player][input] = currentCheck;
	}
}

// ------------------------------------------------------------------------------ //
// ----------------------------- Delegate Management ---------------------------- //
// ------------------------------------------------------------------------------ //

void GEInput::addXBoxContollerDelegate(GEInputXBoxControllerProtocol* delegate)
{
	m_XBoxDelegates.push_back(delegate);
}

void GEInput::removeXBoxControllerDelegate(GEInputXBoxControllerProtocol* delegate)
{
	for (vector<GEInputXBoxControllerProtocol*>::iterator it = m_XBoxDelegates.begin(); it != m_XBoxDelegates.end(); it++)
	{
		if (*it._Ptr == delegate)
		{
			m_XBoxDelegates.erase(it);
			return;
		}
	}
}

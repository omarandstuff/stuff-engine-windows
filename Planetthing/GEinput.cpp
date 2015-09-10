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
				doXboxButtonCheck(GE_INPUT_XBOX_BUTTON_A, i, (m_XBoxController[i].Gamepad.wButtons & XINPUT_GAMEPAD_A) > 0);
				
				// Button B
				doXboxButtonCheck(GE_INPUT_XBOX_BUTTON_B, i, (m_XBoxController[i].Gamepad.wButtons & XINPUT_GAMEPAD_B) > 0);

				// Button X
				doXboxButtonCheck(GE_INPUT_XBOX_BUTTON_X, i, (m_XBoxController[i].Gamepad.wButtons & XINPUT_GAMEPAD_X) > 0);

				// Button Y
				doXboxButtonCheck(GE_INPUT_XBOX_BUTTON_Y, i, (m_XBoxController[i].Gamepad.wButtons & XINPUT_GAMEPAD_Y) > 0);

				// Button Back
				doXboxButtonCheck(GE_INPUT_XBOX_BUTTON_BACK, i, (m_XBoxController[i].Gamepad.wButtons & XINPUT_GAMEPAD_BACK) > 0);

				// Button Start
				doXboxButtonCheck(GE_INPUT_XBOX_BUTTON_START, i, (m_XBoxController[i].Gamepad.wButtons & XINPUT_GAMEPAD_START) > 0);

				// Button Left Bumper
				doXboxButtonCheck(GE_INPUT_XBOX_LBUMPER, i, (m_XBoxController[i].Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) > 0);

				// Button Right Bumper
				doXboxButtonCheck(GE_INPUT_XBOX_RBUMPER, i, (m_XBoxController[i].Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) > 0);

				// Button D Pad Right
				doXboxButtonCheck(GE_INPUT_XBOX_DPAD_RIGHT, i, (m_XBoxController[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) > 0);

				// Button D Pad Left
				doXboxButtonCheck(GE_INPUT_XBOX_DPAD_LEFT, i, (m_XBoxController[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) > 0);

				// Button D Pad Up
				doXboxButtonCheck(GE_INPUT_XBOX_DPAD_UP, i, (m_XBoxController[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) > 0);

				// Button D Pad Down
				doXboxButtonCheck(GE_INPUT_XBOX_DPAD_DOWN, i, (m_XBoxController[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) > 0);

				// Button Thumb Left
				doXboxButtonCheck(GE_INPUT_XBOX_THUMB_LEFT, i, (m_XBoxController[i].Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) > 0);

				// Button Thumb Right
				doXboxButtonCheck(GE_INPUT_XBOX_THUMB_RIGHT, i, (m_XBoxController[i].Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) > 0);

				// Trigger Right
				doXboxTriggerCheck(GE_INPUT_XBOX_RIGHT_TRIGGER, i, m_XBoxController[i].Gamepad.bRightTrigger / 255.0f);

				// Trigger Left
				doXboxTriggerCheck(GE_INPUT_XBOX_LEFT_TRIGGER, i, m_XBoxController[i].Gamepad.bLeftTrigger / 255.0f);

				// Stick Right
				doXboxStickChange(GE_INPUT_XBOX_RIGHT_STICK, i, m_XBoxController[i].Gamepad.sThumbRX / 32000.0f, m_XBoxController[i].Gamepad.sThumbRY / 32000.0f);

				// Stick Left
				doXboxStickChange(GE_INPUT_XBOX_LEFT_STICK, i, m_XBoxController[i].Gamepad.sThumbLX / 32000.0f, m_XBoxController[i].Gamepad.sThumbLY / 32000.0f);
			}
			else
			{
				// Clear Controller inf.
				if (m_XBoxActiveController[i])
				{
					ZeroMemory(&m_XBoxButtons[i], sizeof(m_XBoxButtons[i]));
					ZeroMemory(&m_XBoxTrggers[i], sizeof(m_XBoxTrggers[i]));
					ZeroMemory(&m_XBoxSticks[i], sizeof(m_XBoxSticks[i]));
				}
					

				// This controller is not conected;
				m_XBoxActiveController[i] = false;
			}
		}
	}

	if (m_XBoxCheckElapsed > 5.0f) m_XBoxCheckElapsed = 0.0f;
}

void GEInput::doXboxButtonCheck(GE_INPUT_XBOX input, int player, bool currentCheck)
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

void GEInput::doXboxTriggerCheck(GE_INPUT_XBOX input, int player, float currentValue)
{
	float recordCheck = m_XBoxTrggers[player][input - GE_INPUT_XBOX_LEFT_TRIGGER];
	if (recordCheck != currentValue)
	{
		for (vector<GEInputXBoxControllerProtocol*>::iterator it = m_XBoxDelegates.begin(); it != m_XBoxDelegates.end(); it++)
		{
			(*it)->xBoxControllerTriguerChange(input, player, currentValue);
		}
		m_XBoxTrggers[player][input - GE_INPUT_XBOX_LEFT_TRIGGER] = currentValue;
	}
}

void GEInput::doXboxStickChange(GE_INPUT_XBOX input, int player, float currentXAxis, float currentYAxis)
{
	float recordCheckX = m_XBoxSticks[player][input - GE_INPUT_XBOX_LEFT_STICK][0];
	float recordCheckY = m_XBoxSticks[player][input - GE_INPUT_XBOX_LEFT_STICK][1];
	if (recordCheckX != currentXAxis || recordCheckY != currentYAxis)
	{
		for (vector<GEInputXBoxControllerProtocol*>::iterator it = m_XBoxDelegates.begin(); it != m_XBoxDelegates.end(); it++)
		{
			(*it)->xBoxControllerStickChange(input, player, currentXAxis, currentYAxis);
		}
		m_XBoxSticks[player][input - GE_INPUT_XBOX_LEFT_STICK][0] = currentXAxis;
		m_XBoxSticks[player][input - GE_INPUT_XBOX_LEFT_STICK][1] = currentYAxis;
	}
}

// ------------------------------------------------------------------------------ //
// -------------------------------- Window Input -------------------------------- //
// ------------------------------------------------------------------------------ //

void GEInput::mouseMove(float coordX, float coordY)
{
	static float lastCoordX = coordX, lastCoordY = coordY;
	for (vector<GEInputMouseProtocol*>::iterator it = m_mouseDelegtes.begin(); it != m_mouseDelegtes.end(); it++)
	{
		(*it)->mouseMove(coordX, coordY);
		(*it)->mouseChange(coordX - lastCoordX, coordY - lastCoordY);
	}
	lastCoordX = coordX;
	lastCoordY = coordY;
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

void GEInput::addMouseDelegate(GEInputMouseProtocol* delegate)
{
	m_mouseDelegtes.push_back(delegate);
}

void GEInput::removeMouseDelegate(GEInputMouseProtocol* delegate)
{
	for (vector<GEInputMouseProtocol*>::iterator it = m_mouseDelegtes.begin(); it != m_mouseDelegtes.end(); it++)
	{
		if (*it._Ptr == delegate)
		{
			m_mouseDelegtes.erase(it);
			return;
		}
	}
}
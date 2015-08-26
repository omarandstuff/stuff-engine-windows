#include "GEanimation.h"

// ------------------------------------------------------------------------------ //
// ------------------------------- Initialization ------------------------------- //
// ------------------------------------------------------------------------------ //

GEAnimation::GEAnimation()
{
	GEUpdateCaller::sharedInstance()->addUpdateableSelector(this);
}

GEAnimation::GEAnimation(wstring filename)
{
	GEUpdateCaller::sharedInstance()->addUpdateableSelector(this);
	loadAnimationWithFileName(filename);
}

GEAnimation::~GEAnimation()
{
	GEUpdateCaller::sharedInstance()->removeSelector((void**)this);
}

// ------------------------------------------------------------------------------ //
// ----------------------------------- Playback --------------------------------- //
// ------------------------------------------------------------------------------ //

void GEAnimation::play()
{
	Playing = true;
}

void GEAnimation::stop()
{
	Playing = false;
	CurrentTime = 0;
	m_finalFrame = Frames[0];
	callSelectors();
}

void GEAnimation::pause()
{
	Playing = false;
}

// ------------------------------------------------------------------------------ //
// ------------------------------------ Update ---------------------------------- //
// ------------------------------------------------------------------------------ //

void GEAnimation::update(float time)
{
	if (!Playing) return;
	if (NumberOfFrames < 1) return;

	CurrentTime += time * (Reverse ? -1.0f : 1.0f);

	// Delta time can be huge, find the time in the future with a big delta time.
	while (CurrentTime > Duration) CurrentTime -= Duration;
	while (CurrentTime < 0.0f) CurrentTime += Duration;

	// Figure out which frame we're on.
	float frameIndex = CurrentTime * FrameRate;

	int preFrameIndex = (int)floorf(frameIndex);
	int posFrameIndex = (int)ceilf(frameIndex);
	preFrameIndex = preFrameIndex % NumberOfFrames;
	posFrameIndex = posFrameIndex % NumberOfFrames;

	float interpolation = frameIndex - floorf(frameIndex);

	GEFrame* preFrame = &Frames[preFrameIndex];
	GEFrame* posFrame = &Frames[posFrameIndex];

	for (int i = 0; i < (int)preFrame->Joints.size(); i++)
	{
		GEJoint* finalJoint = &m_finalFrame.Joints[i];
		GEJoint* preJoint = &preFrame->Joints[i];
		GEJoint* posJoint = &posFrame->Joints[i];

		finalJoint->Position = glm::lerp(preJoint->Position, posJoint->Position, interpolation);
		finalJoint->Orientation = glm::mix(preJoint->Orientation, posJoint->Orientation, interpolation);
	}

	// Interpolate bounds.
	m_finalFrame.Bound.MaxBound = glm::lerp(preFrame->Bound.MaxBound, posFrame->Bound.MaxBound, interpolation);
	m_finalFrame.Bound.MinBound = glm::lerp(preFrame->Bound.MinBound, posFrame->Bound.MinBound, interpolation);

	callSelectors();
}

void GEAnimation::callSelectors()
{
	// Update every selector
	for (vector<GEAnimationProtocol*>::iterator it = m_selectors.begin(); it != m_selectors.end(); it++)
		(*it)->poseForFrameDidFinish(&m_finalFrame);
}

// ------------------------------------------------------------------------------ //
// ----------------------------- Selector Management ---------------------------- //
// ------------------------------------------------------------------------------ //

void GEAnimation::addSelector(GEAnimationProtocol* selector)
{
	m_selectors.push_back(selector);
}

void GEAnimation::removeSelector(void** selector)
{
	for (vector<GEAnimationProtocol*>::iterator it = m_selectors.begin(); it != m_selectors.end(); it++)
	{
		if (it._Ptr == (GEAnimationProtocol**)selector)
		{
			m_selectors.erase(it);
			return;
		}
	}
}

// ------------------------------------------------------------------------------ //
// --------------------------- Load - Import - Export --------------------------- //
// ------------------------------------------------------------------------------ //

void GEAnimation::loadAnimationWithFileName(wstring filename)
{
	if (filename == L"") return;

	wstring fileType = filename.substr(filename.find_last_of(L".") + 1);
	wstring filePath = filename.substr(0, filename.find_last_of(L"."));

	FileName = filename;

	// Decide what load method to use.
	if (fileType == L"md5anim")
		Ready = loadMD5WithFileName(filePath);

	// The file was loaded successfully
	if (Ready)
	{
		m_frameDuration = 1.0f / (float)FrameRate;
		Duration = m_frameDuration * (float)NumberOfFrames;
	}
}

bool GEAnimation::loadMD5WithFileName(wstring filename)
{
	wfstream wStream((filename + L".md5anim").c_str());

	if (!wStream)
		return false;

	// Animation counters.
	unsigned int numberOfJoints = 0;
	unsigned int numberOfAnimatedComponents = 0;

	//Joints
	vector<wstring> jointNames;
	struct jointInf
	{
		int parentID;
		int flags;
		int startData;
	};
	struct jointInf* jointInfs = 0;


	wchar_t line[256];
	while (wStream.getline(line, 256))
	{
		wstringstream newLine(line, wstringstream::in);
	}
	

	return true;
}

float GEAnimation::computeWComponentOfQuaternion(glm::quat quaternion)
{
	return 0.0;
}

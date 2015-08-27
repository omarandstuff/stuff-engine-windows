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
	struct jointInf
	{
		wstring name;
		int parentID;
		int flags;
		int startData;
	};
	vector<jointInf> jointInfs;

	// Bounds
	struct bound
	{
		float maxX, maxY, maxZ;
		float minX, minY, minZ;
	};
	vector<bound> bounds;

	// Frames
	vector<vector<float> > frameDatas;

	wchar_t line[256];
	while (wStream.getline(line, 256))
	{
		wistringstream newLine(line, wistringstream::in);

		wstring first;
		newLine >> first;

		if (first == L"")
			continue;

		if (first == L"numFrames") // Line with the number of frames in the animation.
		{
			newLine >> NumberOfFrames;;
			continue;
		}
		else if (first == L"numJoints") // Line with the number of joints to read.
		{
			newLine >> numberOfJoints;
			continue;
		}
		else if (first == L"frameRate") // Line with the frame rate of the animation.
		{
			newLine >> FrameRate;
			continue;
		}
		else if (first == L"numAnimatedComponents") // Line with the number of animated componen per frame.
		{
			newLine >> numberOfAnimatedComponents;
			continue;
		}
		else if (first == L"hierarchy")
		{
			// Fill the data holder with every joint line.
			for (unsigned int i = 0; i < numberOfJoints; i++)
			{
				jointInf curretJoint;
				// Joint line.
				wStream.getline(line, 256);
				wistringstream jointLine(line, wistringstream::in);

				// Name.
				wstring name, nameBuffer;
				jointLine >> nameBuffer;
				name = nameBuffer;
				while (nameBuffer.back() != L'\"')
				{
					jointLine >> nameBuffer;
					name += L" " + nameBuffer;
				}

				// Data.
				curretJoint.name = name;
				jointLine >> curretJoint.parentID;
				jointLine >> curretJoint.flags;
				jointLine >> curretJoint.startData;

				jointInfs.push_back(curretJoint);
			}
		}
		else if (first == L"bounds")
		{
			bound currentBound;
			// Fill the data holder with every bound line.
			for (unsigned int i = 0; i < NumberOfFrames; i++)
			{
				// Bound line.
				wStream.getline(line, 256);
				wistringstream boundLine(line, wistringstream::in);

				// New Bound.
				boundLine >> currentBound.minX;
				boundLine >> currentBound.minZ;
				currentBound.minZ *= -1.0f;
				boundLine >> currentBound.minY;
				boundLine >> currentBound.maxX;
				boundLine >> currentBound.maxZ;
				currentBound.maxZ *= -1.0f;
				boundLine >> currentBound.maxY;

				bounds.push_back(currentBound);
			}
		}
		else if (first == L"baseframe")
		{
			// Make a joint object for each joint line.
			for (unsigned int i = 0; i < numberOfJoints; i++)
			{
				// Joint line.
				wStream.getline(line, 256);
				wistringstream jointLine(line, wistringstream::in);

				// New joint.
				GEJoint currentJoint;

				// Position data.
				jointLine >> currentJoint.Position.x;
				jointLine >> currentJoint.Position.y;
				jointLine >> currentJoint.Position.z;

				// Orientation data.
				jointLine >> currentJoint.Orientation.x;
				jointLine >> currentJoint.Orientation.y;
				jointLine >> currentJoint.Orientation.z;
				computeWComponentOfQuaternion(currentJoint.Orientation);

				// Add new joint.
				m_finalFrame.Joints.push_back(currentJoint);
			}
		}
		else if (first == L"frame")
		{
			// Frame index
			unsigned int frameIndex;
			newLine >> frameIndex;

			// Fill the data with all the next data lines.
			unsigned int dataIndex = 0;
			unsigned int remainDatas = numberOfAnimatedComponents;
			do
			{
				// Joint line.
				wStream.getline(line, 256);
				wistringstream jointLine(line, wistringstream::in);

				vector<float> currentFrameData;

				do
				{
					float currentData;
					jointLine >> currentData;
					currentFrameData.push_back(currentData);
					remainDatas--;
				} while (jointLine.rdbuf()->in_avail() != 0);

				if (!remainDatas)frameDatas.push_back(currentFrameData);

			} while (remainDatas);
		}
	}

	return true;
}

void GEAnimation::computeWComponentOfQuaternion(glm::quat& quaternion)
{
	float t = 1.0f - (quaternion.x * quaternion.x) - (quaternion.y * quaternion.y) - (quaternion.z * quaternion.z);
	quaternion.w = t < 0.0f ? 0.0f : -sqrtf(t);
}

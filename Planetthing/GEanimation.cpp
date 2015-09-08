#include "GEanimation.h"

// ------------------------------------------------------------------------------ //
// ------------------------------- Initialization ------------------------------- //
// ------------------------------------------------------------------------------ //

GEAnimation::GEAnimation()
{
	GEUpdateCaller::sharedInstance()->addUpdateableDelegate(this);
}

GEAnimation::GEAnimation(wstring filename) : GEAnimation::GEAnimation()
{
	loadAnimationWithFileName(filename);
}

GEAnimation::~GEAnimation()
{
	GEUpdateCaller::sharedInstance()->removeDelegate(this);
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
	callDelegates();
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

	GEFrame* preFrame = Frames[preFrameIndex];
	GEFrame* posFrame = Frames[posFrameIndex];

	for (int i = 0; i < (int)preFrame->Joints.size(); i++)
	{
		GEJoint* finalJoint = m_finalFrame->Joints[i];
		GEJoint* preJoint = preFrame->Joints[i];
		GEJoint* posJoint = posFrame->Joints[i];

		finalJoint->Position = glm::lerp(preJoint->Position, posJoint->Position, interpolation);
		finalJoint->Orientation = glm::mix(preJoint->Orientation, posJoint->Orientation, interpolation);
	}

	// Interpolate bounds.
	m_finalFrame->Bounds.MaxBound = glm::lerp(preFrame->Bounds.MaxBound, posFrame->Bounds.MaxBound, interpolation);
	m_finalFrame->Bounds.MinBound = glm::lerp(preFrame->Bounds.MinBound, posFrame->Bounds.MinBound, interpolation);

	callDelegates();
}

void GEAnimation::callDelegates()
{
	// Update every selector
	for (vector<GEAnimationProtocol*>::iterator it = m_delegates.begin(); it != m_delegates.end(); it++)
		(*it)->poseForFrameDidFinish(m_finalFrame);
}

// ------------------------------------------------------------------------------ //
// ----------------------------- Delegate Management ---------------------------- //
// ------------------------------------------------------------------------------ //

void GEAnimation::addDelegate(GEAnimationProtocol* delegate)
{
	m_delegates.push_back(delegate);
}

void GEAnimation::removeDelegate(GEAnimationProtocol* delegate)
{
	for (vector<GEAnimationProtocol*>::iterator it = m_delegates.begin(); it != m_delegates.end(); it++)
	{
		if (*it._Ptr == delegate)
		{
			m_delegates.erase(it);
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
	vector<GEBound> bounds;

	// Frames
	vector<vector<float> > frameDatas;

	m_finalFrame = new GEFrame;

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
			GEBound currentBound;
			// Fill the data holder with every bound line.
			for (unsigned int i = 0; i < NumberOfFrames; i++)
			{
				// Bound line.
				wStream.getline(line, 256);
				wistringstream boundLine(line, wistringstream::in);

				// New Bound.
				wstring junk;
				boundLine >> junk;

				boundLine >> currentBound.MinBound.x;
				boundLine >> currentBound.MinBound.z;
				boundLine >> currentBound.MinBound.y;
				boundLine >> junk >> junk;
				boundLine >> currentBound.MaxBound.x;
				boundLine >> currentBound.MaxBound.z;
				boundLine >> currentBound.MaxBound.y;

				// Flip ZY
				currentBound.MinBound.z *= -1.0f;
				currentBound.MaxBound.z *= -1.0f;

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
				GEJoint* currentJoint = new GEJoint;

				wstring junk;
				jointLine >> junk;

				// Position data.
				jointLine >> currentJoint->Position.x;
				jointLine >> currentJoint->Position.y;
				jointLine >> currentJoint->Position.z;

				jointLine >> junk;
				jointLine >> junk;

				// Orientation data.
				jointLine >> currentJoint->Orientation.x;
				jointLine >> currentJoint->Orientation.y;
				jointLine >> currentJoint->Orientation.z;

				// Add new joint.
				m_finalFrame->Joints.push_back(currentJoint);
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

			frameDatas.push_back(vector<float>());
			vector<vector<float> >::iterator currentFrameData = frameDatas.end() - 1;

			do
			{
				// Joint line.
				wStream.getline(line, 256);
				wistringstream jointLine(line, wistringstream::in);

				do
				{
					float currentData;
					jointLine >> currentData;
					currentFrameData->push_back(currentData);
					remainDatas--;
				} while (jointLine.rdbuf()->in_avail() != 0);

			} while (remainDatas);
		}
	}

	// Build frames
	for (unsigned int i = 0; i < NumberOfFrames; i++)
	{
		// New Frame
		GEFrame* currentFrame = new GEFrame;

		// Fill bound inf.

		currentFrame->Bounds = bounds[i];

		// Frame data
		vector<float>* currentFrameData = &frameDatas[i];

		// Calculate every new joint based on the base frame.
		for (unsigned int j = 0; j < numberOfJoints; j++)
		{
			// BaseJoint
			GEJoint* baseJoint = m_finalFrame->Joints[j];
			jointInf* baseJointInf = &jointInfs[j];

			// New joint
			GEJoint* currentJoint = new GEJoint;

			currentJoint->Position = baseJoint->Position;
			currentJoint->Orientation = baseJoint->Orientation;

			// Parenting
			currentJoint->Parent = baseJointInf->parentID != -1 ? currentFrame->Joints[baseJointInf->parentID] : 0;

			// Flags that tell what member in position and orientation is been modified.
			unsigned int o = 0;
			if (baseJointInf->flags & 1)
				currentJoint->Position.x = (*currentFrameData)[baseJointInf->startData + o++];
			if (baseJointInf->flags & 2)
				currentJoint->Position.y = (*currentFrameData)[baseJointInf->startData + o++];
			if (baseJointInf->flags & 4)
				currentJoint->Position.z = (*currentFrameData)[baseJointInf->startData + o++];
			if (baseJointInf->flags & 8)
				currentJoint->Orientation.x = (*currentFrameData)[baseJointInf->startData + o++];
			if (baseJointInf->flags & 16)
				currentJoint->Orientation.y = (*currentFrameData)[baseJointInf->startData + o++];
			if (baseJointInf->flags & 32)
				currentJoint->Orientation.z = (*currentFrameData)[baseJointInf->startData + o++];

			computeWComponentOfQuaternion(currentJoint->Orientation);

			if (currentJoint->Parent != 0) // Has a parent joint
			{
				glm::vec3 rotPosition = currentJoint->Parent->Orientation * currentJoint->Position;

				currentJoint->Position = currentJoint->Parent->Position + rotPosition;
				currentJoint->Orientation = glm::normalize(currentJoint->Parent->Orientation * currentJoint->Orientation);
			}

			// Push the new joint.
			currentFrame->Joints.push_back(currentJoint);
		}

		// Push the new frame.
		Frames.push_back(currentFrame);
	}

	return true;
}

void GEAnimation::computeWComponentOfQuaternion(glm::quat& quaternion)
{
	float t = 1.0f - (quaternion.x * quaternion.x) - (quaternion.y * quaternion.y) - (quaternion.z * quaternion.z);
	quaternion.w = t < 0.0f ? 0.0f : -sqrtf(t);
}

#pragma once
#include "stdafx.h"

namespace Networking
{
	class GameBitBuffer;
}
class Extension
{
public:
	Extension(void);
	~Extension(void);

	static Ogre::Vector3 ParseV3(Networking::GameBitBuffer* buffer);
	static Ogre::Quaternion ParseQ(Networking::GameBitBuffer* buffer);
	static void EncodeV3(Ogre::Vector3 _vector3, Networking::GameBitBuffer* buffer);
	static void EncodeQ(Ogre::Quaternion _q, Networking::GameBitBuffer* buffer);
};


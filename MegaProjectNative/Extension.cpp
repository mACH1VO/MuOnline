#include "StdAfx.h"
#include "Extension.h"
#include "GameBitBuffer.h"

Extension::Extension(void)
{
}


Extension::~Extension(void)
{
}

Ogre::Vector3 Extension::ParseV3(Networking::GameBitBuffer* buffer)
{
	Ogre::Vector3 v3;
	v3.x = buffer->ReadFloat32();
	v3.y = buffer->ReadFloat32();
	v3.z = buffer->ReadFloat32();
	return v3;
}
Ogre::Quaternion Extension::ParseQ(Networking::GameBitBuffer* buffer)
{
	Ogre::Quaternion q;
	q.x = buffer->ReadFloat32();
	q.y = buffer->ReadFloat32();
	q.z = buffer->ReadFloat32();
	q.w = buffer->ReadFloat32();
	return q;
}

void Extension::EncodeV3(Ogre::Vector3 _vector3, Networking::GameBitBuffer* buffer)
{
	buffer->WriteFloat32(_vector3.x);
	buffer->WriteFloat32(_vector3.y);
	buffer->WriteFloat32(_vector3.z);
}

void Extension::EncodeQ(Ogre::Quaternion _q, Networking::GameBitBuffer* buffer)
{
	buffer->WriteFloat32(_q.x);
	buffer->WriteFloat32(_q.y);
	buffer->WriteFloat32(_q.z);
	buffer->WriteFloat32(_q.w);
}

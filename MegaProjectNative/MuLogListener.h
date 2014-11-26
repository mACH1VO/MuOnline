#pragma once
#include "stdafx.h"
#include "Ogre.h"
//#include "GameFramework.h"

using namespace Ogre;

class MuLogListener : public LogListener
{
public:
	MuLogListener(void);
	~MuLogListener(void);
	virtual void messageLogged( const String& message, LogMessageLevel lml, bool maskDebug, const String &logName, bool& skipThisMessage );
};


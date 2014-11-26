// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>

// stdafx.h

// Ogre headers you need
#include <Ogre.h>
/*#include <OgreException.h>
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>*/

#include "OIS.h"
#include "OISEvents.h"
#include "OISInputManager.h"
#include "OISKeyboard.h"
#include "OISMouse.h"

#include "MyGUI.h"
#include "MyGUI_OgrePlatform.h"

//#include "ParticleUniverse/ParticleUniverseSystemManager.h"

// any other header can be included, as usual
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


//#define RENDER_QUEUE_INVENTORY_ITEM_GLOW	RENDER_QUEUE_OVERLAY + 2

#define RENDER_QUEUE_GLOW_OBJECTS			RENDER_QUEUE_MAIN + 3
#define RENDER_QUEUE_OUTLINE_GLOW_GLOWS		RENDER_QUEUE_MAIN + 4

// stencil values
#define STENCIL_VALUE_FOR_OUTLINE_GLOW 1
#define STENCIL_VALUE_FOR_FULL_GLOW 2
#define STENCIL_FULL_MASK 0xFFFFFFFF

using namespace std;

// TODO: reference additional headers your program requires here

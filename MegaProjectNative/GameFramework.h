#pragma once
#include "stdafx.h"

#include "Ogre.h"
#include "OgreTerrain.h"
#include "OgreTerrainGroup.h"
#include "OgreOverlaySystem.h"

#include "CameraMan.h"

//#include "Hydrax.h"
//#include "Noise/Perlin/Perlin.h"
//#include "Modules/ProjectedGrid/ProjectedGrid.h"

class DotSceneLoader;
class GameGUI;
class MuLogListener;
class MuRenderQueueListener;
//class GameClient;

namespace Networking
{
	class GameClient;
}

namespace Game
{
	class Player;
	class Factory;
	class InventoryItem;
}

bool IsMouseOverWindow(HWND hWnd, const int mx, const int my,
	const bool inClientSpace /*= false */);

using namespace Ogre;

class GameFramework : public Ogre::Singleton<GameFramework>, OIS::KeyListener, OIS::MouseListener, Ogre::FrameListener
{
public:
	GameFramework(void);
	~GameFramework(void);

	int FACTOR_INVENTORY_SIZE_POSITION;
	HWND windowHandle;
	Root *Root;
	RenderSystem *renderSystem;
	SceneManager *sceneManager;
	RenderWindow *window;
	//CameraMan CameraMan;
	Camera *camera;
	
	Viewport *Viewport;
	CameraMan* cameraMan;
	Log* log;
	Timer* pTimer;
	Timer* mFPSLimiterTimer;

	OIS::InputManager* inputManager;
	OIS::Mouse* pMouse;
	OIS::Keyboard* pKeyboard;

	OverlaySystem* pOverlaySystem;
	Overlay* debugOverlay;

	MyGUI::Gui* mGUI;
	MyGUI::OgrePlatform* mPlatform;

	Entity* floor_;

	//Hydrax::Hydrax* mHydrax;

	bool isMBLeftPressed;
	bool isMBRightPressed;

	int lastMouseX;
	int lastMouseY;


	virtual bool keyPressed(const OIS::KeyEvent &keyEventRef);
	virtual bool keyReleased(const OIS::KeyEvent &keyEventRef);

	virtual bool mouseMoved(const OIS::MouseEvent &evt);
	virtual bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

	virtual bool frameStarted(const FrameEvent& evt);
	virtual bool frameRenderingQueued(const FrameEvent& evt);
	virtual bool frameEnded(const FrameEvent& evt);

	GameGUI* getGameGUI();
	Networking::GameClient* getGameClient();
	Game::Factory* getFactory();

	Game::Player* mainPlayer;
	Game::InventoryItem *itemOnAir;
	Game::InventoryItem* currentInventoryItemHovered;

	SceneNode* sn_ogrehead;

	void ClickedButton(MyGUI::WidgetPtr _sender);

	void Start();

private:

	MuLogListener* _mulogListener;
	MuRenderQueueListener* _muRenderQueueListener;
	void _preInitialize();
	void _createRoot();
	void _createRenderSystem();
	void _createCamera();
	void _loadResources();
	void _createInput();
	void _postInitialize();

	GameGUI * _gameGUI;
	Networking::GameClient * _gameClient;
	Game::Factory* _factory;

protected:
	void createScene();
	void createGUI();
	//void createPhysicsEngine();
};
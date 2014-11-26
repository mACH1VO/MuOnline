#pragma once
#include "StdAfx.h"
#include "GameFramework.h"
#include "MUEnums.h"
#include "DotSceneLoader.h"
/*#include "PagedGeometry.h"
#include "GrassLoader.h"
#include "BatchPage.h"
#include "ImpostorPage.h"
#include "TreeLoader3D.h"*/


#include "Factory.h"
#include "GameGUI.h"
#include "GameClient.h"
#include "InventoryItem.h"

#include "MuLogListener.h"
#include "MuRenderQueueListener.h"
#include "GameGlobals.h"

#include "Map.h"
#include "Storage.h"

#include "ProfilingPanel.h"

#include "TestCompositorListener.h"
#include "GFXManager.h"
#include "BitConverterUtil.h"
#include "GameAttributeUtil.h"


//#define MAX_LAYERS_ALLOWED 6

using namespace Forests;

template<> GameFramework* Ogre::Singleton<GameFramework>::msSingleton = 0;

GameFramework::GameFramework(void)
{
	//this->mLoader = 0;
	this->mainPlayer = 0;
	this->_factory = 0;
	this->_mulogListener = 0;
	this->_muRenderQueueListener = 0;
	this->sn_ogrehead = 0;

	this->isMBLeftPressed = false;
	this->isMBRightPressed = false;

	this->lastMouseX = 0;
	this->lastMouseY = 0;

	MyGUI::IRenderTarget* rt;
	MyGUI::ILogListener* ll;
	MyGUI::OgreRenderManager* orm;

	this->itemOnAir = 0;
	this->currentInventoryItemHovered = 0;

	this->FACTOR_INVENTORY_SIZE_POSITION = 1;
}

GameFramework::~GameFramework(void)
{
	/*mGUI->shutdown();
	delete mGUI;
	mGUI = 0;   
	mPlatform->shutdown();
	delete mPlatform;
	mPlatform = 0;*/
}

void GameFramework::Start()
{
	this->_preInitialize();
	this->_createRoot();

	/*Thread.Sleep(1000);*/
	this->log = LogManager::getSingleton().getLog("Ogre.log");
	this->log->setDebugOutputEnabled(true);
	this->log->setTimeStampEnabled(true);

	//log.MessageLogged += new LogListener.MessageLoggedHandler(MegaProject.Logging.Logger.log_MessageLogged);

	this->_createRenderSystem();

	this->pOverlaySystem = new Ogre::OverlaySystem();

	this->_createCamera();
	this->_loadResources();
	this->_createInput();
	this->createScene();

	this->sceneManager->addRenderQueueListener(pOverlaySystem);

	this->_muRenderQueueListener = new MuRenderQueueListener();
	this->sceneManager->addRenderQueueListener(this->_muRenderQueueListener);

	this->createGUI();
	
	this->_postInitialize();
	this->Root->addFrameListener(this);
	this->Root->startRendering();
}

void GameFramework::_preInitialize()
{

}

void GameFramework::_createRoot()
{
	this->Root = new Ogre::Root("plugins.cfg");
	//Ogre::RenderSystem *rs = myroot->getRenderSystemByName("Direct3D9 Rendering Subsystem"/*"Direct3D11 Rendering Subsystem"*//*"OpenGL Rendering Subsystem"*/);
	//myroot->showConfigDialog();
}

void GameFramework::_createRenderSystem()
{
	uint WIDTH = 1280;
	uint HEIGHT = 720;
	CompositorInstance* ci;
	//this.RWAspectRatio = AspectRatio._4_3;
	//Ogre::RenderSystemList* rsl = this->Root->getAvailableRenderers();
	this->renderSystem = this->Root->getRenderSystemByName("Direct3D9 Rendering Subsystem"/*"Direct3D11 Rendering Subsystem"*//*"OpenGL Rendering Subsystem"*/);
	this->renderSystem->setConfigOption("Full Screen", "false");
	this->renderSystem->setConfigOption("Video Mode", "1280 x 720 @ 32-bit colour");
	//RenderSystem.SetConfigOption("border", "fixed");
	Root->setRenderSystem(renderSystem);

	if (/*Root->showConfigDialog()*/true)
	{
		//this->window = this->Root->initialise(true, "MU2");
		ConfigOptionMap com = this->renderSystem->getConfigOptions();

		NameValuePairList extraparam;
		extraparam["border"] = "fixed";
		extraparam["vsync"] = "false";
		//extraparam["FSAA"] = "8 [Quality]";
		extraparam["FSAA"] = "0";

		this->window = this->Root->initialise(false, "MU");
		this->window = this->Root->createRenderWindow("MU",WIDTH, HEIGHT, FALSE, &extraparam);

		this->window->setDeactivateOnFocusChange(false);

	}
	else
	{
		LogManager::getSingleton().logMessage("root showconfigdialog false error");
	}

	//CREATE SCENE MANAGER

	this->sceneManager = Root->createSceneManager(Ogre::SceneType::ST_EXTERIOR_CLOSE);
	Entity::setDefaultQueryFlags(QueryFlags::DEFAULT_MASK);


}

void GameFramework::_createCamera()
{
	RenderTarget* rt;
	this->camera = this->sceneManager->createCamera("MainCamera");

	this->sceneManager->getRootSceneNode()->createChildSceneNode("Camera")->attachObject(this->camera);

	//Camera.Position = new Vector3(0, 10, 25);
	this->camera->getParentSceneNode()->setPosition(Vector3(0, 10, 25)*20);

	this->camera->lookAt(Vector3(0, 0, 0));

	/*this->camera2 = this->sceneManager->createCamera("camera2");
	this->camera2->setPosition(Vector3(10,0,10)*5);
	this->camera2->lookAt(Vector3::ZERO);*/

	camera->setAutoAspectRatio(true);

	this->camera->setNearClipDistance(0.1f);
	//Camera.ProjectionType = ProjectionType.PT_ORTHOGRAPHIC;

	this->cameraMan = new CameraMan(this->camera);

	// Create one viewport, entire window
	this->Viewport = this->window->addViewport(camera);
	//this->window->addViewport(this->camera2);
	this->Viewport->setBackgroundColour(ColourValue(0.5f, 0.5f, 0.5f));
	//this->camera->setAspectRatio((float)this->Viewport->getActualHeight() / (float)this->Viewport->getActualHeight());


	//este va despues, para usar el viewport.>getActialWidth
	int actual_width = this->Viewport->getActualWidth();
	int actual_height = this->Viewport->getActualHeight();

	actual_width = actual_width / this->FACTOR_INVENTORY_SIZE_POSITION;
	actual_height = actual_height / this->FACTOR_INVENTORY_SIZE_POSITION;

	this->cameraMan->camera_ortho_tricker = this->sceneManager->createCamera("camera_ortho_tricker");
	this->sceneManager->getRootSceneNode()->createChildSceneNode("camera_ortho_tricker_sn")->attachObject(this->cameraMan->camera_ortho_tricker);
	this->cameraMan->camera_ortho_tricker->setAutoAspectRatio(true);
	this->cameraMan->camera_ortho_tricker->getParentSceneNode()->setPosition(Vector3((actual_width / 2), ( -actual_height / 2 ), 1000));
	this->cameraMan->camera_ortho_tricker->lookAt(Vector3(( actual_width / 2 ), ( -actual_height / 2 ), 0));
	this->cameraMan->camera_ortho_tricker->setProjectionType(Ogre::ProjectionType::PT_ORTHOGRAPHIC);
	this->cameraMan->camera_ortho_tricker->setOrthoWindow(actual_width, actual_height);
}

void GameFramework::_loadResources()
{
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	//LoadingBar loadingBar = new LoadingBar();
	//loadingBar.Start(Window, 1, 1, 0.75F);

	//Load resource paths from config file
	ConfigFile cf ;
	cf.load("resources.cfg", "\t:=", true);

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	Ogre::String sec, type, arch;

	while (seci.hasMoreElements())
	{
		sec = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		// go through all resource paths
		for (i = settings->begin(); i != settings->end(); i++)
		{
			type = i->first;
			arch = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
		}
	}

	//Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../../Media/Compositor", "FileSystem", "General");
	//Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../../Media/Compositor/Invert", "FileSystem", "General");

	//arch = "../../Media/Fonts"
	//E:\MegaProjectNative\Media\Compositor

	 Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	 this->pTimer = new Ogre::Timer();
	 this->pTimer->reset();

	 this->mFPSLimiterTimer = new Ogre::Timer();
	 this->mFPSLimiterTimer->reset();
}

void GameFramework::_createInput()
{
	size_t hWnd = 0;
	OIS::ParamList paramList;
	window->getCustomAttribute("WINDOW", &hWnd);

	paramList.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));
	this->windowHandle = (HWND)hWnd;

	//paramList.insert(OIS::ParamList::value_type("w32_mouse", "DISCL_EXCLUSIVE"));
	//paramList.insert(OIS::ParamList::value_type("w32_mouse", "DISCL_NONEXCLUSIVE"));
	//paramList.insert(OIS::ParamList::value_type("w32_mouse", "DISCL_FOREGROUND"));

	paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));

	this->inputManager = OIS::InputManager::createInputSystem(paramList);

	this->pKeyboard = static_cast<OIS::Keyboard*>(this->inputManager->createInputObject(OIS::OISKeyboard, true));
	this->pMouse = static_cast<OIS::Mouse*>(this->inputManager->createInputObject(OIS::OISMouse, true));
	int aa = this->window->getHeight();
	this->pMouse->getMouseState().height = this->window->getHeight();
	this->pMouse->getMouseState().width	 = this->window->getWidth();

	/*const OIS::MouseState &mouseState = pMouse->getMouseState(); // mMouse is type of OIS::Mouse*
	mouseState.width = 1024; // your rendering area width
	mouseState.height = 768; // your rendering area height*/

	this->pKeyboard->setEventCallback(this);
	this->pMouse->setEventCallback(this);

}

void GameFramework::createGUI()
{
	mPlatform = new MyGUI::OgrePlatform();
	mPlatform->initialise(this->window, this->sceneManager); // mWindow is Ogre::RenderWindow*, mSceneManager is Ogre::SceneManager*
	mGUI = new MyGUI::Gui();
	mGUI->initialise();

	/*MyGUI::ButtonPtr button = mGUI->createWidget<MyGUI::Button>("Button", 10, 10, 300, 26, MyGUI::Align::Default, "Main");
	button->setCaption("exit");
	// set callback
	button->eventMouseButtonClick += MyGUI::newDelegate(this, &GameFramework::ClickedButton);*/ // CLASS_POINTER is pointer to instance of a CLASS_NAME (usually '''this''')


	// load layout
	
	//MyGUI::LayoutManager::getInstance().loadLayout("PanelView.layout");
	//MyGUI::LayoutManager::getInstance().loadLayout("ProfilingPanel.layout");
	//MyGUI::LayoutManager::getInstance().loadLayout("MenuPanel.layout");

	//MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize()); //Uncomment this line if you want to align worked immediately after loading layout
	// set callback

    //MyGUI::ButtonPtr button = mGUI->findWidget<MyGUI::Button>("MyFirstButton");
	//button->eventMouseButtonClick += MyGUI::newDelegate(this, &GameFramework::ClickedButton); // CLASS_POINTER is pointer to CLASS_NAME ('''this''')


	//MyGUI::TextBox* fps_textbox = (MyGUI::TextBox*)MyGUI::Gui::getInstance().findWidgetT("fps_textbox");
	

	//this->pKeyboard->setEventCallback(this->_gameGUI);
	//this->pMouse->setEventCallback(this->_gameGUI);

}

void GameFramework::ClickedButton(MyGUI::WidgetPtr _sender)
{
	String fps = StringConverter::toString(this->window->getLastFPS());
	((MyGUI::Button *)_sender)->setCaption(fps);
}

void GameFramework::createScene()
{
	/*Entity* ogrehead = this->sceneManager->createEntity("Mikki.mesh");
	sn_ogrehead = this->sceneManager->getRootSceneNode()->createChildSceneNode();
	sn_ogrehead->attachObject(ogrehead);
	sn_ogrehead->setPosition(Vector3(1280, -720, 0));
	sn_ogrehead->setScale(Vector3::UNIT_SCALE * 0.3);*/

	/*ogrehead->setRenderQueueGroupAndPriority(RenderQueueGroupID::RENDER_QUEUE_MAX,1);*/

	//Ogre::uint8 t = ogrehead->getRenderQueueGroup();

	//ogrehead->getMesh()->_setBounds(Ogre::AxisAlignedBox(Ogre::AxisAlignedBox::EXTENT_INFINITE));
	
	this->camera->setOrthoWindow(this->Viewport->getActualWidth(), this->Viewport->getActualHeight());

	//ogrehead->setRenderQueueGroup(Ogre::RenderQueueGroupID::
	
	this->sceneManager->setSkyBox(true, "Sky/Clouds");

	//this->Viewport->setBackgroundColour(ColourValue(1.0f, 1.0f, 0.8f));
	//this->sceneManager->setFog(Ogre::FOG_LINEAR, ColourValue(0.5f, 0.5f, 0.5f), 1, 15, 100);

	// set shadow properties
	//this->sceneManager->setShadowTexturePixelFormat(Ogre::PF_FLOAT16_R);
	this->sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED);
	//this->sceneManager->setShadowTechnique(ShadowTechnique::SHADOWTYPE_TEXTURE_MODULATIVE);
	this->sceneManager->setShadowTextureSelfShadow(true);

	//this->sceneManager->setShadowTextureCasterMaterial("Ogre/DepthShadowmap/Caster/Float");
	//this->sceneManager->setShadowTextureReceiverMaterial("ShadowReceiver");

	//this->sceneManager->setShadowTexturePixelFormat(Ogre::PixelFormat::PF_FLOAT32_R);
	//this->sceneManager->setShadowCasterRenderBackFaces(false);

	this->sceneManager->setShadowColour(ColourValue::Red/* * 0.4*/);
	this->sceneManager->setShadowTextureSize(1024);
	this->sceneManager->setShadowTexturePixelFormat(PixelFormat::PF_R8G8B8A8);
	this->sceneManager->setShadowTextureCount(1);
	this->sceneManager->setShadowFarDistance(140);

	// use a small amount of ambient lighting
	this->sceneManager->setAmbientLight(ColourValue(0.3, 0.3, 0.3));

	// add a bright light above the scene
	Light* light = this->sceneManager->createLight();
	light->setType(Light::LightTypes::LT_DIRECTIONAL);
	light->setPosition(-100, 40, 20);
	light->setDirection(-1.5, -1, -1);
	light->setSpecularColour(ColourValue::White);

	// create a floor mesh resource
	/*MeshManager::getSingleton().createPlane("floor_", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0), 100, 100, 10, 10, true, 1, 10, 10, Vector3::UNIT_Z);

	// create a floor entity, give it a material, and place it at the origin
	Entity* floor1 = this->sceneManager->createEntity("Floor", "floor_");
	floor1->setMaterialName("Examples/Rockwall");
	floor1->setCastShadows(false);
	this->sceneManager->getRootSceneNode()->attachObject(floor1);

	this->floor_ = floor1;*/


	/*this->sceneManager->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
	Ogre::Light* light = this->sceneManager->createLight( "MainLight" );
	light->setPosition(20, 40, 20);
	light->setCastShadows(true);*/

	// create a floor mesh resource
	/*MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0), 100, 100, 10, 10, true, 1, 10, 10, Vector3::UNIT_Z);

	// create a floor entity, give it a material, and place it at the origin
	Entity* floor = this->sceneManager->createEntity("Floor", "floor");
	floor->setMaterialName("Examples/Rockwall");
	floor->setCastShadows(false);
	this->sceneManager->getRootSceneNode()->attachObject(floor);*/

	//this->sceneManager->setShadowFarDistance(1000);
	//this->sceneManager->setShadowTextureSize(512);
	// Create Hydrax object
	/*mHydrax = new Hydrax::Hydrax(this->sceneManager, this->camera, this->window->getViewport(0));

	// Create our projected grid module  
	Hydrax::Module::ProjectedGrid *mModule 
		= new Hydrax::Module::ProjectedGrid(// Hydrax parent pointer
		mHydrax,
		// Noise module
		new Hydrax::Noise::Perlin(),
		// Base plane
		Ogre::Plane(Ogre::Vector3(0,1,0), Ogre::Vector3(0,0,0)),
		// Normal mode
		Hydrax::MaterialManager::NM_VERTEX,
		// Projected grid options
		Hydrax::Module::ProjectedGrid::Options());

	// Set our module
	mHydrax->setModule(static_cast<Hydrax::Module::Module*>(mModule));

	// Load all parameters from config file
	// Remarks: The config file must be in Hydrax resource group.
	// All parameters can be set/updated directly by code(Like previous versions),
	// but due to the high number of customizable parameters, since 0.4 version, Hydrax allows save/load config files.
	bool r = ResourceGroupManager::getSingletonPtr()->resourceExistsInAnyGroup("HydraxDemo.hdx");
	mHydrax->loadCfg("HydraxDemo.hdx");

	// Create water
	mHydrax->create();

	// Hydrax initialization code end -----------------------------------------
	// ------------------------------------------------------------------------

	// Load island
	//mSceneMgr->setWorldGeometry("Island.cfg");

	mHydrax->getMaterialManager()->addDepthTechnique(
		static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName("Island"))
		->createTechnique());*/

	/*Entity *outlineGlowEntity = this->sceneManager->createEntity("outlineGlow", "ogrehead.mesh");
	outlineGlowEntity->setRenderQueueGroup(RENDER_QUEUE_GLOW_OBJECTS);
	this->sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(outlineGlowEntity);

	// outline glow entity actual glow
	Ogre::Entity* actualOutlineGlowEntity = outlineGlowEntity->clone(outlineGlowEntity->getName() + "_glow"); 
	actualOutlineGlowEntity->setRenderQueueGroup(RENDER_QUEUE_OUTLINE_GLOW_GLOWS); 
	actualOutlineGlowEntity->setMaterialName("cg/glow"); 
	Ogre::SceneNode* actualOutlineGlowNode = outlineGlowEntity->getParentSceneNode()->createChildSceneNode("outlineGlowNode"); 
	actualOutlineGlowNode->attachObject(actualOutlineGlowEntity); */

	// normal entity
	/*Entity *normalOgreEntity = this->sceneManager->createEntity("normalOgreEntity", "ogrehead.mesh");
	Ogre::SceneNode* normalOgreNode = this->sceneManager->getRootSceneNode()->createChildSceneNode();
	normalOgreNode->attachObject(normalOgreEntity);
	normalOgreNode->setPosition(80, 0, 0);*/

	/*Entity *fullGlowEntity = this->sceneManager->createEntity("fullGlowEntity", "ogrehead.mesh");
	Ogre::SceneNode* fullGlowNode = this->sceneManager->getRootSceneNode()->createChildSceneNode();
	fullGlowNode->attachObject(fullGlowEntity);
	fullGlowNode->setPosition(-80, 0, 0);

	// full glow alpha glow
	Ogre::Entity* alphaFullGlowEntity = fullGlowEntity->clone(fullGlowEntity->getName() + "_alphaGlow"); 
	alphaFullGlowEntity->setRenderQueueGroup(RENDER_QUEUE_FULL_GLOW_ALPHA_GLOW); 
	alphaFullGlowEntity->setMaterialName("cg/alpha_glow"); 
	Ogre::SceneNode* alphaFullGlowNode = fullGlowEntity->getParentSceneNode()->createChildSceneNode("fullGlowAlphaNode"); 
	alphaFullGlowNode->attachObject(alphaFullGlowEntity); 

	// full glow alpha glow
	Ogre::Entity* glowFullGlowEntity = fullGlowEntity->clone(fullGlowEntity->getName() + "_glow"); 
	glowFullGlowEntity->setRenderQueueGroup(RENDER_QUEUE_FULL_GLOW_GLOW); 
	glowFullGlowEntity->setMaterialName("cg/no_depth_check_glow"); 
	Ogre::SceneNode* glowFullGlowNode = fullGlowEntity->getParentSceneNode()->createChildSceneNode("fullGlowGlowNode"); 
	glowFullGlowNode->attachObject(glowFullGlowEntity); */

}

void GameFramework::_postInitialize()
{
	this->_mulogListener = new MuLogListener();
	this->log->addListener(this->_mulogListener);

	this->_gameGUI = new GameGUI();
	this->_gameClient = new Networking::GameClient();
	this->_factory = new Game::Factory();

	Game::Map* map = new Game::Map(); //one time;
	Game::Map::getSingletonPtr()->Load("LoginScenePlane.scene"/*"Lorencia.scene"*/);

	new Storage();
	Storage::getSingletonPtr()->loadsnoMap();


	/*Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
	// Create an overlay
	Ogre::Overlay* overlay = overlayManager.create( "OverlayName" );
	// Create a panel
	Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", "PanelName" ) );
	panel->setPosition( 0.0, 0.0 );
	panel->setDimensions( 0.3, 0.3 );
	panel->setMaterialName( "BaseWhite" );
	// Add the panel to the overlay
	overlay->add2D( panel );

	// Show the overlay
	overlay->show();*/

	/*
	pass
	{
	scene_blend alpha_blend
	depth_write off

	vertex_program_ref glow_vs_cg
	{
	param_named_auto worldViewProjMatrix worldviewproj_matrix
	param_named size_value float 3.2
	param_named_auto time time_0_x 100
	}

	fragment_program_ref glow_ps_cg 
	{
	param_named alpha_value float 0.99
	param_named_auto time time_0_x 100
	}
	}
	*/
	//m.getTechnique(0)->getPass(0)->

	new GFXManager();
	new BitConverterUtil();
	new Game::GameAttributeUtil();

}

bool GameFramework::keyPressed(const OIS::KeyEvent &arg)
{
	/*if(m_pKeyboard->isKeyDown(OIS::KC_SYSRQ))
	{
		m_pRenderWnd->writeContentsToTimestampedFile("AOF_Screenshot_", ".jpg");
		return true;
	}

	if(m_pKeyboard->isKeyDown(OIS::KC_O))
	{
		if(m_pTrayMgr->isLogoVisible())
		{
			m_pTrayMgr->hideFrameStats();
			m_pTrayMgr->hideLogo();
		}
		else
		{
			m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
			m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
		}
	}*/

	switch(arg.key)
	{
	case OIS::KeyCode::KC_W:
	case OIS::KeyCode::KC_UP:
		this->cameraMan->mGoingForward = true;
		break;

	case OIS::KeyCode::KC_S:
	case OIS::KeyCode::KC_DOWN:
		this->cameraMan->mGoingBack = true;
		break;

	case OIS::KeyCode::KC_A:
	case OIS::KeyCode::KC_LEFT:
		this->cameraMan->mGoingLeft = true;
		break;

	case OIS::KeyCode::KC_D:
	case OIS::KeyCode::KC_RIGHT:
		this->cameraMan->mGoingRight = true;
		break;

	case OIS::KeyCode::KC_E:
	case OIS::KeyCode::KC_PGUP:
		this->cameraMan->mGoingUp = true;
		break;

	case OIS::KeyCode::KC_Q:
	case OIS::KeyCode::KC_PGDOWN:
		this->cameraMan->mGoingDown = true;
		break;

	case OIS::KeyCode::KC_LSHIFT:
	case OIS::KeyCode::KC_RSHIFT:
		this->cameraMan->mFastMove = true;
		break;
	}

	if (arg.key == OIS::KC_R)   // Cycle polygon rendering mode
	{
		Ogre::String newVal;
		Ogre::PolygonMode pm;

		switch (this->camera->getPolygonMode())
		{
		case Ogre::PM_SOLID:
			newVal = "Wireframe";
			pm = Ogre::PM_WIREFRAME;
			break;
		case Ogre::PM_WIREFRAME:
			newVal = "Points";
			pm = Ogre::PM_POINTS;
			break;
		default:
			newVal = "Solid";
			pm = Ogre::PM_SOLID;
		}

		this->camera->setPolygonMode(pm);
	}

	if(arg.key == OIS::KC_F5)      // Refresh all textures
	{
		Ogre::TextureManager::getSingleton().reloadAll();
	}

	if (arg.key == OIS::KC_SYSRQ)
	{
		this->window->writeContentsToTimestampedFile("screenshot", ".jpg");
	}

	if (this->_gameGUI != 0)
		this->_gameGUI->keyPressed(arg);
	
	//MyGUI::KeyCode kk = MyGUI::KeyCode::Enum(arg.key);
	MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::Enum(arg.key), arg.text);
	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameFramework::keyReleased(const OIS::KeyEvent &arg)
{
	switch(arg.key)
	{
	case OIS::KeyCode::KC_W:
	case OIS::KeyCode::KC_UP:
		this->cameraMan->mGoingForward = false;
		break;

	case OIS::KeyCode::KC_S:
	case OIS::KeyCode::KC_DOWN:
		this->cameraMan->mGoingBack = false;
		break;

	case OIS::KeyCode::KC_A:
	case OIS::KeyCode::KC_LEFT:
		this->cameraMan->mGoingLeft = false;
		break;

	case OIS::KeyCode::KC_D:
	case OIS::KeyCode::KC_RIGHT:
		this->cameraMan->mGoingRight = false;
		break;

	case OIS::KeyCode::KC_E:
	case OIS::KeyCode::KC_PGUP:
		this->cameraMan->mGoingUp = false;
		break;

	case OIS::KeyCode::KC_Q:
	case OIS::KeyCode::KC_PGDOWN:
		this->cameraMan->mGoingDown = false;
		break;

	case OIS::KeyCode::KC_LSHIFT:
	case OIS::KeyCode::KC_RSHIFT:
		this->cameraMan->mFastMove = false;
		break;
	}

	if (this->_gameGUI != 0)
		this->_gameGUI->keyReleased(arg);

	MyGUI::InputManager::getInstance().injectKeyRelease(MyGUI::KeyCode::Enum(arg.key));
	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||
static int countersito;

bool GameFramework::mouseMoved(const OIS::MouseEvent &arg)
{
	this->lastMouseX = arg.state.X.abs;
	this->lastMouseY = arg.state.Y.abs;

	POINT p;
	GetCursorPos(&p);
	//LogManager::getSingletonPtr()->logMessage(Ogre::StringConverter::toString(p.x) + "  " + Ogre::StringConverter::toString(p.y));
	
	if (IsMouseOverWindow(this->windowHandle, p.x, p.y, false))
		ShowCursor((false));
	else
		ShowCursor((true));

	this->cameraMan->MouseMovement(arg.state.X.rel, arg.state.Y.rel);

	Game::Map::getSingletonPtr()->mouseMoved(arg);

	MyGUI::InputManager::getInstance().injectMouseMove(arg.state.X.abs, arg.state.Y.abs, arg.state.Z.abs);

	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameFramework::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	this->lastMouseX = arg.state.X.abs;
	this->lastMouseY = arg.state.Y.abs;


	if (id == OIS::MouseButtonID::MB_Left)
		this->isMBLeftPressed = true;

	if (id == OIS::MouseButtonID::MB_Right)
		this->isMBRightPressed = true;

	this->_gameGUI->mousePressed(arg, id);
	Game::Map::getSingletonPtr()->mousePressed(arg, id);

	MyGUI::InputManager::getInstance().injectMousePress(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));


	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameFramework::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	this->lastMouseX = arg.state.X.abs;
	this->lastMouseY = arg.state.Y.abs;
	

	if (id == OIS::MouseButtonID::MB_Left)
		this->isMBLeftPressed = false;

	if (id == OIS::MouseButtonID::MB_Right)
		this->isMBRightPressed = false;

	this->_gameGUI->mouseReleased(arg, id);
	Game::Map::getSingletonPtr()->mouseReleased(arg, id);
	MyGUI::InputManager::getInstance().injectMouseRelease(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
	return true;
}

bool GameFramework::frameStarted(const FrameEvent& evt)
{
	return true;
}

bool GameFramework::frameRenderingQueued(const FrameEvent& evt)
{
	this->pKeyboard->capture();
	this->pMouse->capture();

//	if (this->mHydrax != 0)
//		;//this->mHydrax->update(evt.timeSinceLastFrame);

	if (this->_gameClient != 0)
		this->_gameClient->update(evt.timeSinceLastFrame);

	if (this->_gameGUI != 0)
		this->_gameGUI->update(evt.timeSinceLastFrame);

	if (this->cameraMan != 0)
		this->cameraMan->UpdateCamera(evt.timeSinceLastFrame);

	/*if (this->sn_ogrehead != 0)
	{
		long total_time = this->pTimer->getMilliseconds();
		Vector3 pos = this->sn_ogrehead->getPosition();
		float x = 640*Ogre::Math::Sin(Ogre::Degree(total_time*0.1));
		pos.x = x;
		this->sn_ogrehead->setPosition(pos);
	}*/

	Game::Map::getSingletonPtr()->update(evt.timeSinceLastFrame);

	if (true)
	{
		MyGUI::TextBox* fps_textbox = (MyGUI::TextBox*)MyGUI::Gui::getInstance().findWidgetT("fps_textbox");
		fps_textbox->setCaption("FPS " + StringConverter::toString(this->window->getLastFPS()) + " || " + "Tris " +  StringConverter::toString(this->window->getTriangleCount()));
		//fps_textbox->setCaption("ms CPU " + StringConverter::toString(this->pTimer->getMillisecondsCPU()) + " || " + "Tris " +  StringConverter::toString(this->pTimer->getMilliseconds()));
	}
	//this->pTimer->reset();

	if (GameGlobals::FPS_LIMITER)
	{
		if (this->mFPSLimiterTimer->getMilliseconds() < GameGlobals::FPS_LIMIT)
		{
			unsigned long to_sleep_ms = GameGlobals::FPS_LIMIT - this->mFPSLimiterTimer->getMilliseconds();
			Sleep(to_sleep_ms);
		}
		this->mFPSLimiterTimer->reset();
	}

	return true;
}
bool GameFramework::frameEnded(const FrameEvent& evt)
{
	return true;
}


GameGUI* GameFramework::getGameGUI()
{
	return this->_gameGUI;
}

Networking::GameClient* GameFramework::getGameClient()
{
	return this->_gameClient;
}

Game::Factory* GameFramework::getFactory()
{
	return this->_factory;
}

///////////////////////////////////////////////////////////////////
///
/// Checks if the mouse cursor is over the window.
///
/// @param hWnd        [IN] window handle
/// @param mx            [IN] x mouse coordinate
/// @param my            [IN] y mouse coordinate
/// @param inClientSpace [IN] indicates if we check coordinate in 
///                                        client or screen space.
///
/// @return true if the point is over the window area.
///
bool IsMouseOverWindow(HWND hWnd, const int mx, const int my,
	const bool inClientSpace /*= false */)
{
	RECT windowRect;

	// Get the window in screen space
	::GetWindowRect( hWnd, &windowRect );

	if ( inClientSpace )
	{
		POINT offset;
		offset.x = offset.y = 0;
		ClientToScreen( hWnd, &offset );

		// Offset the window to client space
		windowRect.left -= offset.x;
		windowRect.top -= offset.y;
		// NOTE: left and top should now be 0, 0
		windowRect.right -= offset.x;
		windowRect.bottom -= offset.y;
	}

	// Test if mouse over window
	POINT cursorPos = { mx, my };
	return PtInRect( &windowRect, cursorPos );
}
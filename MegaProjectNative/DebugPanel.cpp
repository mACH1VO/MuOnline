#include "stdafx.h"
#include "DebugPanel.h"

#include "GameFramework.h"
#include "GameClient.h"
#include "GameGUI.h"
#include "GameSetupMessage.h"
#include "NewPlayerMessage.h"
#include "CameraMan.h"
#include "GameMessage.h"
#include "DotSceneLoader.h"
#include "Player.h"

#include "EffectFactory.h"

#include "GameMessage.h"
#include "ACDClientTranslateMessage.h"

#include "PathFindingSystem/OgreRecast.h"
#include "PathFindingSystem/RecastInputGeom.h"
#include "PathFindingSystem/ConvexShapeObstacle.h"
#include "PathFindingSystem/CylinderObstacle.h"
#include "PathFindingSystem/CrowdManager.h"

//#include "ParticleUniverse/ParticleUniverseSystemManager.h"

//#include "Ogre.h"

bool initialized;
bool auto_Track_player;
	DebugPanel::DebugPanel(MyGUI::Widget* _parent)
	{
		initialiseByAttributes(this, _parent);

		//this->mconnect_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &DebugPanel::mconnect_Button_click);
		this->mgenerateNavMesh_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &DebugPanel::mgenerateNavMesh_Button_click);
		//this->mcameramode_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &DebugPanel::mcameramode_Button_click);
		//this->mauto_track_playerButton->eventMouseButtonClick += MyGUI::newDelegate(this, &DebugPanel::mauto_track_playerButton_click);
		this->mshow_bb_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &DebugPanel::mshow_bb_Button_click);
		this->mMainWidget->setVisible(false);
		auto_Track_player = false;
		initialized = false;
	}

	DebugPanel::~DebugPanel()
	{
	}

	void DebugPanel::mconnect_Button_click(MyGUI::WidgetPtr _sender)
	{
		
	}

	void DebugPanel::mauto_track_playerButton_click(MyGUI::WidgetPtr _sender)
	{
		//auto_Track_player = !auto_Track_player;
		//GameFramework::getSingletonPtr()->cameraMan->AutoTrackMainPlayer = auto_Track_player;
		//MyGUI::ButtonPtr check
		//box = _sender->castType<MyGUI::Button>();
		//checkbox->setStateCheck(/*!checkbox->getStateCheck()*/true);

		//GameFramework::getSingletonPtr()->cameraMan->AutoTrackMainPlayer = checkbox->getStateCheck();
	}

	int ef_num;
	void DebugPanel::mgenerateNavMesh_Button_click(MyGUI::WidgetPtr _sender)
	{

		int num = GameFramework::getSingleton().window->getNumViewports();

		if (GameFramework::getSingleton().mainPlayer != 0)
			GameFramework::getSingletonPtr()->mainPlayer->say(StringConverter::toString(num), 1000);

		if (!initialized)
		{
			/*ParticleUniverse::ParticleSystemManager* pManager =
				ParticleUniverse::ParticleSystemManager::getSingletonPtr();

			ParticleUniverse::ParticleSystem* pSys = pManager->createParticleSystem("rainSystem_1" + Ogre::StringConverter::toString(GameFramework::getSingletonPtr()->pTimer->getMicrosecondsCPU()),
				"rainSystem_1", GameFramework::getSingletonPtr()->sceneManager);

			SceneNode* mNode = GameFramework::getSingletonPtr()->sceneManager->getRootSceneNode()->createChildSceneNode();
			mNode->attachObject(pSys);
			pSys->setScale(Vector3::UNIT_SCALE * 5);
			//mNode->setScale(10, 10, 10);

			pSys->prepare();
			pSys->start(9999999);

			initialized = true;*/
		}

		SceneNode* sn = GameFramework::getSingletonPtr()->sceneManager->getRootSceneNode()->createChildSceneNode();
		sn->setPosition(Vector3(Ogre::Math::RangeRandom(-50,50), 0, Ogre::Math::RangeRandom(-50,50)));
		EffectFactory::getSingletonPtr()->playRandomEffect(sn);

		/*Messages::ACDClientTranslateMessage* msg = new Messages::ACDClientTranslateMessage();
		msg->Position = Vector3(0.33510, 0.11, 3.5110);
		Networking::GameClient* gc = GameFramework::getSingletonPtr()->getGameClient();
		gc->sendMessage(msg);*/
	}

	void DebugPanel::mcameramode_Button_click(MyGUI::WidgetPtr _sender)
	{
		if (GameFramework::getSingletonPtr()->camera->getProjectionType() == Ogre::ProjectionType::PT_PERSPECTIVE)
			GameFramework::getSingletonPtr()->camera->setProjectionType(Ogre::ProjectionType::PT_ORTHOGRAPHIC);
		else
			GameFramework::getSingletonPtr()->camera->setProjectionType(Ogre::ProjectionType::PT_PERSPECTIVE);
	}

	void DebugPanel::mshow_bb_Button_click(MyGUI::WidgetPtr _sender)
	{
		//GameFramework::getSingletonPtr()->Viewport->setMaterialScheme("testScheme");

		this->mshow_bb_Button->setStateSelected(!this->mshow_bb_Button->getStateSelected());
		Ogre::SceneManager::MovableObjectIterator mo_iterator = GameFramework::getSingletonPtr()->sceneManager->getMovableObjectIterator("Entity");
		
		while (mo_iterator.hasMoreElements())
		{
			Ogre::Entity *ent = static_cast<Ogre::Entity*>(mo_iterator.getNext());
			ent->getParentSceneNode()->showBoundingBox(!this->mshow_bb_Button->getStateSelected());
		}

		bool status = this->mshow_bb_Button->getStateSelected();

		/*Ogre::CompositorManager::getSingleton().setCompositorEnabled(GameFramework::getSingletonPtr()->Viewport, "Test", status);
		Ogre::CompositorManager::getSingleton().setCompositorEnabled(GameFramework::getSingletonPtr()->Viewport, "Grayscale", status);*/

		//Ogre::CompositorManager::getSingleton().setCompositorEnabled(GameFramework::getSingletonPtr()->Viewport, "Test", status);
		//Ogre::CompositorManager::getSingleton().setCompositorEnabled(GameFramework::getSingletonPtr()->Viewport, "Grayscale", status);
		//Ogre::CompositorManager::getSingleton().setCompositorEnabled(GameFramework::getSingletonPtr()->Viewport, "Vignetting", status);
		//Ogre::CompositorManager::getSingleton().setCompositorEnabled(GameFramework::getSingletonPtr()->Viewport, "ColorCorrection", status);
		
	}
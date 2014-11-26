#include "stdafx.h"
#include "ProfilingPanel.h"
#include "GameFramework.h"
#include "GFXManager.h"

#include "VignettingListener.h"
#include "ColorCorrectionListener.h"
#include "GloomListener.h"
#include "PoissonBlurListener.h"
	ProfilingPanel::ProfilingPanel(MyGUI::Widget* _parent)
	{
		initialiseByAttributes(this, _parent);

		MyGUI::Window* window = mMainWidget->castType<MyGUI::Window>(false);
		if (window != nullptr)
			window->eventWindowButtonPressed += MyGUI::newDelegate(this, &ProfilingPanel::notifyWindowButtonPressed);

		/*this->mBaseIntensity_barScrollBar->eventScrollChangePosition += MyGUI::newDelegate(this, &ProfilingPanel::bar_change_value);
		this->mBaseSaturation_barScrollBar->eventScrollChangePosition += MyGUI::newDelegate(this, &ProfilingPanel::bar_change_value);
		this->mGloomIntensity_barScrollBar->eventScrollChangePosition += MyGUI::newDelegate(this, &ProfilingPanel::bar_change_value);
		this->mGloomSaturation_barScrollBar->eventScrollChangePosition += MyGUI::newDelegate(this, &ProfilingPanel::bar_change_value);

		this->mbloom_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &ProfilingPanel::mbloom_Button_click);
		this->mcolor_correction_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &ProfilingPanel::mcolor_correction_Button_click);
		this->mvignetting_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &ProfilingPanel::mvignetting_Button_click);
		this->mglow_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &ProfilingPanel::mglow_Button_click);

		this->msoftshadows_enable_checkboxButton->eventMouseButtonClick += MyGUI::newDelegate(this, &ProfilingPanel::msoftshadows_enable_checkboxButton_click);
		this->mshadow_slider_DiskRadius_ScrollBar->eventScrollChangePosition += MyGUI::newDelegate(this, &ProfilingPanel::bar_change_value);
		this->mshadow_texture_size_apply_Button->eventMouseButtonClick += MyGUI::newDelegate(this, &ProfilingPanel::mshadow_texture_size_apply_Button_click);*/
	}

	ProfilingPanel::~ProfilingPanel()
	{
	}

	void ProfilingPanel::mshadow_texture_size_apply_Button_click(MyGUI::WidgetPtr _sender)
	{
		int resolution = Ogre::StringConverter::parseInt(this->mshadow_texture_size_ComboBox->getCaption());
		GameFramework::getSingletonPtr()->sceneManager->setShadowTextureSize(resolution);

		GFXManager::getSingletonPtr()->poissonBlurListener->InputSize = Vector2(resolution, resolution);
	}
		
	void ProfilingPanel::msoftshadows_enable_checkboxButton_click(MyGUI::WidgetPtr _sender)
	{
		this->msoftshadows_enable_checkboxButton->setStateSelected(!this->msoftshadows_enable_checkboxButton->getStateSelected());
		bool status = this->msoftshadows_enable_checkboxButton->getStateSelected();
		Ogre::TexturePtr texture = GameFramework::getSingleton().sceneManager->getShadowTexture(0);
		Ogre::Viewport* l_ShadowMapViewport = texture->getBuffer()->getRenderTarget()->getViewport(0);
		Ogre::CompositorManager::getSingleton().setCompositorEnabled(l_ShadowMapViewport, "PoissonBlur", status);
	}

	void ProfilingPanel::mcolor_correction_Button_click(MyGUI::WidgetPtr _sender)
	{
		this->mcolor_correction_Button->setStateSelected(!this->mcolor_correction_Button->getStateSelected());
		bool status = this->mcolor_correction_Button->getStateSelected();
		Ogre::CompositorManager::getSingleton().setCompositorEnabled(GameFramework::getSingletonPtr()->Viewport, "ColorCorrection", status);

		//Ogre::CompositorManager::getSingletonPtr()->i;
	}
	void ProfilingPanel::mbloom_Button_click(MyGUI::WidgetPtr _sender)
	{
		this->mbloom_Button->setStateSelected(!this->mbloom_Button->getStateSelected());
		bool status = this->mbloom_Button->getStateSelected();
		Ogre::CompositorManager::getSingleton().setCompositorEnabled(GameFramework::getSingletonPtr()->Viewport, "Gloom", status);
	}
	void ProfilingPanel::mvignetting_Button_click(MyGUI::WidgetPtr _sender)
	{
		this->mvignetting_Button->setStateSelected(!this->mvignetting_Button->getStateSelected());
		bool status = this->mvignetting_Button->getStateSelected();
		Ogre::CompositorManager::getSingleton().setCompositorEnabled(GameFramework::getSingletonPtr()->Viewport, "Vignetting", status);
	}
	void ProfilingPanel::mglow_Button_click(MyGUI::WidgetPtr _sender)
	{
		this->mglow_Button->setStateSelected(!this->mglow_Button->getStateSelected());
		bool status = this->mglow_Button->getStateSelected();
		Ogre::CompositorManager::getSingleton().setCompositorEnabled(GameFramework::getSingletonPtr()->Viewport, "Glow", status);
	}

	void ProfilingPanel::bar_change_value(MyGUI::ScrollBar* _sender, size_t _position)
	{
		string name = _sender->getName();

		if (name.find("BaseIntensity") != string::npos)
		{
			float value = _position / 50.0;
			this->mBaseIntensityTextBox->setCaption("BaseInt " + Ogre::StringConverter::toString(value));
			GFXManager::getSingletonPtr()->gloomListener->BaseIntensity = value;
		}

		if (name.find("BaseSaturation") != string::npos)
		{
			float value = _position / 50.0;
			this->mBaseSaturationTextBox->setCaption("BaseSat " + Ogre::StringConverter::toString(value));
			GFXManager::getSingletonPtr()->gloomListener->BaseSaturation = value;
		}

		if (name.find("GloomIntensity") != string::npos)
		{
			float value = _position / 50.0;
			this->mGloomIntensityTextBox->setCaption("GloomInt " + Ogre::StringConverter::toString(value));
			GFXManager::getSingletonPtr()->gloomListener->GloomIntensity = value;
		}

		if (name.find("GloomSaturation") != string::npos)
		{
			float value = _position / 50.0;
			this->mGloomSaturationTextBox->setCaption("GloomSat " + Ogre::StringConverter::toString(value));
			GFXManager::getSingletonPtr()->gloomListener->GloomSaturation = value;
		}

		if (name.find("DiskRadius") != string::npos)
		{
			float value = _position / 20.0; // de 1 a 5
			this->mshadow_diskradius_TextBox->setCaption("DiskRadius " + Ogre::StringConverter::toString(value));
			GFXManager::getSingletonPtr()->poissonBlurListener->DiskRadius = value;

			/*GameFramework::getSingleton().sceneManager->setShadowFarDistance(_position * 5);
			this->mshadow_diskradius_TextBox->setCaption(Ogre::StringConverter::toString(_position * 5));*/
		}
	}

	void ProfilingPanel::update(float timeSinceLastFrame)
	{
		Ogre::RenderWindow::FrameStats stats = GameFramework::getSingletonPtr()->window->getStatistics();

		this->mprof_fpsTextBox->setCaption("FPS " + Ogre::StringConverter::toString(stats.lastFPS));
		this->mprof_trianglecountTextBox->setCaption("Triangle count " + Ogre::StringConverter::toString(stats.triangleCount));
		this->mprof_batchcountTextBox->setCaption("Batch count " + Ogre::StringConverter::toString(stats.batchCount));
	}

	//(MyGUI::Window* _sender, const std::string& _name)
	void ProfilingPanel::notifyWindowButtonPressed(MyGUI::Window* _sender, const std::string& _name)
	{
		if (_name == "close")
			_sender->setVisible(false);

		//GameFramework::getSingletonPtr()->getGameGUI()->getProfilingPanel()->getMainWidget()->setVisible(/*!isVisible*/true);
	}
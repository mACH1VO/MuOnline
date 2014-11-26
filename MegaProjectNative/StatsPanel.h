#ifndef _STATS_PANEL_H_
#define _STATS_PANEL_H_

#include "stdafx.h"
#include "BaseLayout/BaseLayout.h"

#include "GameFramework.h"

#include "RenderBox.h"
#include "RenderBoxScene.h"

	static wraps::RenderBox gRenderBox;
	static wraps::RenderBoxScene gRenderBoxScene;


	ATTRIBUTE_CLASS_LAYOUT(StatsPanel, "Stats.layout");
	class StatsPanel : public wraps::BaseLayout
	{
	public:
		StatsPanel(MyGUI::Widget* _parent = nullptr);
		virtual ~StatsPanel();

		MyGUI::Widget* getMainWidget()
		{
			return this->mMainWidget;
		}

		void inline setEnableAllButtons(bool _enabled)
		{
			this->mstrength_button_Button->setEnabled(_enabled);
			this->magility_button_Button->setEnabled(_enabled);
			this->mstamina_button_Button->setEnabled(_enabled);
			this->menergy_button_Button->setEnabled(_enabled);
		}

		void eventMouseButtonClick_statButton(MyGUI::WidgetPtr _sender);

		void inline initialize()
		{
			/*gRenderBox.setCanvas(this->mcharacter_canvas_Canvas);
			gRenderBox.setViewport(GameFramework::getSingletonPtr()->camera);
			gRenderBox.setBackgroundColour(MyGUI::Colour::Black);*/

			gRenderBoxScene.setCanvas(this->mcharacter_canvas_Canvas);
			gRenderBoxScene.injectObject("NewFace02.mesh");
			gRenderBoxScene.mNode->setScale(Vector3::UNIT_SCALE * 2);
			gRenderBoxScene.mNode->setPosition(Vector3(0,-9,0));
			//gRenderBoxScene.setAutoRotation(true);
			gRenderBoxScene.setMouseRotation(true);
			gRenderBoxScene.setAnimation("Emotion");

			MyGUI::Gui::getInstance().eventFrameStart += MyGUI::newDelegate(this, &StatsPanel::notifyFrameStart);
		}
		void inline StatsPanel::notifyFrameStart(float _time)
		{
			/*if (mNode)
				mNode->yaw(Ogre::Radian(Ogre::Degree(_time * 10)));*/
		}

		//%LE Widget_Declaration list start
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mRootWidget, "Root");
		MyGUI::Widget* mRootWidget;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mdefense_shield_EditBox, "defense_shield_");
		MyGUI::EditBox* mdefense_shield_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mdps_EditBox, "dps_");
		MyGUI::EditBox* mdps_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mstrengh_EditBox, "strengh_");
		MyGUI::EditBox* mstrengh_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, magility_EditBox, "agility_");
		MyGUI::EditBox* magility_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mstamina_EditBox, "stamina_");
		MyGUI::EditBox* mstamina_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, menergy_EditBox, "energy_");
		MyGUI::EditBox* menergy_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mstrength_button_Button, "strength_button_");
		MyGUI::Button* mstrength_button_Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, magility_button_Button, "agility_button_");
		MyGUI::Button* magility_button_Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mstamina_button_Button, "stamina_button_");
		MyGUI::Button* mstamina_button_Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, menergy_button_Button, "energy_button_");
		MyGUI::Button* menergy_button_Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mlevel_EditBox, "level_");
		MyGUI::EditBox* mlevel_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mcharacter_canvas_Canvas, "character_canvas_");
		MyGUI::Canvas* mcharacter_canvas_Canvas;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mavailable_point_text_EditBox, "available_point_text_");
		MyGUI::EditBox* mavailable_point_text_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mavailable_points_number_EditBox, "available_points_number_");
		MyGUI::EditBox* mavailable_points_number_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mclass_name_EditBox, "class_name_");
		MyGUI::EditBox* mclass_name_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mnick_EditBox, "nick_");
		MyGUI::EditBox* mnick_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mexperience_EditBox, "experience_");
		MyGUI::EditBox* mexperience_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mdmg_EditBox, "dmg_");
		MyGUI::EditBox* mdmg_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mattack_rate_EditBox, "attack_rate_");
		MyGUI::EditBox* mattack_rate_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mcritical_EditBox, "critical_");
		MyGUI::EditBox* mcritical_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mdefense_EditBox, "defense_");
		MyGUI::EditBox* mdefense_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mrate_EditBox, "rate_");
		MyGUI::EditBox* mrate_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mspeed_EditBox, "speed_");
		MyGUI::EditBox* mspeed_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mhp_EditBox, "hp_");
		MyGUI::EditBox* mhp_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mlife_rec_EditBox, "life_rec_");
		MyGUI::EditBox* mlife_rec_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mmana_EditBox, "mana_");
		MyGUI::EditBox* mmana_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mmana_rec_EditBox, "mana_rec_");
		MyGUI::EditBox* mmana_rec_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(StatsPanel, mskill_dmg_EditBox, "skill_dmg_");
		MyGUI::EditBox* mskill_dmg_EditBox;
		//%LE Widget_Declaration list end
	};


#endif // _STATS_PANEL_H_

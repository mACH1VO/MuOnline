#ifndef _BUTTOM_BAR_H_
#define _BUTTOM_BAR_H_
#include "stdafx.h"
#include "BaseLayout/BaseLayout.h"

class TickTimer;
enum SkillOpcode;
enum SkillSlot;

ATTRIBUTE_CLASS_LAYOUT(ButtomBar, "ButtomBar.layout");

class ButtomBar :
	public wraps::BaseLayout
{
public:
	ButtomBar(MyGUI::Widget* _parent = nullptr);
	virtual ~ButtomBar();

	MyGUI::Widget* getMainWidget()
	{
		return this->mMainWidget;
	}
	string ButtomBar::skill_opcode_to_string(SkillOpcode opcode);
	void eventMouseButtonClick_skillButton(MyGUI::WidgetPtr _sender);
	void eventMouseButtonClick_availableSkillButton(MyGUI::WidgetPtr _sender);

	void ButtomBar::setVisualSkillIcon(SkillSlot skillSlot, SkillOpcode skillOpcode);
	void ButtomBar::setVisualAvailableSkillIcon(int position, SkillOpcode skillOpcode);

	void ButtomBar::setNumberToAvailableSkillButton(int number, SkillOpcode skillOpcode);

	TickTimer* ttupdateGlobe;
	int currentHPGlobeFrame;
	void update(float timeSinceLastFrame);
	MyGUI::Widget* _lastButtonSkillClicked;

	//%LE Widget_Declaration list start
	ATTRIBUTE_FIELD_WIDGET_NAME(ButtomBar, mskill_slot_primaryButton, "skill_slot_primary");
	MyGUI::Button* mskill_slot_primaryButton;
	ATTRIBUTE_FIELD_WIDGET_NAME(ButtomBar, mskill_slot_secondaryButton, "skill_slot_secondary");
	MyGUI::Button* mskill_slot_secondaryButton;
	ATTRIBUTE_FIELD_WIDGET_NAME(ButtomBar, mskill_number_secondary_EditBox, "skill_number_secondary_");
	MyGUI::EditBox* mskill_number_secondary_EditBox;
	ATTRIBUTE_FIELD_WIDGET_NAME(ButtomBar, mQ_slot_Widget, "Q_slot_");
	MyGUI::Widget* mQ_slot_Widget;
	ATTRIBUTE_FIELD_WIDGET_NAME(ButtomBar, mW_slot_Widget, "W_slot_");
	MyGUI::Widget* mW_slot_Widget;
	ATTRIBUTE_FIELD_WIDGET_NAME(ButtomBar, mE_slot_Widget, "E_slot_");
	MyGUI::Widget* mE_slot_Widget;
	ATTRIBUTE_FIELD_WIDGET_NAME(ButtomBar, mR_slot_Widget, "R_slot_");
	MyGUI::Widget* mR_slot_Widget;
	ATTRIBUTE_FIELD_WIDGET_NAME(ButtomBar, mHPResourceGlobeWidget, "HPResourceGlobe");
	MyGUI::Widget* mHPResourceGlobeWidget;
	ATTRIBUTE_FIELD_WIDGET_NAME(ButtomBar, mpanel_select_skill_Widget, "panel_select_skill_");
	MyGUI::Widget* mpanel_select_skill_Widget;
	ATTRIBUTE_FIELD_WIDGET_NAME(ButtomBar, mManaResourceGlobeWidget, "ManaResourceGlobe");
	MyGUI::Widget* mManaResourceGlobeWidget;
	ATTRIBUTE_FIELD_WIDGET_NAME(ButtomBar, mexperience_bar_ProgressBar, "experience_bar_");
	MyGUI::ProgressBar* mexperience_bar_ProgressBar;
	/*ATTRIBUTE_FIELD_WIDGET_NAME(ButtomBar, mavailable_1_Button, "available_1_");
	MyGUI::Button* mavailable_1_Button;
	ATTRIBUTE_FIELD_WIDGET_NAME(ButtomBar, mavailable_2_Button, "available_2_");
	MyGUI::Button* mavailable_2_Button;
	ATTRIBUTE_FIELD_WIDGET_NAME(ButtomBar, mavailable_3_Button, "available_3_");
	MyGUI::Button* mavailable_3_Button;
	ATTRIBUTE_FIELD_WIDGET_NAME(ButtomBar, mavailable_4_Button, "available_4_");
	MyGUI::Button* mavailable_4_Button;
	ATTRIBUTE_FIELD_WIDGET_NAME(ButtomBar, mavailable_5_Button, "available_5_");
	MyGUI::Button* mavailable_5_Button;
	ATTRIBUTE_FIELD_WIDGET_NAME(ButtomBar, mavailable_6_Button, "available_6_");
	MyGUI::Button* mavailable_6_Button;
	ATTRIBUTE_FIELD_WIDGET_NAME(ButtomBar, mavailable_7_Button, "available_7_");
	MyGUI::Button* mavailable_7_Button;*/
	//%LE Widget_Declaration list end
};


#endif // _BUTTOM_BAR_H_

#ifndef _INVENTORY_PANEL_H_
#define _INVENTORY_PANEL_H_

#include "stdafx.h"
#include "BaseLayout/BaseLayout.h"

enum EquipmentSlotId;

namespace Game
{
	class InventorySlot;
	class InventorySize;
}

	ATTRIBUTE_CLASS_LAYOUT(InventoryPanel, "Inventory.layout");
	class InventoryPanel :
		public wraps::BaseLayout
	{
	public:
		InventoryPanel(MyGUI::Widget* _parent = nullptr);
		virtual ~InventoryPanel();

		MyGUI::Widget* getMainWidget()
		{
			return this->mMainWidget;
		}

		void InventoryPanel::mclose_eventMouseButtonClick(MyGUI::WidgetPtr _sender);
		//Slot related functions
		bool hitTestSlots(const MyGUI::types::TRect<int>&  _value);
		MyGUI::Widget* InventoryPanel::getWidgetSlotByScreenPosition(const MyGUI::types::TPoint<int>&  _value);
		MyGUI::Widget* InventoryPanel::getWidgetSlotByScreenPosition_modified(const MyGUI::types::TPoint<int>&  _value);
		MyGUI::Widget* InventoryPanel::getWidgetSlotByRC(int r, int c);
		Game::InventorySlot InventoryPanel::getSlotByWidgetName(std::string name);

		//Equipment
		MyGUI::Widget* InventoryPanel::getEquipmentWidgetByScreenPosition(const MyGUI::types::TPoint<int>&  _value);
		MyGUI::Widget* InventoryPanel::getWidgetByEquipmentId(EquipmentSlotId _equipmentSlot);
		EquipmentSlotId InventoryPanel::getEquipmentIdByWidgetName(std::string name);

		//Colours!
		void InventoryPanel::setAllEquipmentColour(MyGUI::Colour color);
		void InventoryPanel::setAllSlotsColor(MyGUI::Colour color);
		void InventoryPanel::setHoverSlotsColor(Game::InventorySlot* _slot, Game::InventorySize* _size , MyGUI::Colour color);
		void InventoryPanel::setHoverSlotsColor(const MyGUI::types::TRect<int>&  _value , MyGUI::Colour color);

		std::vector<MyGUI::Widget*>* slot_list;

		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, mRootWidget, "Root");
		MyGUI::Widget* mRootWidget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, mitem_cap_Widget, "item_cap_");
		MyGUI::Widget* mitem_cap_Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, mitem_boots_Widget, "item_boots_");
		MyGUI::Widget* mitem_boots_Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, mitem_fairy_Widget, "item_fairy_");
		MyGUI::Widget* mitem_fairy_Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, mitem_gloves_Widget, "item_gloves_");
		MyGUI::Widget* mitem_gloves_Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, mitem_lower_Widget, "item_lower_");
		MyGUI::Widget* mitem_lower_Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, mitem_necklace_Widget, "item_necklace_");
		MyGUI::Widget* mitem_necklace_Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, mitem_ring_l_Widget, "item_ring_l_");
		MyGUI::Widget* mitem_ring_l_Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, mitem_ring_r_Widget, "item_ring_r_");
		MyGUI::Widget* mitem_ring_r_Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, mitem_upper_Widget, "item_upper_");
		MyGUI::Widget* mitem_upper_Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, mitem_weapon_l_Widget, "item_weapon_l_");
		MyGUI::Widget* mitem_weapon_l_Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, mitem_weapon_r_Widget, "item_weapon_r_");
		MyGUI::Widget* mitem_weapon_r_Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, mitem_wing_Widget, "item_wing_");
		MyGUI::Widget* mitem_wing_Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, mslot_container_panel_1_Widget, "slot_container_panel_1_");
		MyGUI::Widget* mslot_container_panel_1_Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, mslot_container_panel_2_Widget, "slot_container_panel_2_");
		MyGUI::Widget* mslot_container_panel_2_Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_0x0Widget, "inventory_slot_0x0");
		MyGUI::Widget* minventory_slot_0x0Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_0x1Widget, "inventory_slot_0x1");
		MyGUI::Widget* minventory_slot_0x1Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_0x2Widget, "inventory_slot_0x2");
		MyGUI::Widget* minventory_slot_0x2Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_0x3Widget, "inventory_slot_0x3");
		MyGUI::Widget* minventory_slot_0x3Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_0x4Widget, "inventory_slot_0x4");
		MyGUI::Widget* minventory_slot_0x4Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_0x5Widget, "inventory_slot_0x5");
		MyGUI::Widget* minventory_slot_0x5Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_0x6Widget, "inventory_slot_0x6");
		MyGUI::Widget* minventory_slot_0x6Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_0x7Widget, "inventory_slot_0x7");
		MyGUI::Widget* minventory_slot_0x7Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_0x8Widget, "inventory_slot_0x8");
		MyGUI::Widget* minventory_slot_0x8Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_0x9Widget, "inventory_slot_0x9");
		MyGUI::Widget* minventory_slot_0x9Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_0x10Widget, "inventory_slot_0x10");
		MyGUI::Widget* minventory_slot_0x10Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_0x11Widget, "inventory_slot_0x11");
		MyGUI::Widget* minventory_slot_0x11Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_1x0Widget, "inventory_slot_1x0");
		MyGUI::Widget* minventory_slot_1x0Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_1x1Widget, "inventory_slot_1x1");
		MyGUI::Widget* minventory_slot_1x1Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_1x2Widget, "inventory_slot_1x2");
		MyGUI::Widget* minventory_slot_1x2Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_1x3Widget, "inventory_slot_1x3");
		MyGUI::Widget* minventory_slot_1x3Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_1x4Widget, "inventory_slot_1x4");
		MyGUI::Widget* minventory_slot_1x4Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_1x5Widget, "inventory_slot_1x5");
		MyGUI::Widget* minventory_slot_1x5Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_1x6Widget, "inventory_slot_1x6");
		MyGUI::Widget* minventory_slot_1x6Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_1x7Widget, "inventory_slot_1x7");
		MyGUI::Widget* minventory_slot_1x7Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_1x8Widget, "inventory_slot_1x8");
		MyGUI::Widget* minventory_slot_1x8Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_1x9Widget, "inventory_slot_1x9");
		MyGUI::Widget* minventory_slot_1x9Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_1x10Widget, "inventory_slot_1x10");
		MyGUI::Widget* minventory_slot_1x10Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_1x11Widget, "inventory_slot_1x11");
		MyGUI::Widget* minventory_slot_1x11Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_2x0Widget, "inventory_slot_2x0");
		MyGUI::Widget* minventory_slot_2x0Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_2x1Widget, "inventory_slot_2x1");
		MyGUI::Widget* minventory_slot_2x1Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_2x2Widget, "inventory_slot_2x2");
		MyGUI::Widget* minventory_slot_2x2Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_2x3Widget, "inventory_slot_2x3");
		MyGUI::Widget* minventory_slot_2x3Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_2x4Widget, "inventory_slot_2x4");
		MyGUI::Widget* minventory_slot_2x4Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_2x5Widget, "inventory_slot_2x5");
		MyGUI::Widget* minventory_slot_2x5Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_2x6Widget, "inventory_slot_2x6");
		MyGUI::Widget* minventory_slot_2x6Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_2x7Widget, "inventory_slot_2x7");
		MyGUI::Widget* minventory_slot_2x7Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_2x8Widget, "inventory_slot_2x8");
		MyGUI::Widget* minventory_slot_2x8Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_2x9Widget, "inventory_slot_2x9");
		MyGUI::Widget* minventory_slot_2x9Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_2x10Widget, "inventory_slot_2x10");
		MyGUI::Widget* minventory_slot_2x10Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_2x11Widget, "inventory_slot_2x11");
		MyGUI::Widget* minventory_slot_2x11Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_3x0Widget, "inventory_slot_3x0");
		MyGUI::Widget* minventory_slot_3x0Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_3x1Widget, "inventory_slot_3x1");
		MyGUI::Widget* minventory_slot_3x1Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_3x2Widget, "inventory_slot_3x2");
		MyGUI::Widget* minventory_slot_3x2Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_3x3Widget, "inventory_slot_3x3");
		MyGUI::Widget* minventory_slot_3x3Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_3x4Widget, "inventory_slot_3x4");
		MyGUI::Widget* minventory_slot_3x4Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_3x5Widget, "inventory_slot_3x5");
		MyGUI::Widget* minventory_slot_3x5Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_3x6Widget, "inventory_slot_3x6");
		MyGUI::Widget* minventory_slot_3x6Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_3x7Widget, "inventory_slot_3x7");
		MyGUI::Widget* minventory_slot_3x7Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_3x8Widget, "inventory_slot_3x8");
		MyGUI::Widget* minventory_slot_3x8Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_3x9Widget, "inventory_slot_3x9");
		MyGUI::Widget* minventory_slot_3x9Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_3x10Widget, "inventory_slot_3x10");
		MyGUI::Widget* minventory_slot_3x10Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_3x11Widget, "inventory_slot_3x11");
		MyGUI::Widget* minventory_slot_3x11Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_4x0Widget, "inventory_slot_4x0");
		MyGUI::Widget* minventory_slot_4x0Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_4x1Widget, "inventory_slot_4x1");
		MyGUI::Widget* minventory_slot_4x1Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_4x2Widget, "inventory_slot_4x2");
		MyGUI::Widget* minventory_slot_4x2Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_4x3Widget, "inventory_slot_4x3");
		MyGUI::Widget* minventory_slot_4x3Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_4x4Widget, "inventory_slot_4x4");
		MyGUI::Widget* minventory_slot_4x4Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_4x5Widget, "inventory_slot_4x5");
		MyGUI::Widget* minventory_slot_4x5Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_4x6Widget, "inventory_slot_4x6");
		MyGUI::Widget* minventory_slot_4x6Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_4x7Widget, "inventory_slot_4x7");
		MyGUI::Widget* minventory_slot_4x7Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_4x8Widget, "inventory_slot_4x8");
		MyGUI::Widget* minventory_slot_4x8Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_4x9Widget, "inventory_slot_4x9");
		MyGUI::Widget* minventory_slot_4x9Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_4x10Widget, "inventory_slot_4x10");
		MyGUI::Widget* minventory_slot_4x10Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_4x11Widget, "inventory_slot_4x11");
		MyGUI::Widget* minventory_slot_4x11Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_5x0Widget, "inventory_slot_5x0");
		MyGUI::Widget* minventory_slot_5x0Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_5x1Widget, "inventory_slot_5x1");
		MyGUI::Widget* minventory_slot_5x1Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_5x2Widget, "inventory_slot_5x2");
		MyGUI::Widget* minventory_slot_5x2Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_5x3Widget, "inventory_slot_5x3");
		MyGUI::Widget* minventory_slot_5x3Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_5x4Widget, "inventory_slot_5x4");
		MyGUI::Widget* minventory_slot_5x4Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_5x5Widget, "inventory_slot_5x5");
		MyGUI::Widget* minventory_slot_5x5Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_5x6Widget, "inventory_slot_5x6");
		MyGUI::Widget* minventory_slot_5x6Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_5x7Widget, "inventory_slot_5x7");
		MyGUI::Widget* minventory_slot_5x7Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_5x8Widget, "inventory_slot_5x8");
		MyGUI::Widget* minventory_slot_5x8Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_5x9Widget, "inventory_slot_5x9");
		MyGUI::Widget* minventory_slot_5x9Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_5x10Widget, "inventory_slot_5x10");
		MyGUI::Widget* minventory_slot_5x10Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_5x11Widget, "inventory_slot_5x11");
		MyGUI::Widget* minventory_slot_5x11Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_6x0Widget, "inventory_slot_6x0");
		MyGUI::Widget* minventory_slot_6x0Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_6x1Widget, "inventory_slot_6x1");
		MyGUI::Widget* minventory_slot_6x1Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_6x2Widget, "inventory_slot_6x2");
		MyGUI::Widget* minventory_slot_6x2Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_6x3Widget, "inventory_slot_6x3");
		MyGUI::Widget* minventory_slot_6x3Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_6x4Widget, "inventory_slot_6x4");
		MyGUI::Widget* minventory_slot_6x4Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_6x5Widget, "inventory_slot_6x5");
		MyGUI::Widget* minventory_slot_6x5Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_6x6Widget, "inventory_slot_6x6");
		MyGUI::Widget* minventory_slot_6x6Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_6x7Widget, "inventory_slot_6x7");
		MyGUI::Widget* minventory_slot_6x7Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_6x8Widget, "inventory_slot_6x8");
		MyGUI::Widget* minventory_slot_6x8Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_6x9Widget, "inventory_slot_6x9");
		MyGUI::Widget* minventory_slot_6x9Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_6x10Widget, "inventory_slot_6x10");
		MyGUI::Widget* minventory_slot_6x10Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, minventory_slot_6x11Widget, "inventory_slot_6x11");
		MyGUI::Widget* minventory_slot_6x11Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, mlevel_EditBox, "level_");
		MyGUI::EditBox* mlevel_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, mstrength_EditBox, "strength_");
		MyGUI::EditBox* mstrength_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, magility_EditBox, "agility_");
		MyGUI::EditBox* magility_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, mstamina_EditBox, "stamina_");
		MyGUI::EditBox* mstamina_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, menergy_EditBox, "energy_");
		MyGUI::EditBox* menergy_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(InventoryPanel, mclose_button_Button, "close_button_");
		MyGUI::Button* mclose_button_Button;
		//%LE Widget_Declaration list end
	};

#endif // _INVENTORY_PANEL_H_

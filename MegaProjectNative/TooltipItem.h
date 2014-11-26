#ifndef _TOOLTIP_ITEM_H_
#define _TOOLTIP_ITEM_H_

#include "stdafx.h"
#include "BaseLayout/BaseLayout.h"

	ATTRIBUTE_CLASS_LAYOUT(TooltipItem, "TooltipItem.layout");
	class TooltipItem :
		public wraps::BaseLayout
	{
	public:
		TooltipItem(MyGUI::Widget* _parent = nullptr);
		virtual ~TooltipItem();
		MyGUI::Widget* getMainWidget()
		{
			return this->mMainWidget;
		}
	//%LE Widget_Declaration list start
		ATTRIBUTE_FIELD_WIDGET_NAME(TooltipItem, mRootWidget, "Root");
		MyGUI::Widget* mRootWidget;
		ATTRIBUTE_FIELD_WIDGET_NAME(TooltipItem, mtooltip_attributePanel_Widget, "tooltip_attributePanel_");
		MyGUI::Widget* mtooltip_attributePanel_Widget;
		ATTRIBUTE_FIELD_WIDGET_NAME(TooltipItem, mitem_name_EditBox, "item_name_");
		MyGUI::EditBox* mitem_name_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(TooltipItem, mattribute_0_EditBox, "attribute_0_");
		MyGUI::EditBox* mattribute_0_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(TooltipItem, mattribute_1_EditBox, "attribute_1_");
		MyGUI::EditBox* mattribute_1_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(TooltipItem, mattribute_2_EditBox, "attribute_2_");
		MyGUI::EditBox* mattribute_2_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(TooltipItem, mattribute_3_EditBox, "attribute_3_");
		MyGUI::EditBox* mattribute_3_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(TooltipItem, mattribute_4_EditBox, "attribute_4_");
		MyGUI::EditBox* mattribute_4_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(TooltipItem, mattribute_5_EditBox, "attribute_5_");
		MyGUI::EditBox* mattribute_5_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(TooltipItem, mattribute_6_EditBox, "attribute_6_");
		MyGUI::EditBox* mattribute_6_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(TooltipItem, mattribute_7_EditBox, "attribute_7_");
		MyGUI::EditBox* mattribute_7_EditBox;
	//%LE Widget_Declaration list end
	};


#endif // _TOOLTIP_ITEM_H_

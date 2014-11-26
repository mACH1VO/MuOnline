#ifndef _MENU_PANEL_H_
#define _MENU_PANEL_H_

#include "stdafx.h"
#include "BaseLayout/BaseLayout.h"
//namespace GUI
//{
	ATTRIBUTE_CLASS_LAYOUT(MenuPanel, "MenuPanel.layout");
	class MenuPanel :
		public wraps::BaseLayout
	{
	public:
		MenuPanel(MyGUI::Widget* _parent = nullptr);
		virtual ~MenuPanel();

		ATTRIBUTE_FIELD_WIDGET_NAME(MenuPanel, mexit_Button, "exit_");
		MyGUI::Button* mexit_Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(MenuPanel, mselectserver_Button, "selectserver_");
		MyGUI::Button* mselectserver_Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(MenuPanel, mselectcharacter_Button, "selectcharacter_");
		MyGUI::Button* mselectcharacter_Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(MenuPanel, msettings_Button, "settings_");
		MyGUI::Button* msettings_Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(MenuPanel, mcancel_Button, "cancel_");
		MyGUI::Button* mcancel_Button;
		//%LE Widget_Declaration list start
		//%LE Widget_Declaration list end

		MyGUI::Widget* getMainWidget()
		{
			return this->mMainWidget;
		}

		void mexit_Button_click(MyGUI::WidgetPtr _sender);
		void mselectserver_Button_click(MyGUI::WidgetPtr _sender);
		void mselectcharacter_Button_click(MyGUI::WidgetPtr _sender);
		void msettings_Button_click(MyGUI::WidgetPtr _sender);
		void mprofilingtool_Button_click(MyGUI::WidgetPtr _sender);
		void mcancel_Button_click(MyGUI::WidgetPtr _sender);
	};
//}


#endif // _MENU_PANEL_H_

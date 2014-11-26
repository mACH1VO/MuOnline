#ifndef _MOVE_PANEL_H_
#define _MOVE_PANEL_H_

#include "stdafx.h"
#include "BaseLayout/BaseLayout.h"

	ATTRIBUTE_CLASS_LAYOUT(MovePanel, "MovePanel.layout");
	class MovePanel :
		public wraps::BaseLayout
	{
	public:
		MovePanel(MyGUI::Widget* _parent = nullptr);
		virtual ~MovePanel();

		MyGUI::Widget* getMainWidget()
		{
			return this->mMainWidget;
		}

		void MovePanel::eventMouseSetFocus(MyGUI::WidgetPtr _sender, MyGUI::Widget* _old);
		void MovePanel::eventMouseLostFocus(MyGUI::WidgetPtr _sender, MyGUI::Widget* _old);

	private:
	//%LE Widget_Declaration list start
		ATTRIBUTE_FIELD_WIDGET_NAME(MovePanel, mbutton_list_1Button, "button_list_1");
		MyGUI::Button* mbutton_list_1Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(MovePanel, mbutton_list_2Button, "button_list_2");
		MyGUI::Button* mbutton_list_2Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(MovePanel, mbutton_list_3Button, "button_list_3");
		MyGUI::Button* mbutton_list_3Button;
	//%LE Widget_Declaration list end
	};

#endif // _MOVE_PANEL_H_

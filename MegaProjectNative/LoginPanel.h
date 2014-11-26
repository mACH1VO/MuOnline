#ifndef _LOGIN_PANEL_H_
#define _LOGIN_PANEL_H_

#include "stdafx.h"
#include "BaseLayout/BaseLayout.h"


	ATTRIBUTE_CLASS_LAYOUT(LoginPanel, "LoginPanel.layout");
	class LoginPanel :
		public wraps::BaseLayout
	{
	public:
		LoginPanel(MyGUI::Widget* _parent = nullptr);
		virtual ~LoginPanel();

		MyGUI::Widget* getMainWidget()
		{
			return this->mMainWidget;
		}

		//%LE Widget_Declaration list start
		ATTRIBUTE_FIELD_WIDGET_NAME(LoginPanel, mmu_Ok_Button, "mu_Ok_");
		MyGUI::Button* mmu_Ok_Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(LoginPanel, mmu_Cancel_Button, "mu_Cancel_");
		MyGUI::Button* mmu_Cancel_Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(LoginPanel, mmu_Account_EditBox, "mu_Account_");
		MyGUI::EditBox* mmu_Account_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(LoginPanel, mmu_Password_EditBox, "mu_Password_");
		MyGUI::EditBox* mmu_Password_EditBox;
		//%LE Widget_Declaration list end

		void mmu_Ok_Button_click(MyGUI::WidgetPtr _sender);
	};

#endif // _LOGIN_PANEL_H_

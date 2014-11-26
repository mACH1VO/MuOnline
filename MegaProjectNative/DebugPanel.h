#ifndef _DEBUG_PANEL_H_
#define _DEBUG_PANEL_H_

#include "stdafx.h"
#include "BaseLayout/BaseLayout.h"

	ATTRIBUTE_CLASS_LAYOUT(DebugPanel, "PanelView.layout");
	class DebugPanel :
		public wraps::BaseLayout
	{
	public:
		DebugPanel(MyGUI::Widget* _parent = nullptr);
		virtual ~DebugPanel();

		ATTRIBUTE_FIELD_WIDGET_NAME(DebugPanel, mpacketlog_ListBox, "packetlog_");
		MyGUI::ListBox* mpacketlog_ListBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(DebugPanel, mgenerateNavMesh_Button, "generateNavMesh_");
		MyGUI::Button* mgenerateNavMesh_Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(DebugPanel, msaveNavMesh_Button, "saveNavMesh_");
		MyGUI::Button* msaveNavMesh_Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(DebugPanel, mshow_bb_Button, "show_bb_");
		MyGUI::Button* mshow_bb_Button;

		MyGUI::Widget* getMainWidget()
		{
			return this->mMainWidget;
		}

		void mconnect_Button_click(MyGUI::WidgetPtr _sender);
		void mgenerateNavMesh_Button_click(MyGUI::WidgetPtr _sender);
		void mcameramode_Button_click(MyGUI::WidgetPtr _sender);
		void mauto_track_playerButton_click(MyGUI::WidgetPtr _sender);
		void mshow_bb_Button_click(MyGUI::WidgetPtr _sender);

		//void mconnect_Button_click2(MyGUI::WidgetPtr _sender):
	};

#endif // _DEBUG_PANEL_H_

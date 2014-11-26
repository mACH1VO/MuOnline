#ifndef _PROFILING_PANEL_H_
#define _PROFILING_PANEL_H_

#include "stdafx.h"
#include "BaseLayout/BaseLayout.h"


	ATTRIBUTE_CLASS_LAYOUT(ProfilingPanel, "ProfilingPanel.layout");
	class ProfilingPanel :
		public wraps::BaseLayout
	{
	public:
		ProfilingPanel(MyGUI::Widget* _parent = nullptr);
		virtual ~ProfilingPanel();

	void update(float timeSinceLastFrame);

	void ProfilingPanel::bar_change_value(MyGUI::ScrollBar* _sender, size_t _position);

	void ProfilingPanel::mcolor_correction_Button_click(MyGUI::WidgetPtr _sender);
	void ProfilingPanel::mbloom_Button_click(MyGUI::WidgetPtr _sender);
	void ProfilingPanel::mvignetting_Button_click(MyGUI::WidgetPtr _sender);
	void ProfilingPanel::mglow_Button_click(MyGUI::WidgetPtr _sender);
	

	void ProfilingPanel::msoftshadows_enable_checkboxButton_click(MyGUI::WidgetPtr _sender);
	void ProfilingPanel::mshadow_texture_size_apply_Button_click(MyGUI::WidgetPtr _sender);

	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mprofilingtool_tabcontrolTabControl, "profilingtool_tabcontrol");
	MyGUI::TabControl* mprofilingtool_tabcontrolTabControl;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mframestatics_tabitemTabItem, "framestatics_tabitem");
	MyGUI::TabItem* mframestatics_tabitemTabItem;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mprof_fpsTextBox, "prof_fps");
	MyGUI::TextBox* mprof_fpsTextBox;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mprof_trianglecountTextBox, "prof_trianglecount");
	MyGUI::TextBox* mprof_trianglecountTextBox;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mprof_batchcountTextBox, "prof_batchcount");
	MyGUI::TextBox* mprof_batchcountTextBox;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mprof_lightsourcesTextBox, "prof_lightsources");
	MyGUI::TextBox* mprof_lightsourcesTextBox;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mseetings_tabitemTabItem, "seetings_tabitem");
	MyGUI::TabItem* mseetings_tabitemTabItem;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mfullscreeneffects_tabitemTabItem, "fullscreeneffects_tabitem");
	MyGUI::TabItem* mfullscreeneffects_tabitemTabItem;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mcolor_correction_Button, "color_correction_");
	MyGUI::Button* mcolor_correction_Button;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mbloom_Button, "bloom_");
	MyGUI::Button* mbloom_Button;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mvignetting_Button, "vignetting_");
	MyGUI::Button* mvignetting_Button;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mglow_Button, "glow_");
	MyGUI::Button* mglow_Button;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mqueue_listbox_ListBox, "queue_listbox_");
	MyGUI::ListBox* mqueue_listbox_ListBox;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mGloomIntensity_barScrollBar, "GloomIntensity_bar");
	MyGUI::ScrollBar* mGloomIntensity_barScrollBar;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mGloomIntensityTextBox, "GloomIntensity");
	MyGUI::TextBox* mGloomIntensityTextBox;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mBaseIntensity_barScrollBar, "BaseIntensity_bar");
	MyGUI::ScrollBar* mBaseIntensity_barScrollBar;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mBaseIntensityTextBox, "BaseIntensity");
	MyGUI::TextBox* mBaseIntensityTextBox;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mGloomSaturationTextBox, "GloomSaturation");
	MyGUI::TextBox* mGloomSaturationTextBox;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mBaseSaturationTextBox, "BaseSaturation");
	MyGUI::TextBox* mBaseSaturationTextBox;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mGloomSaturation_barScrollBar, "GloomSaturation_bar");
	MyGUI::ScrollBar* mGloomSaturation_barScrollBar;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mBaseSaturation_barScrollBar, "BaseSaturation_bar");
	MyGUI::ScrollBar* mBaseSaturation_barScrollBar;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mnetworking_tabitemTabItem, "networking_tabitem");
	MyGUI::TabItem* mnetworking_tabitemTabItem;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mshadows_tabitemTabItem, "shadows_tabitem");
	MyGUI::TabItem* mshadows_tabitemTabItem;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, msoftshadows_enable_checkboxButton, "softshadows_enable_checkbox");
	MyGUI::Button* msoftshadows_enable_checkboxButton;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mshadow_texture_size_ComboBox, "shadow_texture_size_");
	MyGUI::ComboBox* mshadow_texture_size_ComboBox;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mshadow_slider_DiskRadius_ScrollBar, "shadow_slider_DiskRadius_");
	MyGUI::ScrollBar* mshadow_slider_DiskRadius_ScrollBar;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mshadow_texture_size_apply_Button, "shadow_texture_size_apply_");
	MyGUI::Button* mshadow_texture_size_apply_Button;
	ATTRIBUTE_FIELD_WIDGET_NAME(ProfilingPanel, mshadow_diskradius_TextBox, "shadow_diskradius_");
	MyGUI::TextBox* mshadow_diskradius_TextBox;

		MyGUI::Widget* getMainWidget()
		{
			return this->mMainWidget;
		}

		void notifyWindowButtonPressed(MyGUI::Window* _sender, const std::string& _name);
	//%LE Widget_Declaration list end
	};


#endif // _PROFILING_PANEL_H_

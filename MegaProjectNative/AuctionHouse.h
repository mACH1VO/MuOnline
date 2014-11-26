#ifndef _AUCTION_HOUSE_H_
#define _AUCTION_HOUSE_H_
#include "stdafx.h"
#include "BaseLayout/BaseLayout.h"

	ATTRIBUTE_CLASS_LAYOUT(AuctionHouse, "AuctionHouse.layout");
	class AuctionHouse :
		public wraps::BaseLayout
	{
	public:
		AuctionHouse(MyGUI::Widget* _parent = nullptr);
		virtual ~AuctionHouse();

	MyGUI::Widget* getMainWidget()
	{
		return this->mMainWidget;
	}
	private:
	//%LE Widget_Declaration list start
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mRootWidget, "Root");
		MyGUI::Widget* mRootWidget;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mitemtype_combobox_ComboBox, "itemtype_combobox_");
		MyGUI::ComboBox* mitemtype_combobox_ComboBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mrace_combobox_ComboBox, "race_combobox_");
		MyGUI::ComboBox* mrace_combobox_ComboBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, msearch_button_Button, "search_button_");
		MyGUI::Button* msearch_button_Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mauction_list_button_1Button, "auction_list_button_1");
		MyGUI::Button* mauction_list_button_1Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_1_itemnameEditBox, "list_button_1_itemname");
		MyGUI::EditBox* mlist_button_1_itemnameEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_1_itemtypeEditBox, "list_button_1_itemtype");
		MyGUI::EditBox* mlist_button_1_itemtypeEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_1_bidEditBox, "list_button_1_bid");
		MyGUI::EditBox* mlist_button_1_bidEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_1_buyoutEditBox, "list_button_1_buyout");
		MyGUI::EditBox* mlist_button_1_buyoutEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_1_timeleftEditBox, "list_button_1_timeleft");
		MyGUI::EditBox* mlist_button_1_timeleftEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_1_canvasCanvas, "list_button_1_canvas");
		MyGUI::Canvas* mlist_button_1_canvasCanvas;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mauction_list_button_2Button, "auction_list_button_2");
		MyGUI::Button* mauction_list_button_2Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_2_itemnameEditBox, "list_button_2_itemname");
		MyGUI::EditBox* mlist_button_2_itemnameEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_2_itemtypeEditBox, "list_button_2_itemtype");
		MyGUI::EditBox* mlist_button_2_itemtypeEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_2_bidEditBox, "list_button_2_bid");
		MyGUI::EditBox* mlist_button_2_bidEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_2_buyoutEditBox, "list_button_2_buyout");
		MyGUI::EditBox* mlist_button_2_buyoutEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_2_timeleftEditBox, "list_button_2_timeleft");
		MyGUI::EditBox* mlist_button_2_timeleftEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_2_canvasCanvas, "list_button_2_canvas");
		MyGUI::Canvas* mlist_button_2_canvasCanvas;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mauction_list_button_3Button, "auction_list_button_3");
		MyGUI::Button* mauction_list_button_3Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_3_itemnameEditBox, "list_button_3_itemname");
		MyGUI::EditBox* mlist_button_3_itemnameEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_3_itemtypeEditBox, "list_button_3_itemtype");
		MyGUI::EditBox* mlist_button_3_itemtypeEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_3_bidEditBox, "list_button_3_bid");
		MyGUI::EditBox* mlist_button_3_bidEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_3_buyoutEditBox, "list_button_3_buyout");
		MyGUI::EditBox* mlist_button_3_buyoutEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_3_timeleftEditBox, "list_button_3_timeleft");
		MyGUI::EditBox* mlist_button_3_timeleftEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_3_canvasCanvas, "list_button_3_canvas");
		MyGUI::Canvas* mlist_button_3_canvasCanvas;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mauction_list_button_4Button, "auction_list_button_4");
		MyGUI::Button* mauction_list_button_4Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_4_itemnameEditBox, "list_button_4_itemname");
		MyGUI::EditBox* mlist_button_4_itemnameEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_4_itemtypeEditBox, "list_button_4_itemtype");
		MyGUI::EditBox* mlist_button_4_itemtypeEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_4_bidEditBox, "list_button_4_bid");
		MyGUI::EditBox* mlist_button_4_bidEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_4_buyoutEditBox, "list_button_4_buyout");
		MyGUI::EditBox* mlist_button_4_buyoutEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_4_timeleftEditBox, "list_button_4_timeleft");
		MyGUI::EditBox* mlist_button_4_timeleftEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_4_canvasCanvas, "list_button_4_canvas");
		MyGUI::Canvas* mlist_button_4_canvasCanvas;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mauction_list_button_5Button, "auction_list_button_5");
		MyGUI::Button* mauction_list_button_5Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_5_itemnameEditBox, "list_button_5_itemname");
		MyGUI::EditBox* mlist_button_5_itemnameEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_5_itemtypeEditBox, "list_button_5_itemtype");
		MyGUI::EditBox* mlist_button_5_itemtypeEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_5_bidEditBox, "list_button_5_bid");
		MyGUI::EditBox* mlist_button_5_bidEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_5_buyoutEditBox, "list_button_5_buyout");
		MyGUI::EditBox* mlist_button_5_buyoutEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_5_timeleftEditBox, "list_button_5_timeleft");
		MyGUI::EditBox* mlist_button_5_timeleftEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_5_canvasCanvas, "list_button_5_canvas");
		MyGUI::Canvas* mlist_button_5_canvasCanvas;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mauction_list_button_6Button, "auction_list_button_6");
		MyGUI::Button* mauction_list_button_6Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_6_itemnameEditBox, "list_button_6_itemname");
		MyGUI::EditBox* mlist_button_6_itemnameEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_6_itemtypeEditBox, "list_button_6_itemtype");
		MyGUI::EditBox* mlist_button_6_itemtypeEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_6_bidEditBox, "list_button_6_bid");
		MyGUI::EditBox* mlist_button_6_bidEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_6_buyoutEditBox, "list_button_6_buyout");
		MyGUI::EditBox* mlist_button_6_buyoutEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_6_timeleftEditBox, "list_button_6_timeleft");
		MyGUI::EditBox* mlist_button_6_timeleftEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_6_canvasCanvas, "list_button_6_canvas");
		MyGUI::Canvas* mlist_button_6_canvasCanvas;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mauction_list_button_7Button, "auction_list_button_7");
		MyGUI::Button* mauction_list_button_7Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_7_itemnameEditBox, "list_button_7_itemname");
		MyGUI::EditBox* mlist_button_7_itemnameEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_7_itemtypeEditBox, "list_button_7_itemtype");
		MyGUI::EditBox* mlist_button_7_itemtypeEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_7_bidEditBox, "list_button_7_bid");
		MyGUI::EditBox* mlist_button_7_bidEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_7_buyoutEditBox, "list_button_7_buyout");
		MyGUI::EditBox* mlist_button_7_buyoutEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_7_timeleftEditBox, "list_button_7_timeleft");
		MyGUI::EditBox* mlist_button_7_timeleftEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_7_canvasCanvas, "list_button_7_canvas");
		MyGUI::Canvas* mlist_button_7_canvasCanvas;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mauction_list_button_8Button, "auction_list_button_8");
		MyGUI::Button* mauction_list_button_8Button;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_8_itemnameEditBox, "list_button_8_itemname");
		MyGUI::EditBox* mlist_button_8_itemnameEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_8_itemtypeEditBox, "list_button_8_itemtype");
		MyGUI::EditBox* mlist_button_8_itemtypeEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_8_bidEditBox, "list_button_8_bid");
		MyGUI::EditBox* mlist_button_8_bidEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_8_buyoutEditBox, "list_button_8_buyout");
		MyGUI::EditBox* mlist_button_8_buyoutEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_8_timeleftEditBox, "list_button_8_timeleft");
		MyGUI::EditBox* mlist_button_8_timeleftEditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(AuctionHouse, mlist_button_8_canvasCanvas, "list_button_8_canvas");
		MyGUI::Canvas* mlist_button_8_canvasCanvas;
	//%LE Widget_Declaration list end
	};

#endif // _AUCTION_HOUSE_H_

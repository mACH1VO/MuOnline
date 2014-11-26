#ifndef _CHAT_H_
#define _CHAT_H_

#include "stdafx.h"
#include "BaseLayout/BaseLayout.h"

namespace Messages
{
	class GameMessage;
}

	ATTRIBUTE_CLASS_LAYOUT(Chat, "Chat.layout");
	class Chat :
		public wraps::BaseLayout
	{
	public:
		Chat(MyGUI::Widget* _parent = nullptr);
		virtual ~Chat();

		void mnormal_EditBox_eventKeyButtonPressed(MyGUI::Widget* _sender, MyGUI::KeyCode _key, MyGUI::Char _char);

		void Consume(Messages::GameMessage* message);

		std::deque<string>* recorded_deque_text;

		MyGUI::Widget* getMainWidget()
		{
			return this->mMainWidget;
		}
		bool inline isActive()
		{
			return this->mMainWidget->getVisible();
		}
		void ProcessEnter();
	//%LE Widget_Declaration list start
		ATTRIBUTE_FIELD_WIDGET_NAME(Chat, mnormal_EditBox, "normal_");
		MyGUI::EditBox* mnormal_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(Chat, mwhisper_EditBox, "whisper_");
		MyGUI::EditBox* mwhisper_EditBox;
		ATTRIBUTE_FIELD_WIDGET_NAME(Chat, mchat_record_EditBox, "chat_record_");
		MyGUI::EditBox* mchat_record_EditBox;
	//%LE Widget_Declaration list end

	private:
		int _indexEditBoxArrows;
	};


#endif // _CHAT_H_

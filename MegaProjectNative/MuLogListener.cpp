#include "StdAfx.h"
#include "MuLogListener.h"

#include "DebugPanel.h"
#include "GameGUI.h"
#include "GameFramework.h"


MuLogListener::MuLogListener(void)
{

}


MuLogListener::~MuLogListener(void)
{

}


void MuLogListener::messageLogged( const String& message, LogMessageLevel lml, bool maskDebug, const String &logName, bool& skipThisMessage )
{
	DebugPanel *dp = GameFramework::getSingletonPtr()->getGameGUI()->getDebugPanel();
	if (dp)
	{
		/*MyGUI::ListBox* listBox = GameFramework::getSingletonPtr()->getGameGUI()->getDebugPanel()->mpacketlog_ListBox;
		listBox->addItem(message);*/
	}
}
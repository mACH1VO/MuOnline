//|||||||||||||||||||||||||||||||||||||||||||||||
#pragma once

#include "stdafx.h"
#include "Ogre.h"
#include "GameFramework.h"

//|||||||||||||||||||||||||||||||||||||||||||||||

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

//|||||||||||||||||||||||||||||||||||||||||||||||

//INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
int main(int argc, char **argv)
{
	try
	{
		GameFramework mu;
		mu.Start();
	}
	catch(std::exception& e)
	{
		MessageBoxA(NULL, e.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}

	return 0;
}

//|||||||||||||||||||||||||||||||||||||||||||||||
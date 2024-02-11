#pragma once
#include "Application.h"

#ifdef GUIMAKER_PLATFORM_WINDOWS

// ReSharper disable once CppNonInlineFunctionDefinitionInHeaderFile
int main(int argc, char** argv)
{
	EopGuiMaker::Log::Init();
	GUIMAKER_CORE_INFO("Started Core");
	GUIMAKER_APP_INFO("Started Client");

	const auto app = EopGuiMaker::CreateApplication();
	app->Run();
	delete app;
}


#endif

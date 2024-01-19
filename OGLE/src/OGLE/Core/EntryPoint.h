#pragma once
#include "OGLE/Core/Base.h"
#include "OGLE/Core/Application.h"

#ifdef OGLE_PLATFORM_WINDOWS

extern OGLE::Application* OGLE::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	OGLE::Log::Init();

	OGLE_PROFILE_BEGIN_SESSION("Startup", "OGLEProfile-Startup.json");
	auto app = OGLE::CreateApplication({ argc, argv });
	OGLE_PROFILE_END_SESSION();

	OGLE_PROFILE_BEGIN_SESSION("Runtime", "OGLEProfile-Runtime.json");
	app->Run();
	OGLE_PROFILE_END_SESSION();

	OGLE_PROFILE_BEGIN_SESSION("Shutdown", "OGLEProfile-Shutdown.json");
	delete app;
	OGLE_PROFILE_END_SESSION();
}

#endif
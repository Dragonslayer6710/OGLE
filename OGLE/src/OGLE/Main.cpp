#include "oglepch.h"
#include "OGLE/Core/EntryPoint.h"


namespace OGLE
{
	class OGLEApp : public Application
	{
	public:
		OGLEApp(const ApplicationSpecification& spec)
			: Application(spec)
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "OGLEApp";
		spec.CommandLineArgs = args;
		return new OGLEApp(spec);
	}
}
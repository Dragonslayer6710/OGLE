#include "oglepch.h"
#include "OGLE/Core/EntryPoint.h"

#include "OGLE/Display/Layer/GameWorldLayer.h"

namespace OGLE
{
	class OGLEApp : public Application
	{
	public:
		OGLEApp(const ApplicationSpecification& spec)
			: Application(spec)
		{
			PushLayer(new GameWorldLayer(*m_Renderer));
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
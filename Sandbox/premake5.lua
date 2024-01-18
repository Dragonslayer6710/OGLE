project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "%/{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "%/{prj.name}")

	files{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs{
		-- "%{wks.location}/OpenGLEngine/vendor/spdlog/include",
		"%{wks.location}/OpenGLEngine/src",
		"%{wks.location}/OpenGLEngine/vendor",
		"%{IncludeDir.glm}",
		-- "%{IncludeDir.entt}"
	}

	links{
		"OpenGLEngine"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "OGLE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "OGLE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "OGLE_DIST"
		runtime "Release"
		optimize "on"
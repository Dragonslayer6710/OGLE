include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "OpenGLEngine"
	architecture "x86_64"
	-- startproject "OGLE Editor"

	configurations {
		"Debug", 
		"Release", 
		"Dist"
	}

	solution_items{
		".editorconfig"
	}

	flags{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "vendor/premake"
	-- include "OpenGLEngine/vendor/Box2D"
	include "OpenGLEngine/vendor/GLFW"
	include "OpenGLEngine/vendor/Glad"
	-- include "OpenGLEngine/vendor/msdf-atlas-gen"
	include "OpenGLEngine/vendor/imgui"
	-- include "OpenGLEngine/vendor/yaml-cpp"
group ""

group "Core"
	include "OpenGLEngine"
	-- include "OpenGLEngine-ScriptCore"
group ""

-- group "Tools"
	-- include "OGLE Editor"
-- group ""

group "Misc"
	include "Sandbox"
group ""
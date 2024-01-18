include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "OGLE"
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
	-- include "OGLE/vendor/Box2D"
	include "OGLE/vendor/GLFW"
	include "OGLE/vendor/Glad"
	-- include "OGLE/vendor/msdf-atlas-gen"
	include "OGLE/vendor/imgui"
	-- include "OGLE/vendor/yaml-cpp"
group ""

group "Core"
	include "OGLE"
	-- include "OGLE-ScriptCore"
group ""

-- group "Tools"
	-- include "OGLE Editor"
-- group ""

group "Misc"
	include "Sandbox"
group ""
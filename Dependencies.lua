
-- OGLE Dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["stb_image"] = "%{wks.location}/OGLE/vendor/stb_image"
-- IncludeDir["yaml_cpp"] = "%{wks.location}/OGLE/vendor/yaml-cpp/include"
-- IncludeDir["Box2D"] = "%{wks.location}/OGLE/vendor/Box2D/include"
-- IncludeDir["filewatch"] = "%{wks.location}/OGLE/vendor/filewatch"
IncludeDir["GLFW"] = "%{wks.location}/OGLE/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/OGLE/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/OGLE/vendor/imgui"
-- IncludeDir["ImGuizmo"] = "%{wks.location}/OGLE/vendor/ImGuizmo"
IncludeDir["glm"] = "%{wks.location}/OGLE/vendor/glm"
-- IncludeDir["entt"] = "%{wks.location}/OGLE/vendor/entt/include"
-- IncludeDir["mono"] = "%{wks.location}/OGLE/vendor/mono/include"
IncludeDir["shaderc"] = "%{wks.location}/OGLE/vendor/shaderc/include"
IncludeDir["SPIRV_Cross"] = "%{wks.location}/OGLE/vendor/SPIRV-Cross"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
IncludeDir["msdfgen"] = "%{wks.location}/OGLE/vendor/msdf-atlas-gen/msdfgen"
IncludeDir["msdf_atlas_gen"] = "%{wks.location}/OGLE/vendor/msdf-atlas-gen/msdf-atlas-gen"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
-- LibraryDir["mono"] = "%{wks.location}/OGLE/vendor/mono/lib/%{cfg.buildcfg}"

Library = {}
-- Library["mono"] = "%{LibraryDir.mono}/libmono-static-sgen.lib"

Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"

-- Windows
Library["WinSock"] = "Ws2_32.lib"
Library["WinMM"] = "Winmm.lib"
Library["WinVersion"] = "Version.lib"
Library["BCrypt"] = "Bcrypt.lib"
-- premake5.lua
workspace "WinApiTextEditor"
   architecture "x64"
   configurations { "Debug", "Release"}
   startproject "App"

   warnings "Extra" -- This enforces /W4 across all projects

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus", "/W4", "/w44365" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Core"
	include "Core/Build-Core.lua"
group ""

include "App/Build-App.lua"
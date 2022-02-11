workspace "cah_file"
	configurations { "Release", "Debug" }
	location "build"

	files { "src/*.*" }
	includedirs { "src" }

project "cah_file"
	kind "ConsoleApp"
	language "C++"
	targetname "cah_file"
	targetdir "bin/%{cfg.buildcfg}"

	characterset ("MBCS")
	-- toolset ("v141_xp")
	links { "legacy_stdio_definitions" }
	defines { "WIN32_LEAN_AND_MEAN", "VC_EXTRALEAN", "WIN32_LEAN_AND_MEAN", "_CRT_SECURE_NO_WARNINGS", "_CRT_NONSTDC_NO_DEPRECATE" }

	filter "configurations:Debug"
		defines { "_DEBUG" }
		symbols "full"
		optimize "off"
		runtime "debug"
		staticruntime "on"

	filter "configurations:Release"
		defines { "NDEBUG" }
		symbols "on"
		optimize "speed"
		runtime "release"
		staticruntime "on"
		flags { "LinkTimeOptimization" }

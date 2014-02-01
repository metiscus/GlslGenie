solution "GlslGenie"
	configurations { "Debug", "Release" }
	
	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" }
 
	configuration "Release"
		defines { "NDEBUG" }
        flags { "Optimize" } 
		
	project "GlslGenie"
		kind "WindowedApp"
		language "C++"
		files { "src/**.cpp",
				"src/**.h"
		}
		defines { "_CRT_SECURE_NO_WARNINGS" }
		buildoptions{ "/wd4396" }	-- suppress inline specifier friend declaration warning
		flags { "Unicode", "WinMain" }
		includedirs{ 
			"extern/oglplus/implement",
			"extern/oglplus/include", 
			"extern/oglplus/build/include",
			"extern/glew-1.10.0/include",
			"extern/freeglut/include",
			-- wxWidgets
			"c:/wxWidgets-2.9.5/include", 
			"c:/wxWidgets-2.9.5/include/msvc", 
			"c:/wxWidgets-2.9.5/lib/"			
		}
		
		libdirs{
			"extern/freeglut/lib",
			"extern/glew-1.10.0/lib/Release/Win32",
			-- wxWidgets
			"c:/wxWidgets-2.9.5/lib/vc_lib" 
			}
		links{"glew32"}
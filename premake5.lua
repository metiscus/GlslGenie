dofile "bulkbuild.lua"

--updateBulkBuild();

local action = _ACTION or ""

solution "GlslGenie"
	configurations { "Debug", "Release" }
	location( "build/" .. action )
	
	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" }
 
	configuration "Release"
		defines { "NDEBUG" }
        flags { "Optimize" } 

	project "Lua-5.1"
		location( "build/" .. action )
		kind "StaticLib"
		language "C"
		defines { "_CRT_SECURE_NO_WARNINGS" }
		files { "tools/lua-5.1/src/*.c", "tools/lua-5.1/src/*.h" }
		excludes { "tools/lua-5.1/src/lua.c", "tools/lua-5.1/src/luac.c" }
	
	project "libtolua++"
		location( "build/" .. action )
		kind "StaticLib"
		language "C++"
		defines { "_CRT_SECURE_NO_WARNINGS" }
		files { "tools/tolua/lib_src/*.*" }
		links { "Lua-5.1" }
		includedirs{ "tools/lua-5.1/src/" }
		
	project "tolua++"
		location( "build/" .. action )
		kind "ConsoleApp"
		language "C++"
		defines { "_CRT_SECURE_NO_WARNINGS" }
		files { "tools/tolua/bin_src/*.*", }
		links { "Lua-5.1", "libtolua++" }
		includedirs{ "tools/lua-5.1/src/", "tools/tolua/lib_src" }
		
	project "GlslGenie"
		location( "build/" .. action )
		kind "WindowedApp"
		language "C++"
		files { "src/**.cpp",
				"src/**.h"
		}
		excludes { "src/bb.cpp" }
		defines { "_CRT_SECURE_NO_WARNINGS" }
		buildoptions{ "/wd4396" }	-- suppress inline specifier friend declaration warning
		flags { 
			"Unicode"
			,"WinMain" 
		  --, "ExcludeFromBuild" 
		}
		includedirs{ 
			"extern/oglplus/implement",
			"extern/oglplus/include", 
			"extern/oglplus/build/include",
			"extern/glew-1.10.0/include",
			"extern/freeglut/include",
			"extern/rapidxml-1.13",
			"extern/libpng-1.2.37/include",
			"extern/zlib-1.2.7/",
			-- wxWidgets
			"c:/wxWidgets-2.9.5/include", 
			"c:/wxWidgets-2.9.5/include/msvc", 
			"c:/wxWidgets-2.9.5/lib/"			
		}
		
		if action == "clean" then
		  os.rmdir("build")
		end		
		
		libdirs{
			"extern/freeglut/lib",
			"extern/glew-1.10.0/lib/Release/Win32",
			"extern/libpng-1.2.37/lib",
			-- wxWidgets
			"c:/wxWidgets-2.9.5/lib/vc_lib"			
			}
		links{"glew32", "libpng"}
		
--	project "GlslGenie_BulkBuild"
--		kind "WindowedApp"
--		language "C++"
--		files { "src/bb.cpp" }
--		defines { "_CRT_SECURE_NO_WARNINGS" }
--		buildoptions{ "/wd4396" }	-- suppress inline specifier friend declaration warning
--		flags { "Unicode", "WinMain", "ExcludeFromBuild" }
--		includedirs{ 
--			"extern/oglplus/implement",
--			"extern/oglplus/include", 
--			"extern/oglplus/build/include",
--			"extern/glew-1.10.0/include",
--			"extern/freeglut/include",
--			-- wxWidgets
--			"c:/wxWidgets-2.9.5/include", 
--			"c:/wxWidgets-2.9.5/include/msvc", 
--			"c:/wxWidgets-2.9.5/lib/"			
--		}
--		
--		libdirs{
--			"extern/freeglut/lib",
--			"extern/glew-1.10.0/lib/Release/Win32",
--			-- wxWidgets
--			"c:/wxWidgets-2.9.5/lib/vc_lib" 
--			}
--		links{"glew32"}		
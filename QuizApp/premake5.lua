project "QuizApp"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    files {
        "src/**.h", "src/**.cpp",
        "%{wks.location}/external/glad/src/**.c"
    }

    includedirs {
        "%{wks.location}/external/imgui",
        "%{wks.location}/external/glfw/include",
        "%{wks.location}/external/glad/include"
    }

    libdirs {
        "%{wks.location}/external/bin/Debug-windows-x86_64/Imgui",
        "%{wks.location}/external/glfw/lib-vc2022",
    }

    links {
        "Imgui", "glfw3", "opengl32"
    }

    filter "configurations:Debug"
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      runtime "Release"
      optimize "On"
      symbols "On"
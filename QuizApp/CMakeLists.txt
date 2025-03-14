file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

add_executable(QuizApp ${SOURCES})
target_sources(QuizApp PRIVATE ${SOURCES} ${HEADERS})

find_package(glad REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

target_link_libraries(QuizApp PRIVATE glad::glad imgui::imgui glfw fmt::fmt)
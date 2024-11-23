# CMakeList.txt : CMake project for Puzzle, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Puzzle")


include(FetchContent)

# Dependencies
set(RAYLIB_VERSION 5.0)

FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS
)

FetchContent_MakeAvailable(raylib)

# Add source to this project's executable.
add_executable (Puzzle "src/Puzzle.cpp" "src/Puzzle.h" "src/scene/Scene.h" "src/scene/SceneID.h" "src/scene/ChooseImageScene.cpp" "src/scene/PuzzleScene.cpp" "src/scene/Scene.cpp" "src/constants.h" "src/components/Component.h" "src/components/Component.cpp" "src/components/Image.cpp" "src/components/Border.cpp" "src/components/Grid.cpp" "src/util/util.h" "src/util/globals.h" "src/util/TexturePool.h" "src/util/TexturePool.cpp" "src/util/util.cpp" "src/components/ImageButton.cpp"   "src/components/PuzzleGrid.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Puzzle PROPERTY CXX_STANDARD 20)
endif()


add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

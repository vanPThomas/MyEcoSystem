cmake_minimum_required(VERSION 3.16)
project(MyEcoSystem VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- version -------------------------------------------------
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

add_compile_definitions(PROJECT_VERSION="${PROJECT_VERSION}")
# -------------------------------------------------------------

# MyEcoSystem
add_executable(MyEcoSystem
    src/main.cpp
    src/UI/UIManager.cpp
    src/Creature/Creature.cpp
    src/Creature/DNA.cpp
    src/Creature/Brain.cpp
    src/Utils/MathUtils.cpp
    src/World/Plant.cpp
    src/World/Environment.cpp
    src/Creature/Herbivore.cpp
    src/Creature/Carnivore.cpp
    
    # ImGui core
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_tables.cpp

    # ImGui backends
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp

    imgui/misc/cpp/imgui_stdlib.cpp
)

# Include directories for our code + ImGui
target_include_directories(MyEcoSystem PRIVATE
    include
    imgui
    imgui/backends
    imgui/misc/cpp
)

# Find system libs
find_package(PkgConfig REQUIRED)

# GLFW
pkg_search_module(GLFW REQUIRED glfw3)
target_link_libraries(MyEcoSystem ${GLFW_LIBRARIES})
target_include_directories(MyEcoSystem PRIVATE ${GLFW_INCLUDE_DIRS})

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(MyEcoSystem OpenGL::GL)

# Linux defaults (dl, pthread)
target_link_libraries(MyEcoSystem dl pthread)

# Output to bin/
set_target_properties(MyEcoSystem PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

message("
Behavioral AI system
")

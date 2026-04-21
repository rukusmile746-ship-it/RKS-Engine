cmake_minimum_required(VERSION 3.16)
project(NodeEditorDemo)

set(CMAKE_CXX_STANDARD 17)

# Trouver SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Chemins vers les bibliothèques
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/../../librairie/libs/imgui)
set(IMGUI_SFML_DIR ${CMAKE_SOURCE_DIR}/../../librairie/libs/imgui-sfml)

# Fichiers source
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
)

set(IMGUI_SFML_SOURCES
    ${IMGUI_SFML_DIR}/imgui-SFML.cpp
)

file(GLOB_RECURSE SOURCE CONFIGURE_DEPENDS "src/*.cpp")

# Sources du projet
set(PROJECT_SOURCES
    ${SOURCE}
    ${IMGUI_SOURCES}
    ${IMGUI_SFML_SOURCES}
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Exécutable
add_executable(OUT ${PROJECT_SOURCES})

# Includes
target_include_directories(OUT PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_SFML_DIR}
    ${CMAKE_SOURCE_DIR}/include
)

# OpenGL
find_package(OpenGL REQUIRED)

# Link
target_link_libraries(OUT
    sfml-graphics
    sfml-window
    sfml-system
    OpenGL::GL
)

# Définitions
target_compile_definitions(OUT PRIVATE
    IMGUI_SFML_USE_OPENGL_FIXED_PIPELINE
    IMGUI_DEFINE_MATH_OPERATORS
)

# Settings
include_directories(Engine/Includes/GL)
include_directories(Engine/Includes/glad)
include_directories(Engine/Includes/GLFW)
include_directories(Engine/Includes/glm)
include_directories(Engine/Includes/assimp)
include_directories(Engine/Includes/ImGUI)
include_directories(Engine/Includes/asio-1.24.0/include)

# Files
file(GLOB_RECURSE ENGINE_SOURCES *.cpp *.c)
file(GLOB_RECURSE ENGINE_HEADERS *.h *.hpp *.inl)

# Executable
add_executable(Unireal ${ENGINE_SOURCES} ${ENGINE_HEADERS})

# Libraries
target_link_libraries(Unireal glfw3 opengl32 User32 Gdi32 Shell32 glew32s assimp)

# Find Root Directory
get_filename_component(PROJECT_ROOT ${CMAKE_SOURCE_DIR} ABSOLUTE)

add_compile_definitions(PROJECT_CONTENTS_PATH="${PROJECT_ROOT}/Contents")
target_compile_definitions(Unireal PRIVATE PROJECT_CONTENTS_PATH)
add_definitions(-DPROJECT_CONTENTS_PATH)

add_compile_definitions(WITH_EDITOR)
target_compile_definitions(Unireal PRIVATE WITH_EDITOR)
add_definitions(-DWITH_EDITOR)

TARGET_COMPILE_DEFINITIONS(Unireal PUBLIC GLEW_STATIC)
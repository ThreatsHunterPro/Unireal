# Settings
INCLUDE_DIRECTORIES(Engine/OLD/GL)
INCLUDE_DIRECTORIES(Engine/OLD/glad)
INCLUDE_DIRECTORIES(Engine/OLD/GLFW)
INCLUDE_DIRECTORIES(Engine/OLD/glm)
INCLUDE_DIRECTORIES(Engine/OLD/assimp)
INCLUDE_DIRECTORIES(Engine/OLD/ImGUI)
INCLUDE_DIRECTORIES(Engine/OLD/asio-1.24.0/include)

# Files
FILE(GLOB_RECURSE ENGINE_SOURCES *.cpp *.c)
FILE(GLOB_RECURSE ENGINE_HEADERS *.h *.hpp *.inl)

# Executable
ADD_EXECUTABLE(Unireal ${ENGINE_SOURCES} ${ENGINE_HEADERS})

# Libraries
TARGET_LINK_LIBRARIES(Unireal glfw3 opengl32 User32 Gdi32 Shell32 glew32s assimp)

# Find Root Directory
get_filename_component(PROJECT_ROOT ${CMAKE_SOURCE_DIR} ABSOLUTE)

add_compile_definitions(PROJECT_CONTENTS_PATH="${PROJECT_ROOT}/Contents")
target_compile_definitions(Unireal PRIVATE PROJECT_CONTENTS_PATH)
add_definitions(-DPROJECT_CONTENTS_PATH)

add_compile_definitions(WITH_EDITOR)
target_compile_definitions(Unireal PRIVATE WITH_EDITOR)
add_definitions(-DWITH_EDITOR)

TARGET_COMPILE_DEFINITIONS(Unireal PUBLIC GLEW_STATIC)
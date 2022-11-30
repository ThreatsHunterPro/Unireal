cmake_minimum_required(VERSION 3.0) # Version
project(Unireal) # Projet name
set(CMAKE_CXX_STANDARD 14) # Enable c++14 standard
set(SOURCE_FILES main.cpp) # Add main.cpp file of project root directory as source file

# Recherche la dépendance externe
find_package (External/glfw-3.1.2)

if (glfw-3.1.2_FOUND)
  # Une fois la dépendance trouvée, nous l'incluons au projet
  target_include_directories(main PUBLIC ${PNG_INCLUDE_DIR})
  target_link_libraries (main ${PNG_LIBRARY})
  
else ()
  # Sinon, nous affichons un message
  message(FATAL_ERROR "libpng not found")
  
endif ()
    
add_subdirectory(External)
    
# Crée des variables avec les fichiers à compiler
set(SRCS
    main.c
    )
        
set(HEADERS
    hello.h
    )

# On indique que l'on veut un exécutable "hello" compilé à partir des fichiers décrits par les variables SRCS et HEADERS
add_executable(Unireal ${SRCS} ${HEADERS})
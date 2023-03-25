# Recurse game sources files
file(GLOB_RECURSE GAME_SOURCES *.cpp *.c)
file(GLOB_RECURSE GAME_HEADERS *.hpp *.h *.inl)

# Add executable
add_executable(game ${GAME_SOURCES} ${GAME_HEADERS})

# Link libraries
if(WIN32)
	target_link_libraries(game SDL2.lib SDL2main.lib glew32.lib opengl32.lib assimp-vc143-mt.lib freetype.lib)
endif()

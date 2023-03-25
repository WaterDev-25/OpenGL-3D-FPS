# Recurse game sources files
file(GLOB_RECURSE SERVER_SOURCES *.cpp *.c)
file(GLOB_RECURSE SERVER_HEADERS *.hpp *.h *.inl)

# Add executable
add_executable(server ${SERVER_SOURCES} ${SERVER_HEADERS})

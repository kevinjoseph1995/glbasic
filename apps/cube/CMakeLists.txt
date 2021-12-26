add_executable(cube entry_point.cpp cube.hpp)
target_link_libraries(cube PRIVATE glbasic)
target_compile_definitions(cube PUBLIC SHADER_SOURCE="${PROJECT_SOURCE_DIR}/assets/shaders")
target_compile_definitions(cube PUBLIC TEXTURE_SOURCE="${PROJECT_SOURCE_DIR}/assets/textures")
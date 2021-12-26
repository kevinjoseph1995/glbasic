add_library(glbasic STATIC
        core/glbasic/application.cpp
        core/glbasic/imgui_layer.cpp
        core/glbasic/input.cpp
        core/glbasic/layer_stack.cpp
        core/glbasic/window_manager.cpp

        core/glbasic/renderer/buffer.cpp
        core/glbasic/renderer/renderer.cpp
        core/glbasic/renderer/shader.cpp
        core/glbasic/renderer/texture.cpp
        core/glbasic/renderer/camera.cpp
        core/glbasic/renderer/vertex_array.cpp
        core/glbasic/renderer/rendering_context.cpp
        core/glbasic/renderer/render_command.cpp
        core/glbasic/renderer/render_api.cpp
        core/glbasic/renderer/camera_controller.cpp

        # glbasic object sources
        core/glbasic/objects/cube.cpp

        platform/opengl/opengl_buffer.cpp
        platform/opengl/opengl_context.cpp
        platform/opengl/opengl_shader.cpp
        platform/opengl/opengl_texture.cpp
        platform/opengl/opengl_vertex_array.cpp
        platform/opengl/opengl_debug_callback.cpp
        platform/opengl/opengl_render_api.cpp

        # Utils
        core/glbasic/utils/file_utils.cpp
        )

target_include_directories(glbasic PUBLIC core/)
target_include_directories(glbasic PRIVATE platform/)
target_link_libraries(glbasic PUBLIC glad spdlog -lstdc++fs stb_image -lglfw -ldl glm::glm imgui)
target_compile_options(glbasic PRIVATE -Wall -Wextra -Wpedantic -Werror)
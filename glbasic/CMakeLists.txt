add_library(glbasic STATIC
        core/src/application.cpp
        core/src/imgui_layer.cpp
        core/src/input.cpp
        core/src/layer_stack.cpp
        core/src/window_manager.cpp

        core/src/renderer/buffer.cpp
        core/src/renderer/renderer.cpp
        core/src/renderer/shader.cpp
        core/src/renderer/texture.cpp
        core/src/renderer/camera.cpp
        core/src/renderer/vertex_array.cpp
        core/src/renderer/rendering_context.cpp
        core/src/renderer/render_command.cpp
        core/src/renderer/render_api.cpp
        core/src/renderer/camera_controller.cpp


        core/src/objects/cube.cpp

        platform/opengl/opengl_buffer.cpp
        platform/opengl/opengl_context.cpp
        platform/opengl/opengl_shader.cpp
        platform/opengl/opengl_texture.cpp
        platform/opengl/opengl_vertex_array.cpp
        platform/opengl/opengl_debug_callback.cpp
        platform/opengl/opengl_render_api.cpp

        # Utils
        core/src/file_utils.cpp
        )

target_include_directories(glbasic PUBLIC core/include)
target_include_directories(glbasic PRIVATE platform/)
target_link_libraries(glbasic PUBLIC glad spdlog -lstdc++fs stb_image -lglfw -ldl glm::glm imgui)
target_compile_options(glbasic PRIVATE -Wall -Wextra -Wpedantic -Werror)
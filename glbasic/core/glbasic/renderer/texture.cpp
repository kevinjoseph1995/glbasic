//
// Created by kevin on 6/30/21.
//

#include "texture.h"
#include "opengl/opengl_texture.h"

namespace glbasic
{
std::shared_ptr<Texture> Texture::Create(const std::string &texture_file, const bool flip_on_load)
{
    return std::make_shared<OpenGLTexture2D>(texture_file, flip_on_load);
}
} // namespace glbasic

//
// Created by kevin on 7/23/21.
//

#include "opengl_texture.h"

#include "glbasic/gl_debug.h"
#include "spdlog/spdlog.h"
#include "stb_image.h"

#include <experimental/filesystem>
#include <glad/glad.h>

namespace glbasic
{
OpenGLTexture2D::OpenGLTexture2D(const std::string &texture_file, const bool flip_on_load)
{
    initialize();
    loadTextureFromFile(texture_file, flip_on_load);
}
OpenGLTexture2D::OpenGLTexture2D(int32_t width, int32_t height, int32_t channels)
    : width_{width}, height_(height), num_channels_(channels)
{
    initialize();
    uint32_t format = 0;
    switch (num_channels_)
    {
    case 3:
        format = GL_RGB;
        break;

    case 4:
        format = GL_RGBA;
        break;

    default:
        GL_ASSERT(true, "[OpenGLTexture2D::LoadTextureFromFile] Invalid number of channels ");
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, format, GL_UNSIGNED_BYTE, nullptr);
    glGenerateMipmap(GL_TEXTURE_2D);
}
void OpenGLTexture2D::loadTextureFromFile(const std::string &texture_file, const bool flip_on_load)
{
    GL_ASSERT(id_ != 0, "[OpenGLTexture2D]Has Texture::initialize() been called");
    GL_ASSERT(std::experimental::filesystem::is_regular_file(texture_file),
              "[OpenGLTexture2D::LoadTextureFromFile] is not a regular file");

    stbi_set_flip_vertically_on_load(flip_on_load);
    unsigned char *data = stbi_load(texture_file.c_str(), &width_, &height_, &num_channels_, 0);
    GL_ASSERT(data, "[OpenGLTexture2D::LoadTextureFromFile] Failed to read file");
    GL_ASSERT(num_channels_ == 3 || num_channels_ == 4,
              "[OpenGLTexture2D::LoadTextureFromFile] Invalid number of channels");

    uint32_t format = 0;
    switch (num_channels_)
    {
    case 3:
        format = GL_RGB;
        break;

    case 4:
        format = GL_RGBA;
        break;

    default:

        GL_ASSERT(true, "[OpenGLTexture2D::LoadTextureFromFile] Invalid number of channels ");
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}
void OpenGLTexture2D::initialize()
{
    GL_ASSERT(id_ == 0, "[OpenGLTexture2D::Initialize]");
    glGenTextures(1, &id_);
    glBindTexture(GL_TEXTURE_2D, id_);
    // TODO: Make this configurable
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
void OpenGLTexture2D::Bind(uint32_t tex_unit_slot) const
{
    GL_ASSERT(id_ != 0, "[OpenGLTexture2D::Bind]");
    glActiveTexture(GL_TEXTURE0 + tex_unit_slot);
    glBindTexture(GL_TEXTURE_2D, id_);
}
void OpenGLTexture2D::UnBind() const
{
    GL_ASSERT(id_ != 0, "[OpenGLTexture2D::Bind]");
    glBindTexture(GL_TEXTURE_2D, 0);
}
OpenGLTexture2D::~OpenGLTexture2D()
{
    GL_ASSERT(id_ != 0, "[OpenGLTexture2D::Bind]");
    glDeleteTextures(1, &id_);
}
} // namespace glbasic
#pragma once

#include "glbasic/renderer/texture.h"
namespace glbasic
{
class OpenGLTexture2D : public Texture
{
  public:
    explicit OpenGLTexture2D(const std::string &texture_file, bool flip_on_load = true);
    OpenGLTexture2D(int32_t width, int32_t height, int32_t channels);
    OpenGLTexture2D() = delete;
    ~OpenGLTexture2D() override;

    void Bind(uint32_t tex_unit_slot) const override;
    void UnBind() const override;

  private:
    void loadTextureFromFile(const std::string &texture_file, bool flip_on_load = true);
    void initialize();

  private:
    uint32_t id_{};
    int32_t width_ = -1;
    int32_t height_ = -1;
    int32_t num_channels_ = -1;
};

} // namespace glbasic

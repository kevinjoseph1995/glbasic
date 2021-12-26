#pragma once
#include <memory>
#include <string>

namespace glbasic
{

class Texture
{
  public:
    virtual void Bind(uint32_t tex_unit_slot) const = 0;
    virtual void UnBind() const = 0;
    virtual ~Texture() = default;
    static std::shared_ptr<Texture> Create(const std::string &texture_file, bool flip_on_load = true);
};

} // namespace glbasic
#pragma once

#include "glbasic/gl_debug.h"

#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

namespace glbasic
{

enum class ShaderDataType
{
    None = 0,
    Float,
    Float2,
    Float3,
    Float4,
    Mat3,
    Mat4,
    Int,
    Int2,
    Int3,
    Int4,
    Bool
};

static constexpr uint32_t ShaderDataTypeSize(ShaderDataType type)
{
    switch (type)
    {
    case ShaderDataType::Float:
        return 4;
    case ShaderDataType::Float2:
        return 4 * 2;
    case ShaderDataType::Float3:
        return 4 * 3;
    case ShaderDataType::Float4:
        return 4 * 4;
    case ShaderDataType::Mat3:
        return 4 * 3 * 3;
    case ShaderDataType::Mat4:
        return 4 * 4 * 4;
    case ShaderDataType::Int:
        return 4;
    case ShaderDataType::Int2:
        return 4 * 2;
    case ShaderDataType::Int3:
        return 4 * 3;
    case ShaderDataType::Int4:
        return 4 * 4;
    case ShaderDataType::Bool:
        return 1;
    case ShaderDataType::None:
        GL_ASSERT(false, "Invalid ShaderDataTypeSize");
    }

    GL_ASSERT(false, "Invalid ShaderDataTypeSize");
    return 0;
}

struct BufferElement
{
    std::string name;
    ShaderDataType type = ShaderDataType::None;
    uint32_t size{};
    size_t offset{};
    bool normalized{};

    BufferElement() = default;

    BufferElement(ShaderDataType _type, std::string _name, bool _normalized = false)
        : name(std::move(_name)), type(_type), size(ShaderDataTypeSize(_type)), offset(0), normalized(_normalized)
    {
    }

    [[nodiscard]] uint32_t GetComponentCount() const
    {
        switch (type)
        {
        case ShaderDataType::Float:
            return 1;
        case ShaderDataType::Float2:
            return 2;
        case ShaderDataType::Float3:
            return 3;
        case ShaderDataType::Float4:
            return 4;
        case ShaderDataType::Mat3:
            return 3; // 3* float3
        case ShaderDataType::Mat4:
            return 4; // 4* float4
        case ShaderDataType::Int:
            return 1;
        case ShaderDataType::Int2:
            return 2;
        case ShaderDataType::Int3:
            return 3;
        case ShaderDataType::Int4:
            return 4;
        case ShaderDataType::Bool:
            return 1;
        case ShaderDataType::None:
            GL_ASSERT(false, "Unknown ShaderDataType!");
        }

        GL_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }
};

class BufferLayout
{
  public:
    BufferLayout() = default;

    BufferLayout(std::initializer_list<BufferElement> elements) : elements_(elements)
    {
        CalculateOffsetsAndStride();
    }

    [[nodiscard]] uint32_t GetStride() const
    {
        return stride_;
    }
    [[nodiscard]] const std::vector<BufferElement> &GetElements() const
    {
        return elements_;
    }

    std::vector<BufferElement>::iterator begin()
    {
        return elements_.begin();
    }
    std::vector<BufferElement>::iterator end()
    {
        return elements_.end();
    }
    [[nodiscard]] std::vector<BufferElement>::const_iterator begin() const
    {
        return elements_.cbegin();
    }
    [[nodiscard]] std::vector<BufferElement>::const_iterator end() const
    {
        return elements_.cend();
    }

  private:
    void CalculateOffsetsAndStride()
    {
        size_t offset = 0;
        stride_ = 0;
        for (auto &element : elements_)
        {
            element.offset = offset;
            offset += element.size;
            stride_ += element.size;
        }
    }

  private:
    std::vector<BufferElement> elements_;
    uint32_t stride_ = 0;
};

class VertexBuffer
{
  public:
    virtual ~VertexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void SetData(const float *data, uint32_t size) const = 0;

    [[nodiscard]] virtual const BufferLayout &GetLayout() const = 0;
    virtual void SetLayout(const BufferLayout &layout) = 0;

    static std::shared_ptr<VertexBuffer> Create(uint32_t size);
    static std::shared_ptr<VertexBuffer> Create(const float *vertices, uint32_t size);
};

class IndexBuffer
{
  public:
    virtual ~IndexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    [[nodiscard]] virtual int32_t GetCount() const = 0;

    static std::shared_ptr<IndexBuffer> Create(const uint32_t *indices, int32_t count);
};
} // namespace glbasic
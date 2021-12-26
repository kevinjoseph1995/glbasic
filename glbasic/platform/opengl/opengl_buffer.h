#pragma once

#include "glbasic/renderer/buffer.h"
#include <cstdint>

namespace glbasic
{

class OpenGLVertexBuffer : public VertexBuffer
{
  public:
    explicit OpenGLVertexBuffer(uint32_t size);
    OpenGLVertexBuffer(const float *vertices, uint32_t size);
    ~OpenGLVertexBuffer() override;

  public:
    void Bind() const override;
    void Unbind() const override;

    void SetData(const float *data, uint32_t size) const override;

    [[nodiscard]] const BufferLayout &GetLayout() const override;
    void SetLayout(const BufferLayout &layout) override;

  private:
    uint32_t id_ = 0;
    glbasic::BufferLayout layout_;
};

class OpenGLIndexBuffer : public IndexBuffer
{
  public:
    OpenGLIndexBuffer(const uint32_t *indices, int32_t count);
    ~OpenGLIndexBuffer() override;

  public:
    void Bind() const override;
    void Unbind() const override;

    [[nodiscard]] int32_t GetCount() const override;

  private:
    int32_t count_ = 0;
    uint32_t id_ = 0;
};
} // namespace glbasic
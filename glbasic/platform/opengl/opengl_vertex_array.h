#pragma once
#include "glbasic/renderer/vertex_array.h"

namespace glbasic
{
class OpenGLVertexArray : public VertexArray
{
  public:
    OpenGLVertexArray();
    ~OpenGLVertexArray() override;

    void Bind() const override;
    void Unbind() const override;

    void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) override;
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) override;

    [[nodiscard]] const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const override
    {
        return vertex_buffers_;
    }
    [[nodiscard]] const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const override
    {
        return index_buffer_;
    }

  private:
    uint32_t id_{};
    std::vector<std::shared_ptr<VertexBuffer>> vertex_buffers_;
    std::shared_ptr<IndexBuffer> index_buffer_;
};

} // namespace glbasic

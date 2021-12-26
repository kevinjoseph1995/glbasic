#pragma once
#include "glbasic/layer.h"

#include <memory>
#include <vector>

namespace glbasic
{
class LayerStack
{
  public:
    void PushLayer(std::unique_ptr<Layer> &&layer);
    std::vector<std::unique_ptr<Layer>>::iterator begin()
    {
        return layer_stack_internal_.begin();
    }

    std::vector<std::unique_ptr<Layer>>::iterator end()
    {
        return layer_stack_internal_.end();
    }
    std::vector<std::unique_ptr<Layer>>::const_iterator cbegin()
    {
        return layer_stack_internal_.cbegin();
    }

    std::vector<std::unique_ptr<Layer>>::const_iterator cend()
    {
        return layer_stack_internal_.cend();
    }

  private:
    std::vector<std::unique_ptr<Layer>> layer_stack_internal_;
};
} // namespace glbasic
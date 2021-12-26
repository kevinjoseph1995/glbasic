//
// Created by kevin on 7/6/21.
//

#include "layer_stack.h"
namespace glbasic
{

void LayerStack::PushLayer(std::unique_ptr<Layer> &&layer)
{
    layer->OnAttach();
    layer_stack_internal_.emplace_back(std::move(layer));
}
} // namespace glbasic

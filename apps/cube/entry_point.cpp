//
// Created by kevin on 8/6/21.
//
#include "cube.hpp"

int main()
{

    std::unique_ptr<CubeDemo> app = std::make_unique<CubeDemo>();
    app->Initialize("CubeDemo", 1920, 1080);
    app->Run();
}
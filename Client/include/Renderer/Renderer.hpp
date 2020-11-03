//
// Created by arzeo on 11/2/2020.
//

#ifndef BABEL_RENDERER_HPP
#define BABEL_RENDERER_HPP

#include <queue>
#include <Client/include/RenderTarget/ARenderTarget.hpp>

class Renderer
{
    public:
    Renderer();
    void draw(ARenderTarget &target);
    void clear(ARenderTarget &target);

    private:
    std::queue<ARenderTarget> targetList;
};

#endif //BABEL_RENDERER_HPP

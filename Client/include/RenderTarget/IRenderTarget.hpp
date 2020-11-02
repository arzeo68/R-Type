//
// Created by arzeo on 10/31/2020.
//

#ifndef BABEL_IRENDERTARGET_HPP
#define BABEL_IRENDERTARGET_HPP

#include <Client/include/typeEncapsulation.hpp>

class IRenderTarget
{
    public:
    virtual ~IRenderTarget() = default;
    virtual void draw() = 0;
    virtual void present() = 0;
    virtual void clear(Rtype::color) = 0;
    virtual Rtype::vec2i getSize() const = 0;
};

#endif //BABEL_IRENDERTARGET_HPP

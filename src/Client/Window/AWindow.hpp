//
// Created by alexis on 10/27/2020.
//

#ifndef BABEL_AWINDOW_HPP
#define BABEL_AWINDOW_HPP

#include "IWindow.hpp"

namespace Rtype
{

    /**
     * window abstraction
     */
    class AWindow : public IWindow
    {
        public:
        int getWidth() const override;

        int getHeight() const override;

        private:
        int _width;
        int _height;
    };
}
#endif //BABEL_AWINDOW_HPP

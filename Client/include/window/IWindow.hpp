//
// Created by alexis on 10/27/2020.
//

#ifndef BABEL_IWINDOW_HPP
#define BABEL_IWINDOW_HPP

/**
 * window interface
 */
class IWindow
{
    public:
    virtual ~IWindow() = default;
    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual bool isOpen() const = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
};

#endif //BABEL_IWINDOW_HPP

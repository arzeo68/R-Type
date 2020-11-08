#pragma once

#include <memory>
#include <Client/include/window/IWindow.hpp>

namespace Rtype
{

class Application {
public:
    Application();
    ~Application() = default;

private:
    std::unique_ptr<IWindow> m_Window;
};

} // namespace Rtype
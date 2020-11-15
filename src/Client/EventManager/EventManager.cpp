#include <Client/EventManager/EventManager.hpp>
#include <Client/EventManager/SFMLEvents.hpp>

namespace Rtype
{

void EventManager::update()
{
    sf::Event event;
    while (m_Window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:             {
                std::shared_ptr<EventKeyPressed> key = std::make_shared<EventKeyPressed>(event.key.code);
                m_Subject.notify(EKeyPressed, key);
                break;
            }
            case sf::Event::KeyReleased:            { break; }
            case sf::Event::Closed:                 {
                std::shared_ptr<EventClose> close = std::make_shared<EventClose>();
                m_Subject.notify(EClose, close);
                break;
            }
            case sf::Event::Resized:                {
                std::shared_ptr<EventResized> resized = std::make_shared<EventResized>(event.size.width, event.size.height);
                m_Subject.notify(EResize, resized);
                break;
            }
            case sf::Event::LostFocus:              {
                std::shared_ptr<EventFocus> focus = std::make_shared<EventFocus>(false);
                m_Subject.notify(ELostFocus, focus);
                break;
            }
            case sf::Event::GainedFocus:            {
                std::shared_ptr<EventFocus> focus = std::make_shared<EventFocus>(true);
                m_Subject.notify(EGainedFocus, focus);
                break;
            }
            case sf::Event::TextEntered:            {
                std::shared_ptr<EventText> text = std::make_shared<EventText>(event.text.unicode);
                m_Subject.notify(ETextEntered, text);
                break;
            }
            case sf::Event::MouseWheelScrolled:     {
                std::shared_ptr<EventMouseWheel> wheel = std::make_shared<EventMouseWheel>(event.mouseWheelScroll.delta, event.mouseWheelScroll.x, event.mouseWheelScroll.y);
                m_Subject.notify(EMouseWheelScrool, wheel);
                break;
            }
            case sf::Event::MouseButtonPressed:     {
                std::shared_ptr<EventMouseButton> button = std::make_shared<EventMouseButton>(EventMouseButton::PRESSED, event.mouseButton.button, event.mouseButton.x, event.mouseButton.y);
                m_Subject.notify(EMouseButtonPressed, button);
                break;
            }
            case sf::Event::MouseButtonReleased:    {
                std::shared_ptr<EventMouseButton> button = std::make_shared<EventMouseButton>(EventMouseButton::RELEASED, event.mouseButton.button, event.mouseButton.x, event.mouseButton.y);
                m_Subject.notify(EMouseButtonReleased, button);
                break;
            }
            case sf::Event::MouseMoved:             {
                std::shared_ptr<EventMouseMove> move = std::make_shared<EventMouseMove>(event.mouseMove.x, event.mouseMove.y);
                m_Subject.notify(EMouseMoved, move);
                break;
            }
        }
    }
}

} // namespace Rtype

#ifndef BUTTON
#define BUTTON

#include <SFML/Graphics.hpp>
#include "core/visualize/interfaces/IDrawable.hh"
#include "ui/components/interfaces/IEventable.hh"
#include "ui/components/abstract/APositionable.hh"
#include "ui/components/abstract/ACallbackable.hh"
#include "ui/components/abstract/AFillColor.hh"
#include "ui/components/abstract/ATextable.hh"
#include "ui/components/abstract/ABorderable.hh"

class Button
    : public IDrawable
    , public IEventable
    , public APositionable
    , public ACallbackable
    , public AFillColor
    , public ATextable
    , public ABorderable
{

  public:
    Button(
        // APositionable
        const sf::Vector2f& position
        , const sf::Vector2f& size
        // AFillColor
        , sf::Color colorFill = sf::Color(200, 200, 200)
        , sf::Color colorFillOnHover = sf::Color(150, 150, 150)
        // ATextable
        , unsigned int fontSize = 20.f
        , const std::string& str = "Text"
        , sf::Color colorText = sf::Color::Black
        // ABorderable
        , sf::Color colorBorder = sf::Color::Black
        , float borderThickness = 2.f
    )
        : APositionable(position, size)
        , AFillColor(colorFill, colorFillOnHover)
        , ATextable(fontSize, str, colorText)
        , ABorderable(colorBorder, borderThickness)
    {}

    void Draw(sf::RenderTarget& target,
              const sf::Vector2f& transform = {0, 0},
              const size_t segments = 100) override
    {
        sf::Vector2f globalPos = position + transform;
        sf::RectangleShape rect(size);
        rect.setPosition(globalPos);
        rect.setFillColor(isActive && isMouseHovered(target) ? colorFill : colorFillOnHover);
        rect.setOutlineColor(colorBorder);
        rect.setOutlineThickness(borderThickness);
        target.draw(rect);

        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition({position.x + (size.x - textBounds.size.x) / 2.f,
                         position.y + (size.y - textBounds.size.y) / 2.f});
        target.draw(text);
    }

    void HandleEvent(sf::RenderTarget& target, const sf::Event& event) override {
        sf::Vector2f mousePos = target.mapPixelToCoords(sf::Mouse::getPosition());
        bool isHovered = isPointInside(mousePos);
        if (event.is<sf::Event::MouseButtonPressed>()) {
            const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>();

            if (mouse && mouse->button == sf::Mouse::Button::Left
                && isMouseHovered(target)) {
                this->invokeClick();
            }
        }
    }
};

#endif // BUTTON

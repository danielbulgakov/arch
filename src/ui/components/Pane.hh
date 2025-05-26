#ifndef PANEL
#define PANEL

#include <SFML/Graphics.hpp>
#include "core/containers/ObjectPool.hh"
#include "core/visualize/interfaces/IDrawable.hh"
#include "ui/components/abstract/APositionable.hh"
#include "ui/components/abstract/ABorderable.hh"
#include "ui/components/abstract/ATextable.hh"

class Pane
    : public ObjectPool
    , public IDrawable
    , public APositionable
    , public ABorderable
    , public ATextable
{
  public:
    Pane(const sf::Vector2f& position = {0.f, 0.f}
        , const sf::Vector2f& size = {0.f, 0.f}
        , const sf::Color& colorBorder = sf::Color::White
        , float borderThickness = 2.f
        // ATextable
        , unsigned int fontSize = 13.f
        , const std::string& str = ""
        , sf::Color colorText = sf::Color::White
    ) 
        : APositionable(position, size)
        , ABorderable(colorBorder, borderThickness)
        , ATextable(fontSize, str, colorText)
    {}

    void Draw(sf::RenderTarget& target,
              const sf::Vector2f& transform = {0, 0},
              const size_t segments = 100) override
    {
        sf::Vector2f globalTransform = transform + position;

        // Draw rect around pane
        sf::RectangleShape rect(size);
        rect.setPosition(globalTransform);
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(colorBorder);
        rect.setOutlineThickness(borderThickness);
        text.setPosition({getPosition().x + 5.0f, getPosition().y + 5.0f});

        target.draw(rect);
        target.draw(text);

        for (auto& [id, pd] : pool) {
            if (pd) {
                pd->Draw(target, globalTransform, segments);
            }
        }
    }
};

#endif // PANEL

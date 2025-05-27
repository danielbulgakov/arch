#ifndef CIRCLE
#define CIRCLE

#include <cmath>
#include "core/render/context/SfmlRenderContext.hh"
#include "core/visualize/interfaces/IDrawable.hh"
#include "ui/components/interfaces/IEventable.hh"
#include "ui/components/abstract/APositionable.hh"
#include "ui/components/abstract/AFillColor.hh"
#include "ui/components/abstract/ACallbackable.hh"
#include "ui/components/abstract/ABorderable.hh"

class Circle
    : public IDrawable
    , public IEventable
    , public APositionable
    , public AFillColor
    , public ACallbackable
    , public ABorderable
{
    sf::Color colorFillDefault;
  public:
    Circle(
        // APositionable
        const sf::Vector2f& position
        , const sf::Vector2f& size
        // AFillColor
        , sf::Color colorFill = sf::Color::White
        // ABorderable
        , sf::Color colorBorder = sf::Color::Black
        , float borderThickness = 2.f
    )
        : APositionable(position, size)
        , AFillColor(colorFill)
        , ABorderable(colorBorder, borderThickness)
    {
        colorFillDefault = colorFill;

        setOnHover([this]() {
            if (!isDragging) setColorFill(colorFillOnHover);
        });

        setOnClick([this]() {
            drag();
            setColorFill(colorFillOnDrag);
        });

        setOnRelease([this, colorFill]() {
            dragEnd();
            setColorFill(colorFill);
        });
    }

    bool isPointInside(sf::Vector2f point) const override {
        return std::hypot(point.x - (position.x + size.x), point.y - (position.y + size.y)) <= std::max(size.x, size.y);
    }

    void Draw(IRenderContext& ctx,
              const sf::Vector2f& transform = {0, 0},
              const size_t segments = 100) override
    {
        auto& sfmlCtx = reinterpret_cast<SfmlRenderContext&>(ctx);
        sf::CircleShape circle(std::max(size.x, size.y));
        sf::Vector2f globalPos = position + transform;
        circle.setPosition(globalPos);
        circle.setFillColor(colorFill);
        circle.setOutlineColor(colorBorder);
        circle.setOutlineThickness(borderThickness);

        sfmlCtx.draw(circle);
    }

    void HandleEvent(sf::RenderTarget& target, const sf::Event& event) override {
        sf::Vector2f mousePos = target.mapPixelToCoords(sf::Mouse::getPosition());
        bool isHovered = isPointInside(mousePos);
        if (isMouseHovered(target)) {
            this->invokeHover();
        } else {
            setColorFill(colorFillDefault);
        }
        if (event.is<sf::Event::MouseButtonPressed>()) {
            const auto* mouse = event.getIf<sf::Event::MouseButtonPressed>();

            if (mouse && mouse->button == sf::Mouse::Button::Left
                && isMouseHovered(target)) {
                this->invokeClick();
            }
        }
    }
};

#endif // CIRCLE

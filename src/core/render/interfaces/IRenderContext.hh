#ifndef IRENDERCONTEXT
#define IRENDERCONTEXT

#include <SFML/Graphics.hpp>

class IRenderContext
{
  public:
    virtual ~IRenderContext() = default;

    virtual void drawLine(const sf::Vector2f& from, const sf::Vector2f& to,
                          const sf::Color& color, float thickness = 1.0f,
                          bool dashed = false) = 0;

    virtual void drawCircle(const sf::Vector2f& center, float radius,
                            const sf::Color& color) = 0;

    virtual void drawSquare(const sf::Vector2f& center, float size,
                            const sf::Color& color) = 0;

    virtual void drawArrow(const sf::Vector2f& tip,
                           const sf::Color& color) = 0;

    virtual void draw(const sf::Drawable& drawable) {}
};

#endif // IRENDERCONTEXT

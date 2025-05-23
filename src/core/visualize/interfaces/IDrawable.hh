#ifndef IDRAWABLE
#define IDRAWABLE

#include <SFML/Graphics.hpp>

class IDrawable
{
  public:
    virtual ~IDrawable() = default;
    virtual void Draw(sf::RenderTarget& target,                 \
                      const sf::Vector2f& transform = {0,0},    \
                      const size_t segments         = 100) = 0; \
};

#endif  // IDRAWABLE

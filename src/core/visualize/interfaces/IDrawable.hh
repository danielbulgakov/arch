#ifndef IDRAWABLE
#define IDRAWABLE

#include <SFML/Graphics.hpp>
#include "core/render/interfaces/IRenderContext.hh"

class IDrawable
{
  public:
    virtual ~IDrawable() = default;
    virtual void Draw(IRenderContext& ctx
                    , const sf::Vector2f& transform = {0,0}
                    , const size_t segments = 100
    ) = 0;
};

#endif  // IDRAWABLE

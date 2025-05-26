#ifndef ICURVERENDERER
#define ICURVERENDERER

#include <SFML/Graphics.hpp>
#include "IRenderContext.hh"

class ICurveRenderer
{
  public:
    virtual ~ICurveRenderer() = default;

    virtual void drawSegment(IRenderContext& ctx
                           , const sf::Vector2f& a
                           , const sf::Vector2f& b) = 0;
    virtual void drawStartPoint(IRenderContext& ctx, const sf::Vector2f& point) = 0;
    virtual void drawEndPoint(IRenderContext& ctx, const sf::Vector2f& point) = 0;
};

#endif // ICURVERENDERER

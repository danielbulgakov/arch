#ifndef GREENSCHEMERENDERER
#define GREENSCHEMERENDERER

#include <SFML/Graphics.hpp>
#include "core/render/interfaces/ICurveRenderer.hh"
#include "core/render/interfaces/IRenderContext.hh"

class GreenSchemeRenderer
    : public ICurveRenderer
{
  public:
    void drawSegment(IRenderContext& ctx, const sf::Vector2f& a, const sf::Vector2f& b) override {
        ctx.drawLine(a, b, sf::Color::Green, 1.5f, false);
    }

    void drawStartPoint(IRenderContext& ctx, const sf::Vector2f& p) override {
        ctx.drawCircle(p, 4.0f, sf::Color::Green);
    }

    void drawEndPoint(IRenderContext& ctx, const sf::Vector2f& p) override {
        ctx.drawArrow(p, sf::Color::Green);
    }
};

#endif // GREENSCHEMERENDERER

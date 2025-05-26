#ifndef DASHEDBLACKRENDERER
#define DASHEDBLACKRENDERER

#include <SFML/Graphics.hpp>
#include <cmath>
#include "core/render/interfaces/ICurveRenderer.hh"

class DashedBlackRenderer
    : public ICurveRenderer
{
  public:
    void drawSegment(IRenderContext& ctx, const sf::Vector2f& a, const sf::Vector2f& b) override {
        ctx.drawLine(a, b, sf::Color::Black, 1.0f, true);
    }

    void drawStartPoint(IRenderContext& ctx, const sf::Vector2f& p) override {
        ctx.drawSquare(p, 6.0f, sf::Color::Black);
    }

    void drawEndPoint(IRenderContext& ctx, const sf::Vector2f& p) override {
        ctx.drawSquare(p, 6.0f, sf::Color::Black);
    }
};

#endif // DASHEDBLACKRENDERER

#ifndef VISUALCURVE
#define VISUALCURVE

#include "core/visualize/interfaces/IDrawable.hh"
#include "core/objects/abstracts/ACurve.hh"

class VisualCurve
    : public IDrawable
    , public ICurve
{
  protected:
    std::unique_ptr<ACurve> curve;
    sf::Color color;
    size_t preferred_seg_num = 100;

  public:
    VisualCurve(std::unique_ptr<ACurve> curve, sf::Color color = sf::Color::White)
        : curve(std::move(curve)), color(color)
    {
    }

    std::unique_ptr<IPoint> getPoint(double t) { return curve->getPoint(t); }

    void Draw(sf::RenderTarget& target,                             \
              const sf::Vector2f& transform = {0,0},                \
              const size_t segments         = 100                   \
            ) override
    {
        sf::VertexArray vertices(sf::PrimitiveType::LineStrip, segments + 1);

        for (int i = 0; i <= segments; ++i) {
            double t = static_cast<double>(i) / segments;
            auto p = getPoint(t);
            vertices[i].position = sf::Vector2f(p->getX() + transform.x,
                                                p->getY() + transform.y);
            vertices[i].color = color;
        }

        target.draw(vertices);
    }
};

#endif  // VISUALCURVE

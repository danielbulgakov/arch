#ifndef VISUALCURVE
#define VISUALCURVE

#include "core/visualize/interfaces/IDrawable.hh"
#include "core/objects/abstracts/ACurve.hh"
#include "core/render/interfaces/ICurveRenderer.hh"

class VisualCurve
    : public IDrawable
    , public ICurve
{
  protected:
    std::unique_ptr<ACurve> curve;
    std::shared_ptr<ICurveRenderer> renderer;
    sf::Color color;
    size_t preferred_seg_num = 100;

  public:
    VisualCurve(std::unique_ptr<ACurve> curve
              , std::shared_ptr<ICurveRenderer> renderer
              , sf::Color color = sf::Color::Black
    )
        : curve(std::move(curve))
        , renderer(std::move(renderer))
        , color(color)
    {
    }

    void setRenderer(std::shared_ptr<ICurveRenderer> newRenderer) {
        renderer = std::move(newRenderer);
    }

    std::unique_ptr<IPoint> getPoint(double t) { return curve->getPoint(t); }

    void Draw(IRenderContext& ctx
            , const sf::Vector2f& transform = {0,0}
            , const size_t segments = 100
    ) override
    {
        std::vector<sf::Vector2f> points;
        for (size_t i = 0; i <= segments; ++i) {
            double t = static_cast<double>(i) / segments;
            auto p = getPoint(t);
            points.emplace_back(p->getX() + transform.x, p->getY() + transform.y);
        }

        for (size_t i = 0; i < segments; ++i) {
            renderer->drawSegment(ctx, points[i], points[i + 1]);
        }

        renderer->drawStartPoint(ctx, points.front());
        renderer->drawEndPoint(ctx, points.back());
    }
};

#endif  // VISUALCURVE

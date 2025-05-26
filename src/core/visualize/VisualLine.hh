#ifndef VISUALLINE
#define VISUALLINE

#include "abstracts/VisualCurve.hh"
#include "core/objects/lines/Line.hh"

class VisualLine : public VisualCurve {
  public:
    VisualLine(const IPoint& a, const IPoint& b
             , std::shared_ptr<ICurveRenderer> renderer
             , sf::Color color = sf::Color::Green
    )
        : VisualCurve(std::make_unique<Line>(a, b), renderer, color) 
    {}

    VisualLine(std::unique_ptr<Line> line
              , std::shared_ptr<ICurveRenderer> renderer
              , sf::Color color = sf::Color::Green
    )
        : VisualCurve(std::move(line), renderer, color) 
    {}

    void Draw(IRenderContext& ctx
            , const sf::Vector2f& transform = {0,0}
            , const size_t segments = 1
    ) override
    {
        VisualCurve::Draw(ctx, transform, segments);
    }
};

#endif // VISUALLINE

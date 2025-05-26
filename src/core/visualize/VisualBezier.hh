#ifndef VISUALBEZIER
#define VISUALBEZIER

#include "abstracts/VisualCurve.hh"
#include "core/objects/lines/Bezier.hh"

class VisualBezier : public VisualCurve {
  public:
    VisualBezier(const IPoint& a, const IPoint& b,
                const IPoint& c, const IPoint& d
              , std::shared_ptr<ICurveRenderer> renderer
              , sf::Color color = sf::Color::Cyan
    )
        : VisualCurve(std::make_unique<Bezier>(a, b, c, d), renderer, color) 
    {}

    VisualBezier(std::unique_ptr<Bezier> bezier
              , std::shared_ptr<ICurveRenderer> renderer
              , sf::Color color = sf::Color::Cyan
    )
        : VisualCurve(std::move(bezier), renderer, color) 
    {}
};


#endif // VISUALBEZIER

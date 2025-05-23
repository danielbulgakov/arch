#ifndef VISUALBEZIER
#define VISUALBEZIER

#include "abstracts/VisualCurve.hh"
#include "core/objects/lines/Bezier.hh"

class VisualBezier : public VisualCurve {
public:
    VisualBezier(const IPoint& a, const IPoint& b,
                const IPoint& c, const IPoint& d,
                sf::Color color = sf::Color::Cyan)
        : VisualCurve(std::make_unique<Bezier>(a, b, c, d), color) {}
};


#endif // VISUALBEZIER

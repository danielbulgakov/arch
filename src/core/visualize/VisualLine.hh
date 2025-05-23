#ifndef VISUALLINE
#define VISUALLINE

#include "abstracts/VisualCurve.hh"
#include "core/objects/lines/Line.hh"

class VisualLine : public VisualCurve {
public:
    VisualLine(const IPoint& a, const IPoint& b, sf::Color color = sf::Color::Green)
        : VisualCurve(std::make_unique<Line>(a, b), color) {}

    void Draw(sf::RenderTarget& target,                             \
              const sf::Vector2f& transform = {0,0},                \
              const size_t segments         = 1                     \
            ) override
    {
        VisualCurve::Draw(target, transform, segments);
    }
};

#endif // VISUALLINE

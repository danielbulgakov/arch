#ifndef ICURVERENDERER
#define ICURVERENDERER

#include <SFML/Graphics.hpp>

class ICurveRenderer {
public:
    virtual ~ICurveRenderer() = default;

    virtual void drawSegment(sf::RenderTarget& target
                           , const sf::Vector2f& a
                           , const sf::Vector2f& b) = 0;
    virtual void drawStartPoint(sf::RenderTarget& target, const sf::Vector2f& point) = 0;
    virtual void drawEndPoint(sf::RenderTarget& target, const sf::Vector2f& point) = 0;
};

#endif // ICURVERENDERER

#ifndef GREENSCHEMERENDERER
#define GREENSCHEMERENDERER

#include <SFML/Graphics.hpp>
#include "interfaces/ICurveRenderer.hh"

class GreenSchemeRenderer : public ICurveRenderer {
public:
    void drawSegment(sf::RenderTarget& target
                   , const sf::Vector2f& a
                   , const sf::Vector2f& b
    ) override {
        sf::VertexArray line(sf::PrimitiveType::Lines, 2);
        line[0].position = a;
        line[0].color = sf::Color::Green;
        line[1].position = b;
        line[1].color = sf::Color::Green;
        target.draw(line);
    }

    void drawStartPoint(sf::RenderTarget& target, const sf::Vector2f& point) override {
        sf::CircleShape circle(4);
        circle.setFillColor(sf::Color::Green);
        circle.setPosition(point - sf::Vector2f(4, 4));
        target.draw(circle);
    }

    void drawEndPoint(sf::RenderTarget& target, const sf::Vector2f& point) override {
        sf::ConvexShape arrow;
        arrow.setPointCount(3);
        arrow.setPoint(0, point + sf::Vector2f(0, -6));
        arrow.setPoint(1, point + sf::Vector2f(6, 6));
        arrow.setPoint(2, point + sf::Vector2f(-6, 6));
        arrow.setFillColor(sf::Color::Green);
        target.draw(arrow);
    }
};

#endif // GREENSCHEMERENDERER

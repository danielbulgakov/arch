#ifndef DASHEDBLACKRENDERER
#define DASHEDBLACKRENDERER

#include <SFML/Graphics.hpp>
#include <cmath>
#include "interfaces/ICurveRenderer.hh"

class DashedBlackRenderer : public ICurveRenderer {
public:
    void drawSegment(sf::RenderTarget& target, const sf::Vector2f& a, const sf::Vector2f& b) override {
        const float dashLength = 5.0f;
        sf::Vector2f delta = b - a;
        float length = std::sqrt(delta.x * delta.x + delta.y * delta.y);
        sf::Vector2f unit = delta / length;

        for (float i = 0; i < length; i += 2 * dashLength) {
            sf::Vector2f start = a + unit * i;
            sf::Vector2f end = a + unit * std::min(i + dashLength, length);
            sf::VertexArray line(sf::PrimitiveType::Lines, 2);
            line[0].position = start;
            line[0].color = sf::Color::Black;
            line[1].position = end;
            line[1].color = sf::Color::Black;
            target.draw(line);
        }
    }

    void drawStartPoint(sf::RenderTarget& target, const sf::Vector2f& point) override {
        sf::RectangleShape square({6, 6});
        square.setFillColor(sf::Color::Black);
        square.setPosition(point - sf::Vector2f(3, 3));
        target.draw(square);
    }

    void drawEndPoint(sf::RenderTarget& target, const sf::Vector2f& point) override {
        sf::RectangleShape square({6, 6});
        square.setFillColor(sf::Color::Black);
        square.setPosition(point - sf::Vector2f(3, 3));
        target.draw(square);
    }
};

#endif // DASHEDBLACKRENDERER

#ifndef SFMLRENDERCONTEXT
#define SFMLRENDERCONTEXT

#include <SFML/Graphics.hpp>
#include <cmath>
#include "core/render/interfaces/IRenderContext.hh"

class SfmlRenderContext
    : public IRenderContext
{
    sf::RenderTarget& target;

  public:
    explicit SfmlRenderContext(sf::RenderTarget& target)
        : target(target) {}

    void drawLine(const sf::Vector2f& from, const sf::Vector2f& to,
                  const sf::Color& color, float thickness = 1.0f,
                  bool dashed = false) override {
        if (!dashed) {
            sf::VertexArray line(sf::PrimitiveType::Lines, 2);
            line[0].position = from;
            line[0].color = color;
            line[1].position = to;
            line[1].color = color;
            target.draw(line);
        } else {
            const float dashLength = 6.0f;
            sf::Vector2f dir = to - from;
            float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            sf::Vector2f unit = dir / length;

            for (float i = 0; i < length; i += dashLength * 2) {
                sf::Vector2f p1 = from + unit * i;
                sf::Vector2f p2 = from + unit * std::min(i + dashLength, length);

                sf::VertexArray line(sf::PrimitiveType::Lines, 2);
                line[0].position = p1;
                line[0].color = color;
                line[1].position = p2;
                line[1].color = color;
                target.draw(line);
            }
        }
    }

    void drawCircle(const sf::Vector2f& center, float radius,
                    const sf::Color& color) override {
        sf::CircleShape circle(radius);
        circle.setFillColor(color);
        circle.setOrigin({radius, radius});
        circle.setPosition(center);
        target.draw(circle);
    }

    void drawSquare(const sf::Vector2f& center, float size,
                    const sf::Color& color) override {
        sf::RectangleShape rect({size, size});
        rect.setFillColor(color);
        rect.setOrigin({size / 2.f, size / 2.f});
        rect.setPosition(center);
        target.draw(rect);
    }

    void drawArrow(const sf::Vector2f& tip, const sf::Color& color) override {
        sf::ConvexShape arrow;
        arrow.setPointCount(3);
        arrow.setPoint(0, tip);
        arrow.setPoint(1, tip + sf::Vector2f(-6.f, 10.f));
        arrow.setPoint(2, tip + sf::Vector2f(6.f, 10.f));
        arrow.setFillColor(color);
        target.draw(arrow);
    }

    void draw(const sf::Drawable& drawable) override
    {
        target.draw(drawable);
    }

    sf::RenderTarget& getTarget() { return target; }
};

#endif // SFMLRENDERCONTEXT

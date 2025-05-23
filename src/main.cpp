#include <SFML/Graphics.hpp>
#include <vector>
#include "core/visualize/abstracts/VisualCurve.hh"
#include "core/visualize/VisualBezier.hh"
#include "core/visualize/VisualLine.hh"
#include "ui/components/Button.hh"

sf::Vector2f transform(double x, double y, double width, double height) {
    return sf::Vector2f(static_cast<float>(x + width / 2.0),
                        static_cast<float>(-y + height / 2.0));
}

void
drawCustomLines(sf::RenderWindow& window)
{
    double width = window.getSize().x, height = window.getSize().y;
    auto transform = [&](double x, double y) {
        return Point(x + width/2.f, -y + height/2.f);
    };

    VisualLine line(transform(1,1), transform(width - 1, height - 1), sf::Color::Green);
    VisualBezier bezier(transform(0,0),
                        transform(-50, -50),
                        transform(-100, 50),
                        transform(0, 100),
                        sf::Color::Blue);
    VisualBezier bezier1(transform(0,0),
                        transform(50, -50),
                        transform(100, 50),
                        transform(0, 100),
                        sf::Color::Red);

    line.Draw(window);
    bezier.Draw(window);
    bezier1.Draw(window);
}

int
main()
{
    unsigned int width = 800, height = 600;
    sf::RenderWindow window(sf::VideoMode({width, height}), "Arch");

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        drawCustomLines(window);

        window.display();
        window.clear();
    }
}
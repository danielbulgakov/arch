#ifndef SVGRENDERCONTEXT
#define SVGRENDERCONTEXT

#include <fstream>
#include <string>
#include "core/render/interfaces/IRenderContext.hh"

class SvgRenderContext : public IRenderContext {
    std::ofstream out;
public:
    SvgRenderContext(const std::string& filename, float width, float height) {
        out.open(filename);
        out << "<svg xmlns='http://www.w3.org/2000/svg' width='" << width
            << "' height='" << height << "' viewBox='0 0 " << width << " " << height << "'>\n";
    }

    ~SvgRenderContext() override {
        out << "</svg>\n";
        out.close();
    }

    void drawLine(const sf::Vector2f& from, const sf::Vector2f& to,
                  const sf::Color& color, float thickness = 1.0f,
                  bool dashed = false) override {
        out << "<line x1='" << from.x << "' y1='" << from.y
            << "' x2='" << to.x << "' y2='" << to.y
            << "' stroke='" << svgColor(color) << "' stroke-width='" << thickness << "'";
        if (dashed)
            out << " stroke-dasharray='4,4'";
        out << " />\n";
    }

    void drawCircle(const sf::Vector2f& center, float radius,
                    const sf::Color& color) override {
        out << "<circle cx='" << center.x << "' cy='" << center.y
            << "' r='" << radius << "' fill='" << svgColor(color) << "' />\n";
    }

    void drawSquare(const sf::Vector2f& center, float size,
                    const sf::Color& color) override {
        float half = size / 2.0f;
        out << "<rect x='" << (center.x - half) << "' y='" << (center.y - half)
            << "' width='" << size << "' height='" << size
            << "' fill='" << svgColor(color) << "' />\n";
    }

    void drawArrow(const sf::Vector2f& tip, const sf::Color& color) override {
        sf::Vector2f left = tip + sf::Vector2f(-6, 6);
        sf::Vector2f right = tip + sf::Vector2f(6, 6);
        out << "<polygon points='" << tip.x << "," << tip.y << " "
            << left.x << "," << left.y << " "
            << right.x << "," << right.y
            << "' fill='" << svgColor(color) << "' />\n";
    }

private:
    std::string svgColor(const sf::Color& c) {
        std::ostringstream oss;
        oss << "rgb(" << static_cast<int>(c.r) << "," << static_cast<int>(c.g) << "," << static_cast<int>(c.b) << ")";
        return oss.str();
    }
};

#endif // SVGRENDERCONTEXT

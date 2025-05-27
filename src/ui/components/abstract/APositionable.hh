#ifndef APOSITIONABLE
#define APOSITIONABLE

#include <SFML/Graphics.hpp>

class APositionable
{
  protected:
    sf::Vector2f position;
    sf::Vector2f size;

  public:
    APositionable(sf::Vector2f position, sf::Vector2f size)
      : position(position), size(size)
    {}

    void setPosition(const sf::Vector2f& pos) { position = pos; }
    sf::Vector2f getPosition() const { return position; }

    void setSize(const sf::Vector2f& newSize) { size = newSize; }
    sf::Vector2f getSize() const { return size; }

    float getHeight() { return size.y; }
    float getWeight() { return size.x; }

    virtual bool isPointInside(sf::Vector2f point) const = 0;

    bool isMouseHovered(sf::RenderTarget& target) {
        const sf::Window* window = dynamic_cast<const sf::Window*>(&target);
        if (!window) {
            return false;
        }
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        return isPointInside(sf::Vector2f(mousePos.x, mousePos.y));
    }
};

#endif // APOSITIONABLE

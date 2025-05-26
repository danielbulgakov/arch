#ifndef ABORDERABLE
#define ABORDERABLE

#include <SFML/Graphics.hpp>

class ABorderable
{
  protected:
    sf::Color colorBorder;
    float borderThickness;

  public:
    ABorderable(sf::Color borderColor, float borderThickness)
      : colorBorder(borderColor), borderThickness(borderThickness)
    {}
};

#endif // ABORDERABLE

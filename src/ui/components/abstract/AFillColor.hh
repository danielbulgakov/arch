#ifndef AFILLCOLOR
#define AFILLCOLOR

#include <SFML/Graphics.hpp>

class AFillColor
{
  protected:
    sf::Color colorFill;
    sf::Color colorFillOnHover;
    sf::Color colorFillOnClick;
    sf::Color colorFillOnDrag;

  public:
    AFillColor(sf::Color colorFill = sf::Color::Transparent
             , sf::Color colorFillOnHover = sf::Color::Transparent
             , sf::Color colorFillOnClick = sf::Color::Transparent
             , sf::Color colorFillOnDrag = sf::Color::Transparent
    )
      : colorFill(colorFill)
      , colorFillOnHover(colorFillOnHover)
      , colorFillOnClick(colorFillOnClick)
      , colorFillOnDrag(colorFillOnDrag)
    {}

    inline void setColorFill(sf::Color color) { colorFill = color; }
    inline void setColorFillOnHover(sf::Color color) { colorFillOnHover = color; }
    inline void setColorFillOnClick(sf::Color color) { colorFillOnClick = color; }
    inline void setColorFillOnDrag(sf::Color color) { colorFillOnDrag = color; }
};

#endif // AFILLCOLOR

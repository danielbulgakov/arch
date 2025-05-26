#ifndef AFILLCOLOR
#define AFILLCOLOR

#include <SFML/Graphics.hpp>

class AFillColor
{
  protected:
    sf::Color colorFill;
    sf::Color colorFillOnHover;
    sf::Color colorFillOnClick;

  public:
    AFillColor(sf::Color colorFill = sf::Color::Transparent
             , sf::Color colorFillOnHover = sf::Color::Transparent
             , sf::Color colorFillOnClick = sf::Color::Transparent
    )
      : colorFill(colorFill)
      , colorFillOnHover(colorFillOnHover)
      , colorFillOnClick(colorFillOnClick)
    {}
};

#endif // AFILLCOLOR

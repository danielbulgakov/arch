#ifndef ATEXTABLE
#define ATEXTABLE

#include <SFML/Graphics.hpp>

sf::Font font(getenv("FONT_PATH"));

class ATextable
{
  protected:
    sf::Text text;

  public:
    ATextable(unsigned int fontSize
            , std::string str
            , sf::Color colorText
    )
      : text(sf::Text(font, str, fontSize))
    {
        this->text.setFillColor(colorText);
    }

    void setString(const std::string& str) {
        text.setString(str);
    }

    void setFont(sf::Font font) {
        text.setFont(font);
    }
};

#endif // ATEXTABLE

#ifndef IEVENTABLE
#define IEVENTABLE

#include <SFML/Graphics.hpp>

class IEventable
{
  public:
    virtual ~IEventable() = default;
    virtual void HandleEvent(sf::RenderTarget& target, const sf::Event& event) = 0;
};

#endif // IEVENTABLE

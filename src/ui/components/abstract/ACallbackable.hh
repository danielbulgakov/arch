#ifndef ACALLBACKABLE
#define ACALLBACKABLE

#include <functional>

class ACallbackable
{
  protected:
    std::function<void()> onClick = nullptr;
    std::function<void()> onHover = nullptr;
    std::function<void()> onRelease = nullptr;
    bool isActive = false;

  public:
    virtual ~ACallbackable() = default;

    virtual void setOnClick(std::function<void()> cb) { onClick = std::move(cb); }
    virtual void setOnHover(std::function<void()> cb) { onHover = std::move(cb); }
    virtual void setOnRelease(std::function<void()> cb) { onRelease = std::move(cb); }
    virtual void activate()     { isActive = true; }
    virtual void deactivate()   { isActive = false; }

  protected:
    void invokeClick()    { if (onClick)    onClick(); }
    void invokeHover()    { if (onHover)    onHover(); }
    void invokeRelease()  { if (onRelease)  onRelease(); }
};

#endif // ACALLBACKABLE

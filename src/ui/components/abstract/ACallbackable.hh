#ifndef ACALLBACKABLE
#define ACALLBACKABLE

#include <functional>

class ACallbackable
{
  protected:
    std::function<void()> onClick = nullptr;
    std::function<void()> onHover = nullptr;
    std::function<void()> onRelease = nullptr;
    std::function<void()> onDrag = nullptr;
    bool isActive = false;
    bool isDragging = false;

  public:
    virtual ~ACallbackable() = default;

    virtual void setOnClick(std::function<void()> cb) { onClick = std::move(cb); }
    virtual void setOnHover(std::function<void()> cb) { onHover = std::move(cb); }
    virtual void setOnRelease(std::function<void()> cb) { onRelease = std::move(cb); }
    virtual void setOnDrag(std::function<void()> cb) { onDrag = std::move(cb); }
    virtual void activate()     { isActive = true; }
    virtual void deactivate()   { isActive = false; }
    virtual void drag()         { isDragging = true; }
    virtual void dragEnd()      { isDragging = false; }

  protected:
    void invokeClick()    { if (onClick)    onClick(); }
    void invokeHover()    { if (onHover)    onHover(); }
    void invokeRelease()  { if (onRelease)  onRelease(); }
    void invokeDrag()     { if (onDrag)     onDrag(); }
};

#endif // ACALLBACKABLE

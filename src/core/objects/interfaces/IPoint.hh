#ifndef IPOINT
#define IPOINT

#include <memory>

class IPoint
{
  public:
    virtual ~IPoint() = default;

    virtual inline void setX(double x) = 0;
    virtual inline void setY(double y) = 0;
    virtual inline double getX() const = 0;
    virtual inline double getY() const = 0;

    virtual std::unique_ptr<IPoint> clone() const = 0;
};

#endif // IPOINT

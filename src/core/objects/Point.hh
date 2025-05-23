#ifndef POINT
#define POINT

#include "core/objects/interfaces/IPoint.hh"

class Point : public IPoint
{
    double x, y;

  public:
    Point(double x, double y) : x(x), y(y) {}

    inline void setX(double x) override { this->x = x; }
    inline void setY(double y) override { this->y = y; }
    inline double getX() const override { return x; }
    inline double getY() const override { return y; }

    std::unique_ptr<IPoint> clone() const override { return std::make_unique<Point>(x, y); }
};

#endif // POINT

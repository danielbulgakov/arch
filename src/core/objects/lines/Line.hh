#ifndef LINE
#define LINE

#include <algorithm>
#include "core/objects/abstracts/ACurve.hh"
#include "core/objects/Point.hh"

class Line : public ACurve
{
  protected:
    double lineFunc(double t, double a, double b) { return (1 - t) * a + t * b; }

  public:
    Line(const IPoint& a, const IPoint& b) : ACurve(a, b) {}

    Line(const Line& other)
        : ACurve(*other.a, *other.b)
    {}

    std::unique_ptr<IPoint> getPoint(double t) override
    {
        t = std::clamp(t, 0.0, 1.0);

        double x = lineFunc(t, a->getX(), b->getX());
        double y = lineFunc(t, a->getY(), b->getY());

        return std::make_unique<Point>(x, y);
    }

    std::unique_ptr<ICurve> clone() const {
        return std::make_unique<Line>(*this);
    }
};

#endif // LINE
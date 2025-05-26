#ifndef BEZIER
#define BEZIER

#include <algorithm>
#include <math.h>
#include "core/objects/abstracts/ACurve.hh"
#include "core/objects/Point.hh"

class Bezier : public ACurve
{
  protected:
    std::unique_ptr<IPoint> c, d;

    double bezierFunc(double t, double a, double b, double c, double d)
    {
        return pow(1 - t, 3) * a +            \
               3 * t * pow(1 - t, 2) * c +    \
               3 * pow(t, 2) * (1 - t) * d +  \
               pow(t, 3) * b;
    }

  public:
    Bezier(const IPoint& a, const IPoint& b, const IPoint& c, const IPoint& d)
        : ACurve(a, b), c(c.clone()), d(d.clone())
    {
    }

    Bezier(const Bezier& other)
        : ACurve(*other.a, *other.b)
        , c(other.c->clone())
        , d(other.d->clone()) {}

    std::unique_ptr<IPoint> getPoint(double t) override
    {
        t = std::clamp(t, 0.0, 1.0);

        double x = bezierFunc(t, a->getX(), b->getX(), c->getX(), d->getX());
        double y = bezierFunc(t, a->getY(), b->getY(), c->getY(), d->getY());

        return std::make_unique<Point>(x, y);
    }

    std::unique_ptr<ICurve> clone() const {
        return std::make_unique<Bezier>(*this);
    }
};

#endif // BEZIER

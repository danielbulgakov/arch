#ifndef ICURVE
#define ICURVE

#include <memory>
#include "IPoint.hh"

class ICurve
{
  public:
    virtual ~ICurve() = default;

    virtual std::unique_ptr<IPoint> getPoint(double t) = 0;
    virtual std::unique_ptr<ICurve> clone() const = 0;
};

#endif // ICURVE

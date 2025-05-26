#ifndef ACURVE
#define ACURVE

#include "core/objects/interfaces/IPoint.hh"
#include "core/objects/interfaces/ICurve.hh"

class ACurve : public ICurve
{
  protected:
    std::unique_ptr<IPoint> a, b;

  public:
    ACurve(const IPoint& a, const IPoint& b) : a(a.clone()), b(b.clone()) {}
    virtual std::unique_ptr<ICurve> clone() const = 0;
};

#endif // ACURVE

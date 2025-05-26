#ifndef FRAGMENT
#define FRAGMENT

#include "core/objects/interfaces/ICurve.hh"

class Fragment
    : public ICurve
{
  protected:
    std::unique_ptr<ICurve> base;
    double t_start, t_finish;

  public:
    Fragment(std::unique_ptr<ICurve> base, double t_start, double t_finish)
        : base(std::move(base)), t_start(t_start), t_finish(t_finish)
    {}

    std::unique_ptr<IPoint> getPoint(double t) override {
        double t_mapped = t_start + t * (t_finish - t_start);
        return base->getPoint(t_mapped)->clone();
    }

    std::unique_ptr<ICurve> clone() const override {
        return std::make_unique<Fragment>(base->clone(), t_start, t_finish);
    }
};

#endif // FRAGMENT

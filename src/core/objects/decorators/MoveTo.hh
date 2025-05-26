#ifndef MOVETO
#define MOVETO

#include <memory>
#include "core/objects/interfaces/ICurve.hh"
#include "core/objects/Point.hh"

class MoveTo
    : public ICurve
{
  protected:
    std::unique_ptr<ICurve> base;
    std::unique_ptr<IPoint> offset;

  public:
    MoveTo(std::unique_ptr<ICurve> base_curve, const IPoint& new_start_point)
        : base(std::move(base_curve))
    {
        auto current_start = base->getPoint(0.0);

        double dx = new_start_point.getX() - current_start->getX();
        double dy = new_start_point.getY() - current_start->getY();

        offset = Point(dx, dy).clone();
    }

    std::unique_ptr<IPoint> getPoint(double t) override {
        auto p = base->getPoint(t);
        return std::make_unique<Point>(p->getX() + offset->getX(),
                                       p->getY() + offset->getY());
    }

    std::unique_ptr<ICurve> clone() const override {
        return std::make_unique<MoveTo>(base->clone(), *offset);
    }
};


#endif // MOVETO

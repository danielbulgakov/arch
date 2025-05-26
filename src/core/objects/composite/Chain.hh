#ifndef CHAIN
#define CHAIN

#include <memory>
#include "core/objects/interfaces/ICurve.hh"

class Chain
    : public ICurve
{
  private:
    std::unique_ptr<ICurve> first;
    std::unique_ptr<ICurve> second;

  public:
    Chain(std::unique_ptr<ICurve> first, std::unique_ptr<ICurve> second)
        : first(std::move(first)), second(std::move(second)) {}

    std::unique_ptr<IPoint> getPoint(double t) override {
        if (t <= 0.5) {
            double localT = t / 0.5;
            return first->getPoint(localT);
        } else {
            double localT = (t - 0.5) / 0.5;
            return second->getPoint(localT);
        }
    }

    std::unique_ptr<ICurve> clone() const override {
        return std::make_unique<Chain>(first->clone(), second->clone());
    }
};

#endif // CHAIN

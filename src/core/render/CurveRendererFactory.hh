#ifndef CURVERENDERERFACTORY
#define CURVERENDERERFACTORY

#include <memory>
#include <string>
#include "GreenSchemeRenderer.hh"
#include "DashedBlackRenderer.hh"

enum class CurveRenderScheme {
    Green,
    DashedBlack
};

class CurveRendererFactory {
public:
    static std::shared_ptr<ICurveRenderer> create(CurveRenderScheme scheme) {
        switch (scheme) {
            case CurveRenderScheme::Green:
                return std::make_shared<GreenSchemeRenderer>();
            case CurveRenderScheme::DashedBlack:
                return std::make_shared<DashedBlackRenderer>();
            default:
                return std::make_shared<GreenSchemeRenderer>();
        }
    }
};

#endif // CURVERENDERERFACTORY

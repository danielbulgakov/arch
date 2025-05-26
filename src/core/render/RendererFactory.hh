#ifndef RENDERERFACTORY
#define RENDERERFACTORY

#include <memory>
#include <string>
#include "curves/GreenSchemeRenderer.hh"
#include "curves/DashedBlackRenderer.hh"

enum class CurveRenderScheme {
    Green,
    DashedBlack
};

class RendererFactory {
public:
    static std::unique_ptr<ICurveRenderer> create(CurveRenderScheme scheme) {
        switch (scheme) {
            case CurveRenderScheme::Green:
                return std::make_unique<GreenSchemeRenderer>();
            case CurveRenderScheme::DashedBlack:
                return std::make_unique<DashedBlackRenderer>();
            default:
                return std::make_unique<GreenSchemeRenderer>();
        }
    }
};

#endif // RENDERERFACTORY

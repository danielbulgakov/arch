#include <iostream>
#include "core/visualize/VisualBezier.hh"
#include "core/visualize/VisualLine.hh"
#include "core/visualize/abstracts/VisualCurve.hh"
#include "core/render/RendererFactory.hh"
#include "core/render/context/SvgRenderContext.hh"
#include "ui/components/Button.hh"
#include "ui/components/Pane.hh"
#include <SFML/Graphics.hpp>
#include <vector>

using PanePtr = std::unique_ptr<Pane>;
using PaneRawPtr = Pane*;
using PaneSharedPtr = std::shared_ptr<Pane>;

void
Pane1(PaneSharedPtr global_pane, size_t id)
{
    PaneRawPtr pane = reinterpret_cast<PaneRawPtr>(global_pane->get(id));
    pane->create<VisualLine>(
        Point(0.f, 0.f)
      , Point(pane->getWeight(), pane->getHeight())
      , RendererFactory::create(CurveRenderScheme::Green)
    );
}

void
Pane2(PaneSharedPtr global_pane, size_t id)
{
    PaneRawPtr pane = reinterpret_cast<PaneRawPtr>(global_pane->get(id));
    pane->create<VisualBezier>(
        Point(0.f, pane->getHeight())
      , Point(pane->getWeight(), 0.f)
      , Point(130.0f, -5.0f)
      , Point(-30.0f, 15.0f)
      , RendererFactory::create(CurveRenderScheme::DashedBlack)
    );
}

void
generateWindowObjects(PaneSharedPtr pane, size_t& pane1Id, size_t& pane2Id) {
    const float margin = 20.0f;
    const float width = pane->getWeight();
    const float height = pane->getHeight();
    const sf::Vector2f buttonSize{200.f, 50.f};

    // Helper function to create and configure buttons
    auto createButton = [&](const sf::Vector2f& position
                          , const std::string& label
                          , bool activated = false
    ) {
        auto id = pane->create<Button>(position, buttonSize);
        Button* button = reinterpret_cast<Button*>(pane->get(id));
        button->setString(label);
        if (activated) button->activate();
        return button;
    };

    // Create buttons
    const sf::Vector2f generateButtonPos{margin, margin};
    auto btn = createButton(generateButtonPos, "Generate", true);

    const sf::Vector2f pane1SaveButtonPos{margin, height - buttonSize.y - margin};
    auto btn1 = createButton(pane1SaveButtonPos, "Save to SVG");

    const sf::Vector2f pane2SaveButtonPos{width - buttonSize.x - margin, height - buttonSize.y - margin};
    auto btn2 = createButton(pane2SaveButtonPos, "Save to SVG");

    // Calculate common pane dimensions
    const float paneY = generateButtonPos.y + buttonSize.y + margin;
    const float paneHeight = height - paneY - buttonSize.y - 2 * margin;
    const float paneWidth = width / 2 - 2 * margin;

    // Create panes
    const sf::Vector2f pane1Pos{margin, paneY};
    pane1Id = pane->create<Pane>(
        pane1Pos
      , sf::Vector2f{paneWidth, paneHeight}
      , sf::Color::Black
      , 3.f
    );
    auto p1 = reinterpret_cast<Pane*>(pane->get(pane1Id));
    p1->setString("Visualization Scheme 1");

    const sf::Vector2f pane2Pos{paneWidth + 3 * margin, paneY};
    pane2Id = pane->create<Pane>(
        pane2Pos
      , sf::Vector2f{paneWidth, paneHeight}
      , sf::Color::Black
      , 3.f
    );
    auto p2 = reinterpret_cast<Pane*>(pane->get(pane2Id));
    p2->setString("Visualization Scheme 2");

    btn->setOnClick([pane, pane1Id, pane2Id, btn1, btn2](){
        Pane1(pane, pane1Id);
        btn1->activate();
        Pane2(pane, pane2Id);
        btn2->activate();
    });

    btn1->setOnClick([width, height, p1]() {
        SvgRenderContext svgCtx("pane1.svg", width, height);
        p1->Draw(svgCtx);
    });

    btn2->setOnClick([width, height, p2]() {
        SvgRenderContext svgCtx("pane2.svg", width, height);
        p2->Draw(svgCtx);
    });
}

int
main()
{
    unsigned int width = 1200, height = 720;
    sf::RenderWindow window(sf::VideoMode({width, height}), "Arch");
    SfmlRenderContext ctx(window);

    PaneSharedPtr pane = std::make_shared<Pane>(
        sf::Vector2f{0, 0}
      , sf::Vector2f{static_cast<float>(width), static_cast<float>(height)}
      , sf::Color::Red
      , 3.f
    );

    size_t pane1Id, pane2Id;
    generateWindowObjects(pane, pane1Id, pane2Id);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            for (auto eventable : pane->getEventables()) {
                eventable->HandleEvent(window, *event);
            }

            if (event->is<sf::Event::Closed>())
            window.close();
        }

        pane->Draw(ctx);

        window.display();
        window.clear(sf::Color::White);
    }
}
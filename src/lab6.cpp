#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include <memory>
#include <iostream>
#include <cmath>

#include "ui/components/Circle.hh"

class Command {
public:
    virtual void undo() = 0;
    virtual ~Command() {}
};

class MoveCommand : public Command {
    Circle& element;
    sf::Vector2f from, to;

public:
    MoveCommand(Circle& el, sf::Vector2f from, sf::Vector2f to)
        : element(el), from(from), to(to) {}

    void undo() override {
        element.setPosition(from);
    }
};

class InteractionController {
public:
    std::vector<Circle*> elements;
    std::stack<std::unique_ptr<Command>> history;

    Circle* hovered = nullptr;
    Circle* dragged = nullptr;
    Circle* potentialDrag = nullptr;
    sf::Clock clickClock;
    bool mouseDown = false;

    sf::Vector2f dragOffset;
    sf::Vector2f oldPos;

    const sf::Time dragThreshold = sf::milliseconds(20);

    void updateMouse(const sf::Vector2f& mousePos) {
        hovered = nullptr;
        for (auto* el : elements) {
            if (el->isPointInside(mousePos)) {
                hovered = el;
                // break;
            }
        }

        if (mouseDown && potentialDrag && !dragged) {
            if (clickClock.getElapsedTime() > dragThreshold && hovered == potentialDrag) {
                dragged = potentialDrag;
                dragOffset = dragged->getPosition() - mousePos;
                oldPos = dragged->getPosition();
                dragged->setColorFill(sf::Color::Red);
            }
        }
    }
    
    void handleMouseDown(const sf::Event::MouseButtonPressed& mouse, const sf::Vector2f& pos) {
        if (mouse.button == sf::Mouse::Button::Left && hovered) {
            potentialDrag = hovered;
            clickClock.restart();
            mouseDown = true;
        }
    }
    
    void handleMouseMove(const sf::Vector2f& pos) {
        if (dragged) {
            dragged->setPosition(pos + dragOffset);
        }
    }

    void handleMouseUp(const sf::Event::MouseButtonReleased& mouse) {
        if (mouse.button == sf::Mouse::Button::Left) {
            if (dragged && dragged->getPosition() != oldPos) {
                history.push(std::make_unique<MoveCommand>(*dragged, oldPos, dragged->getPosition()));
            }
            if (dragged) dragged->setColorFill(sf::Color::White);

            dragged = nullptr;
            potentialDrag = nullptr;
            mouseDown = false;
        }
    }

    void updateColors() {
        for (auto* el : elements) {
            if (el == dragged)
                el->setColorFill(sf::Color::Red);
            else if (el == hovered)
                el->setColorFill(sf::Color::Green);
            else
                el->setColorFill(sf::Color::White);
        }
    }

    void undo() {
        if (!history.empty()) {
            history.top()->undo();
            history.pop();
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Interactive UI");
    window.setFramerateLimit(60);

    std::vector<Circle> models = {
        Circle({100,100}, {100,100}),
        Circle({200,150}, {100,100}),
        Circle({300,150}, {100,100})
    };
    InteractionController controller;

    for (auto& el : models) {
        controller.elements.push_back(&el);
    }
    SfmlRenderContext ctx(window);
    while (window.isOpen()) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        controller.updateMouse(mousePos);

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (event->is<sf::Event::MouseButtonPressed>()) {
                const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouse)
                    controller.handleMouseDown(*mouse, mousePos);
            } else if (event->is<sf::Event::MouseButtonReleased>()) {
                const auto* mouse = event->getIf<sf::Event::MouseButtonReleased>();
                if (mouse)
                    controller.handleMouseUp(*mouse);
            } else if (event->is<sf::Event::KeyPressed>()) {
                const auto* key = event->getIf<sf::Event::KeyPressed>();
                if (key && key->code == sf::Keyboard::Key::Z && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
                    controller.undo();
                }
            }
        }

        controller.handleMouseMove(mousePos);
        controller.updateColors();

        window.clear(sf::Color::White);
        for (auto& crcl : models)
            crcl.Draw(ctx);
        window.display();
    }
    return 0;
}

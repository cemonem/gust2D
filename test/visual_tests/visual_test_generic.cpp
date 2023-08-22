#include <SFML/Graphics.hpp>
#include <gust/physics/engine2.h>
#include <apputils/apputils.h>

enum class GameMode {
    START,
    FORCE,
    DRAG
};

int main(int const argc, char const *argv[])
{
    sf::Vector2f mouseDragStart, mouseDragEnd;
    bool forceDrawing = false;
    bool firstPress = true;
    Vec2 dragOffset = Vec2(0.0f, 0.0f);
    DebugGameObject *currentShape = nullptr;
    GameMode gameMode = GameMode::START;

    sf::VertexArray line(sf::LinesStrip, 2);
    line[0].color = sf::Color::Red;
    line[1].color = sf::Color::Red;

    PhysicsEngine2 engine(Vec2(0.0f, 0.0f));
    std::vector<std::unique_ptr<DebugGameObject>> shapes = makeShapesFromTMXFile(argv[1], engine);

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_PX_X, WINDOW_SIZE_PX_Y), "Press S to start, Press F then drag to add force, Press D then drag to move");
    window.setFramerateLimit(60);
    window.clear(sf::Color::Black);
    sf::Event event;
    sf::Clock clock;
    while (window.isOpen()) {
        clock.restart();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
            switch(gameMode) {
                case GameMode::START:
                    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
                        gameMode = GameMode::FORCE;
                        forceDrawing = false;
                        currentShape = nullptr;
                        firstPress = true;
                        dragOffset = Vec2(0.0f, 0.0f);
                        break;
                    }
                    break;
                case GameMode::FORCE:
                    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D) {
                        gameMode = GameMode::DRAG;
                        forceDrawing = false;
                        currentShape = nullptr;
                        firstPress = true;
                        dragOffset = Vec2(0.0f, 0.0f);
                        break;
                    }

                    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                        if(firstPress) {
                            firstPress = false;
                            for(auto &shape : shapes) {
                                if(shape->raycast(sf::Vector2f(sf::Mouse::getPosition(window)))) {
                                    forceDrawing = true;
                                    mouseDragStart = sf::Vector2f(sf::Mouse::getPosition(window));
                                    mouseDragEnd = sf::Vector2f(sf::Mouse::getPosition(window));
                                    currentShape = shape.get();
                                    break;
                                }
                            }
                        }
                    }
                    else if(event.type == sf::Event::MouseButtonReleased  && event.mouseButton.button == sf::Mouse::Left) {
                        firstPress = true;
                        if(!currentShape) break;
                        Vec2 dragStart = toWorldCoords(mouseDragStart);
                        Vec2 dragEnd = toWorldCoords(mouseDragEnd);
                        currentShape->body.addForceAtGlobalPoint((dragEnd - dragStart)*10, dragStart);
                        currentShape = nullptr;
                        forceDrawing = false;
                    }
                    else if(event.type == sf::Event::MouseMoved) {
                        mouseDragEnd = sf::Vector2f(sf::Mouse::getPosition(window));
                    }

                    break;
                
                case GameMode::DRAG:
                    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F) {
                        gameMode = GameMode::FORCE;
                        forceDrawing = false;
                        currentShape = nullptr;
                        firstPress = true;
                        dragOffset = Vec2(0.0f, 0.0f);
                        break;
                    }

                    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                        if(firstPress) {
                            firstPress = false;
                            for(auto &shape : shapes) {
                                if(shape->raycast(sf::Vector2f(sf::Mouse::getPosition(window)))) {
                                    dragOffset = shape->body.transform.translation-toWorldCoords(sf::Vector2f(sf::Mouse::getPosition(window)));
                                    shape->body.velocity = {0.0f, 0.0f};
                                    shape->body.angularVelocity = 0.0f;
                                    currentShape = shape.get();
                                    break;
                                }
                            }
                        }
                    }
                    else if(event.type == sf::Event::MouseButtonReleased  && event.mouseButton.button == sf::Mouse::Left) {
                        firstPress = true;
                        currentShape = nullptr;
                        forceDrawing = false;
                    }
                    else if(event.type == sf::Event::MouseMoved) {
                        if(currentShape) {
                            currentShape->body.transform.translation = toWorldCoords(sf::Vector2f(sf::Mouse::getPosition(window))) + dragOffset;
                        }
                    }

                    break;
            }
        }
        window.clear(sf::Color::Black);
        for(auto const &shape : shapes) {
            shape->draw(window);
        }
        if(forceDrawing) {   
            line[0].position = mouseDragStart;
            line[1].position = mouseDragEnd;
            window.draw(line);
        }

        window.display();
        window.clear(sf::Color::Black);
        if(gameMode == GameMode::START) continue;
        engine.runPhysics(clock.getElapsedTime().asSeconds());
    }

    return 0;
}

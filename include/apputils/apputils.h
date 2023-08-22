#ifndef APPUTILS_H
#define APPUTILS_H

#include <gust/physics/engine2.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <tinyxml2.h>

using namespace gust;

extern float WINDOW_SIZE_PX_Y;
extern float WINDOW_SIZE_PX_X;
extern float PX_PER_METER;
extern float ARROWHEAD_PX_LENGTH;
extern float ARROWHEAD_ANGLE_RAD;
extern float POINT_PX_RADIUS;
extern float TFORM_AXES_PX_LENGTH;

inline sf::Vector2f toWindowCoords(const Vec2 &vec) {
    return sf::Vector2f(vec.x*PX_PER_METER, WINDOW_SIZE_PX_Y-vec.y*PX_PER_METER);
}

inline Vec2 toWorldCoords(const sf::Vector2f &vec) {
    return Vec2(vec.x/PX_PER_METER, (WINDOW_SIZE_PX_Y-vec.y)/PX_PER_METER);
}

inline void drawDebugTform(sf::RenderWindow &window, Tform2 const &tform, sf::Color const &color = sf::Color::Red) {
    sf::Vertex line[] = {
        sf::Vertex(toWindowCoords(tform.translation)),
        sf::Vertex(toWindowCoords(tform.translation + tform.getOrthogonalDirection()*TFORM_AXES_PX_LENGTH/PX_PER_METER))
    };
    for(auto &vertex : line) {
        vertex.color = sf::Color::Cyan;
    }
    window.draw(line, 2, sf::Lines);
    sf::Vertex line2[] = {
        sf::Vertex(toWindowCoords(tform.translation)),
        sf::Vertex(toWindowCoords(tform.translation + tform.getDirection()*TFORM_AXES_PX_LENGTH/PX_PER_METER))
    };
    for(auto &vertex : line2) {
        vertex.color = color;
    }
    window.draw(line2, 2, sf::Lines);
}

inline void drawDebugPositionedVector(sf::RenderWindow &window, Vec2 const &pos, Vec2 const &vec, sf::Color const &color = sf::Color::Blue) {

    sf::Vertex line[] = {
        sf::Vertex(toWindowCoords(pos)),
        sf::Vertex(toWindowCoords(pos + vec))
    };

    //draw arrowhead
    Vec2 arrowhead = (vec.normal().rotated(gust_DEG2RAD * 30.0f) * ARROWHEAD_PX_LENGTH)/PX_PER_METER;
    sf::Vertex arrowhead1[] = {
        sf::Vertex(toWindowCoords(pos + vec)),
        sf::Vertex(toWindowCoords(pos + vec - arrowhead))
    };
    arrowhead = (vec.normal().rotated(gust_DEG2RAD * -30.0f) * ARROWHEAD_PX_LENGTH)/PX_PER_METER;
    sf::Vertex arrowhead2[] = {
        sf::Vertex(toWindowCoords(pos + vec)),
        sf::Vertex(toWindowCoords(pos + vec - arrowhead))
    };

    for(auto &vertex : line) {
        vertex.color = color;
    }
    for(auto &vertex : arrowhead1) {
        vertex.color = color;
    }
    for(auto &vertex : arrowhead2) {
        vertex.color = color;
    }

    window.draw(line, 2, sf::Lines);
    window.draw(arrowhead1, 2, sf::Lines);
    window.draw(arrowhead2, 2, sf::Lines);
}

inline void drawDebugPoint(sf::RenderWindow &window, Vec2 const &pos, sf::Color const &color = sf::Color::Green) {
    sf::CircleShape point(2.0f);
    point.setOrigin(2.0f, 2.0f);
    point.setPosition(toWindowCoords(pos));
    point.setFillColor(color);
    window.draw(point);
}

class DebugGameObject {
public:
    Rigidbody2 &body;
    DebugGameObject(Rigidbody2 &body) : body(body) {}
    virtual ~DebugGameObject() = default;

    virtual void draw(sf::RenderWindow &window) = 0;
    virtual bool raycast(const sf::Vector2f &point) = 0;
};

class DebugCircleGameObject : public DebugGameObject {
private:
    sf::CircleShape sfShape;
public:
    float radius;
    DebugCircleGameObject(Rigidbody2 &body, real radius) : DebugGameObject(body), radius(radius) {
        sfShape.setRadius(radius*PX_PER_METER);
        sfShape.setOrigin(radius*PX_PER_METER, radius*PX_PER_METER);
        sfShape.setFillColor(sf::Color::Transparent);
        sfShape.setOutlineColor(sf::Color::White);
        sfShape.setOutlineThickness(1.0f);
    }

    void draw(sf::RenderWindow &window) override {
        sfShape.setPosition(toWindowCoords(body.transform.translation));
        window.draw(sfShape);

        //draw direction with line of length radius
        sf::Vertex line[] = {
            sf::Vertex(toWindowCoords(body.transform.translation)),
            sf::Vertex(toWindowCoords(body.transform.translation + body.transform.getDirection() * radius))
        };
        window.draw(line, 2, sf::Lines);
    }

    bool raycast(const sf::Vector2f &point) override {
        Vec2 gustPoint = toWorldCoords(point);
        return (gustPoint - body.transform.translation).magnitudeSquared() <= radius * radius;
    }
};

class DebugRectangleGameObject : public DebugGameObject {
private:
    sf::RectangleShape sfShape;
public:
    Vec2 halfSize;
    DebugRectangleGameObject(Rigidbody2 &body, const Vec2 &halfSize) : DebugGameObject(body), halfSize(halfSize) {
        sfShape.setSize(sf::Vector2f(halfSize.x*PX_PER_METER*2.0f, halfSize.y*PX_PER_METER*2.0f));
        sfShape.setOrigin(halfSize.x*PX_PER_METER, halfSize.y*PX_PER_METER);
        sfShape.setFillColor(sf::Color::Transparent);
        sfShape.setOutlineColor(sf::Color::White);
        sfShape.setOutlineThickness(1.0f);
    }

    void draw(sf::RenderWindow &window) override {
        sfShape.setPosition(toWindowCoords(body.transform.translation));
        sfShape.setRotation(-body.transform.getOrientation() * gust_RAD2DEG);

        //draw direction with line of length width/2.0f
        sf::Vertex line[] = {
            sf::Vertex(toWindowCoords(body.transform.translation)),
            sf::Vertex(toWindowCoords(body.transform.translation + body.transform.getDirection() * halfSize.x))
        };
        window.draw(line, 2, sf::Lines);
        window.draw(sfShape);
    }

    bool raycast(const sf::Vector2f &point) override {
        Vec2 gustPoint = toWorldCoords(point);
        Vec2 localPoint = body.transform.inverse() * gustPoint;
        return localPoint.x >= -halfSize.x && localPoint.x <= halfSize.x &&
               localPoint.y >= -halfSize.y && localPoint.y <= halfSize.y;
    }
};

std::vector<std::unique_ptr<DebugGameObject>> makeShapesFromTMXFile(char const *, PhysicsEngine2&);

#endif //APPUTILS_H
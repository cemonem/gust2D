#ifndef GUST_PHYSICS_COLLIDER2_H
#define GUST_PHYSICS_COLLIDER2_H

#include <gust/physics/engine2.h>
#include <gust/physics/rigidbody2.h>
#include <vector>

namespace gust {
    class Collider2;
    class CircleCollider2;
    class PolygonCollider2;
    class RectangleCollider2;
    class PhysicsEngine2;
    class PrivateToPhysicsEngine2;

    template <typename T>
    class Collider2Visitor {
    public:
        virtual T accept(Collider2 const &other, PhysicsEngine2 &engine) const = 0;
        virtual T visitCircle(CircleCollider2 const &other, PhysicsEngine2 &engine) const = 0;
        virtual T visitPolygon(PolygonCollider2 const &other, PhysicsEngine2 &engine) const = 0;
        virtual T visitRectangle(RectangleCollider2 const &other, PhysicsEngine2 &engine) const = 0;
        virtual ~Collider2Visitor() = default;
    };

    using ShapeCollisionVisitor = Collider2Visitor<void>;

    class Collider2 : public ShapeCollisionVisitor {
    public:
        Rigidbody2 &body;
        Tform2 offset;

        real friction, restitution;

        Collider2(PrivateToPhysicsEngine2 const &dummy,
                  Rigidbody2 &body,
                  Tform2 const &offset = Tform2(),
                  real friction = 0.0f,
                  real restitution = 0.0f) : body(body), 
                                             offset(offset), friction(friction), restitution(restitution) {}

        virtual bool inBounds(Vec2 const &point) const = 0;
        virtual Vec2 clamp(Vec2 const &point) const = 0;
    };

    class CircleCollider2 : public Collider2 {
    public:
        real radius;
        CircleCollider2(PrivateToPhysicsEngine2 const &dummy,
                        Rigidbody2 &body,
                        real radius,
                        Tform2 const &offset = Tform2(),
                        real friction = 0.0f,
                        real restitution = 0.0f): Collider2(dummy, body, offset, friction, restitution), 
                                                         radius(radius) {}
        
        void accept(Collider2 const &other, PhysicsEngine2 &engine) const override {
            if(this == &other || &body == &(other.body)) return;
            other.visitCircle(*this, engine);
        }

        void visitCircle(CircleCollider2 const &other, PhysicsEngine2 &engine) const override;

        void visitRectangle(RectangleCollider2 const &other, PhysicsEngine2 &engine) const override;

        void visitPolygon(PolygonCollider2 const &other, PhysicsEngine2 &engine) const override {}

        bool inBounds(Vec2 const &point) const override;

        Vec2 clamp(Vec2 const &point) const override;
    };

    class PolygonCollider2 : public Collider2 {
    public:
        std::vector<Tform2> _vertexTforms;
        PolygonCollider2(PrivateToPhysicsEngine2 const &dummy,
                         Rigidbody2 &body,
                         std::vector<Vec2> const &vertices,
                         Tform2 const &offset = Tform2(),
                         real friction = 0.0f,
                         real restitution = 0.0f): Collider2(dummy, body, offset, friction, restitution) {
            _vertexTforms.reserve(vertices.size());
            for(size_t i = 0; i < vertices.size(); ++i) {
                Vec2 normal = (vertices[(i+1)%vertices.size()] - vertices[i]).normal();
                _vertexTforms.emplace_back(vertices[i], normal);
            }
        }

        void accept(Collider2 const &other, PhysicsEngine2 &engine) const override {
            if(this == &other || &body == &(other.body)) return;
            other.visitPolygon(*this, engine);
        }

        void visitCircle(CircleCollider2 const &other, PhysicsEngine2 &engine) const override {}
        void visitRectangle(RectangleCollider2 const &other, PhysicsEngine2 &engine) const override {}
        void visitPolygon(PolygonCollider2 const &other, PhysicsEngine2 &engine) const override;

        bool inBounds(Vec2 const &point) const override {return false;}
        Vec2 clamp(Vec2 const &point) const override {return Vec2();}

        friend class CircleCollider2;
        friend class RectangleCollider2;
    };


    class RectangleCollider2 : public PolygonCollider2 {
    public:
        Vec2 _halfSize;
        RectangleCollider2(PrivateToPhysicsEngine2 const &dummy,
                           Rigidbody2 &body,
                           Vec2 const &halfSize,
                           Tform2 const &offset = Tform2(),
                           real friction = 0.0f,
                           real restitution = 0.0f): PolygonCollider2(dummy, body, 
                                                                      {Vec2(-halfSize.x, -halfSize.y),
                                                                       Vec2(halfSize.x, -halfSize.y),
                                                                       Vec2(halfSize.x, halfSize.y),
                                                                       Vec2(-halfSize.x, halfSize.y)},
                                                                      offset, friction, restitution), 
                                                                       _halfSize(halfSize) {}

        void accept(Collider2 const &other, PhysicsEngine2 &engine) const override {
            if(this == &other || &body == &(other.body)) return;
            other.visitRectangle(*this, engine);
        }

        void visitCircle(CircleCollider2 const &other, PhysicsEngine2 &engine) const override;

        void visitRectangle(RectangleCollider2 const &other, PhysicsEngine2 &engine) const override;

        void visitPolygon(PolygonCollider2 const &other, PhysicsEngine2 &engine) const override {}

        bool inBounds(Vec2 const &point) const override;

        Vec2 clamp(Vec2 const &point) const override;

        friend class CircleCollider2;
        friend class PolygonCollider2;
    };
}

#endif // GUST_PHYSICS_COLLIDER2_H

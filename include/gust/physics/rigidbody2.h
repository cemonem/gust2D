#ifndef GUST_PHYSICS_RIGIDBODY2_H
#define GUST_PHYSICS_RIGIDBODY2_H

#include <gust/core.h>
#include <gust/tform2.h>
#include <gust/vec2.h>
#include <gust/physics/engine2.h>

namespace gust {
    class PhysicsEngine2;
    class PrivateToPhysicsEngine2;

    class Rigidbody2 {
    public:
        real _inverseMass;
        real _inverseInertia;

        real _isAwake;
        real _awakeMotion;

        Vec2 _accumulatedForce;
        real _accumulatedTorque;

        void _clearAccumulatedForceAndTorque() {
            _accumulatedForce = {};
            _accumulatedTorque = 0.0f;
        }

        void _integrate(real dt);

        real linearDamping;
        real angularDamping;

        Tform2 transform;

        Vec2 velocity;
        real angularVelocity;

        Rigidbody2(const PrivateToPhysicsEngine2 &dummy,
                   const Tform2 &tform,
                   real mass,
                   real inertia,
                   const Vec2 &velocity = {0.0f, 0.0f},
                   real angularVelocity = 0.0f,
                   real linearDamping = 0.1f,
                   real angularDamping = 0.1f) : transform(tform),
                                                 _inverseMass(1.0f / mass),
                                                 _inverseInertia(1.0f / inertia),
                                                 velocity(velocity),
                                                 angularVelocity(angularVelocity),
                                                 linearDamping(linearDamping),
                                                 angularDamping(angularDamping),
                                                 _isAwake(true),
                                                 _awakeMotion(0.0f),
                                                 _accumulatedForce(Vec2()),
                                                 _accumulatedTorque(0.0) {}

        void setMass(real mass) {
            _inverseMass = 1.0f / mass;
        }

        void setMassInfinite() {
            _inverseMass = 0.0f;
        }

        bool isMassInfinite() const {
            return _inverseMass == 0.0f;
        }

        real getMass() const {
            return 1.0f / _inverseMass;
        }

        void setInertia(real inertia) {
            _inverseInertia = 1.0f / inertia;
        }

        void setInertiaInfinite() {
            _inverseInertia = 0.0f;
        }

        bool isInertiaInfinite() const {
            return _inverseInertia == 0.0f;
        }

        real getInertia() const {
            return 1.0f / _inverseInertia;
        }

        void addForce(const Vec2 &force) {
            _accumulatedForce += force;
            _isAwake = true;
        }

        void addTorque(real torque) {
            _accumulatedTorque += torque;
            _isAwake = true;
        }

        void addForceAtGlobalPoint(const Vec2 &force, const Vec2 &point) {
            addForce(force);
            addTorque((point - transform.translation).cross(force));
        }

        void addForceAtLocalPoint(const Vec2 &force, const Vec2 &point) {
            addForce(force);
            addTorque(point.cross(force));
        }

        Vec2 getVelocityAtLocalPoint(const Vec2 &point) const {
            return velocity + point.rotated90() * angularVelocity;
        }

        Vec2 getVelocityAtGlobalPoint(const Vec2 &point) const {
            return velocity + (point - transform.translation).rotated90() * angularVelocity;
        }

        friend class PhysicsEngine2;
    };    
}

#endif // GUST_PHYSICS_RIGIDBODY2_H
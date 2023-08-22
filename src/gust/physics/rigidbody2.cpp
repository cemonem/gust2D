#include <gust/physics/rigidbody2.h>

namespace gust {
    void Rigidbody2::_integrate(real dt) {
        if(_inverseMass == 0.0f) return;

        transform.translation += velocity * dt;
        transform.rotateLocal(angularVelocity * dt);

        Vec2 acceleration = _accumulatedForce * _inverseMass;
        velocity += acceleration * dt;

        real angularAcceleration = _accumulatedTorque * _inverseInertia;
        angularVelocity += angularAcceleration * dt;

        velocity *= std::pow(1.0f - linearDamping, dt);
        angularVelocity *= std::pow(1.0f - angularDamping, dt);

        _clearAccumulatedForceAndTorque();
    }
}
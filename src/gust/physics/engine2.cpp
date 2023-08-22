#include <gust/physics/engine2.h>
#include <gust/physics/rigidbody2.h>
#include <algorithm>

namespace gust {

    void PhysicsEngine2::runPhysics(real dt) {
        _clearContacts();
        for(auto& body : _bodies) {
            body.addForce(gravityField);
            body._integrate(dt);
        }
        _generateCollisionContacts();
        _resolveContacts();
}

    void PhysicsEngine2::_generateCollisionContacts() {
        for(auto it = _colliders.begin(); it != _colliders.end(); ++it) {
            for(auto jt = it; jt != _colliders.end(); ++jt) {
                if(it == jt) continue;
                (*it)->accept(**jt, *this);
            }
        }
    }

    CircleCollider2& PhysicsEngine2::createCircleCollider(Rigidbody2 &body,
                                            real radius,
                                            Tform2 const &offset,
                                            real friction,
                                            real restitution) {
        _colliders.emplace_back(std::make_unique<CircleCollider2>(PrivateToPhysicsEngine2(), 
                                                                  body, radius, offset, friction, restitution));
        return *(static_cast<CircleCollider2*>((_colliders.back().get())));
    }

    RectangleCollider2& PhysicsEngine2::createRectangleCollider(Rigidbody2 &body,
                                                Vec2 const &size,
                                                Tform2 const &offset,
                                                real friction,
                                                real restitution) {
        _colliders.emplace_back(std::make_unique<RectangleCollider2>(PrivateToPhysicsEngine2(), 
                                                                     body, size, offset, friction, restitution));
        return *(static_cast<RectangleCollider2*>((_colliders.back().get())));
    }

    template void PhysicsEngine2::deleteCollider<CircleCollider2>(CircleCollider2&);
    template void PhysicsEngine2::deleteCollider<RectangleCollider2>(RectangleCollider2&);

    static inline real _tangentialInertiaWeightPerUnitImpulse(Vec2 const& impulseDirection, Vec2 const& pointLocal, Rigidbody2 const& body) {
        Vec2 pointLocal_90 = pointLocal.rotated90();
        return body._inverseInertia*pointLocal.cross(impulseDirection)*pointLocal_90.dot(impulseDirection);
    }

    void PhysicsEngine2::_resolveContactVelocities(Contact2 &contact) {
        Rigidbody2& bodyA = contact.getBodyA();
        Rigidbody2& bodyB = contact.getBodyB();

        Vec2 const &contactNormal = contact.transform.getDirection();
        Vec2 const &contactPoint = contact.transform.translation;
        Vec2 contactPoint_WrtA = contactPoint - bodyA.transform.translation;
        Vec2 contactPoint_WrtB = contactPoint - bodyB.transform.translation;

        real closingVelocity = (bodyA.getVelocityAtLocalPoint(contactPoint_WrtA)-
                                bodyB.getVelocityAtLocalPoint(contactPoint_WrtB)).dot(contactNormal);
        
        if(closingVelocity <= gust_EPSILON) return;

        real deltaSeperatingVelocity =  closingVelocity * (1 + contact.restitution);
        real sepVelBodyAWeight = _tangentialInertiaWeightPerUnitImpulse(-contactNormal, 
                                                                         contactPoint_WrtA, bodyA) + bodyA._inverseMass;
        real sepVelBodyBWeight = _tangentialInertiaWeightPerUnitImpulse(contactNormal, 
                                                                        contactPoint_WrtB, bodyB) + bodyB._inverseMass;

        real impulseAmount = deltaSeperatingVelocity / (sepVelBodyAWeight + sepVelBodyBWeight);

        bodyA.velocity -= impulseAmount * contactNormal * bodyA._inverseMass;
        bodyA.angularVelocity -= impulseAmount * bodyA._inverseInertia * contactPoint_WrtA.cross(contactNormal);

        bodyB.velocity += impulseAmount * contactNormal * bodyB._inverseMass;
        bodyB.angularVelocity += impulseAmount * bodyB._inverseInertia * contactPoint_WrtB.cross(contactNormal);
    }

    void PhysicsEngine2::_resolveContactInterpenetrations(Contact2 &contact) {
        contact.getBodyA().transform.translation -= contact.transform.getDirection() * contact.penetration * contact.getBodyA()._inverseMass;
        contact.getBodyB().transform.translation += contact.transform.getDirection() * contact.penetration * contact.getBodyB()._inverseMass;
    }

    void PhysicsEngine2::_resolveContacts() {
        std::sort(_contacts.begin(), _contacts.end(), [](Contact2 const &a, Contact2 const &b) {
            return a.penetration > b.penetration;
        });

        for(auto &contact : _contacts) {
            _resolveContactVelocities(contact);
            _resolveContactInterpenetrations(contact);
        }
    }


}
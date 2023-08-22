#ifndef GUST_PHYSICS_CONTACT2_H
#define GUST_PHYSICS_CONTACT2_H

#include <gust/physics/engine2.h>
#include <gust/physics/rigidbody2.h>

namespace gust {
    class Rigidbody2;
    class PrivateToPhysicsEngine2;

    class Contact2 {
    private:
        Rigidbody2 *_bodyAptr;
        Rigidbody2 *_bodyBptr;

    public:

        Tform2 transform;
        real penetration;

        real restitution;
        real friction;

        Contact2(PrivateToPhysicsEngine2 const &dummy,
                 Rigidbody2 &bodyA, Rigidbody2 &bodyB, 
                 Tform2 const &transform, real penetration,
                 real restitution = 0.0f, real friction = 0.0f) : _bodyAptr(&bodyA), _bodyBptr(&bodyB), 
                                                                  transform(transform),
                                                                  penetration(penetration), 
                                                                  restitution(restitution), friction(friction) {}

        Contact2(PrivateToPhysicsEngine2 const &dummy,
                 Rigidbody2 &bodyA, Rigidbody2 &bodyB, 
                 Vec2 const &point, Vec2 const &normal, real penetration,
                 real restitution = 0.0f, real friction = 0.0f) : _bodyAptr(&bodyA), _bodyBptr(&bodyB), 
                                                                  transform(point, normal),
                                                                  penetration(penetration), 
                                                                  restitution(restitution), friction(friction) {}
        
        Rigidbody2& getBodyA() const { return *_bodyAptr; }
        Rigidbody2& getBodyB() const { return *_bodyBptr; }
            
    };
}

#endif // GUST_PHYSICS_CONTACT2_H

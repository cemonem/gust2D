#ifndef INCLUDE_GUST_PHYSICS_ENGINE2
#define INCLUDE_GUST_PHYSICS_ENGINE2

#include <gust/physics/core2.h>
#include <gust/physics/rigidbody2.h>
#include <gust/physics/contact2.h>
#include <gust/physics/collider2.h>
#include <vector>
#include <list>
#include <memory>
#include <functional>
#include <cassert>

namespace gust
{
    class Rigidbody2;
    class Contact2;
    
    // passkey pattern for privatizing certain classes, hope I am not wasting space 
    class PrivateToPhysicsEngine2
    {
    private:
        PrivateToPhysicsEngine2() = default;

    public:
        PrivateToPhysicsEngine2(const PrivateToPhysicsEngine2 &) = default;
        PrivateToPhysicsEngine2 &operator=(const PrivateToPhysicsEngine2 &) = default;
        ~PrivateToPhysicsEngine2() = default;

        friend class PhysicsEngine2;
    };

    class Collider2;
    class CircleCollider2;
    class RectangleCollider2;

    class PhysicsEngine2 {
    public:
        std::list<Rigidbody2> _bodies;
        
        

        void _clearContacts() {
            _contacts.clear();
        }

        void _generateCollisionContacts();
        void _resolveContacts();
        void _resolveContactInterpenetrations(Contact2 &contact);
        void _resolveContactVelocities(Contact2 &contact);

        std::vector<Contact2> _contacts;
        Vec2 gravityField;
        std::vector<std::unique_ptr<Collider2>> _colliders;

        PhysicsEngine2(Vec2 const &gravityField) : gravityField(gravityField) {}
        
        Rigidbody2& createBody(Tform2 const &tform,
                            real mass,
                            real inertia,
                            Vec2 const &velocity = {0.0f, 0.0f},
                            real angularVelocity = 0.0f,
                            real linearDamping = 0.1f,
                            real angularDamping = 0.1f) {
            _bodies.emplace_back(PrivateToPhysicsEngine2(),
                                 tform, mass, inertia, velocity,
                                 angularVelocity, linearDamping, angularDamping);
            return _bodies.back();
        }

        void destroyBody(Rigidbody2& body) {
            for(auto it = _bodies.begin(); it != _bodies.end(); ++it) {
                if(&(*it) == &body) {
                    _bodies.erase(it);
                    return;
                }
            }
        }

        // I give up on trying to make this work

        // template <typename T, typename... Args, typename = std::enable_if_t<std::is_base_of<Collider2, T>::value>>
        // T& createCollider(Args&&... args) {
        //     _colliders.emplace_back(std::make_unique<T>(PrivateToPhysicsEngine2(), 
        //                                                 std::forward<Args>(args)...));
        //     return *(static_cast<T*>((_colliders.back().get())));
        // }

        CircleCollider2& createCircleCollider(Rigidbody2 &body,
                                              real radius,
                                              Tform2 const &offset = Tform2(),
                                              real friction = 0.0f,
                                              real restitution = 0.0f);
        
        RectangleCollider2& createRectangleCollider(Rigidbody2 &body,
                                                    Vec2 const &size,
                                                    Tform2 const &offset = Tform2(),
                                                    real friction = 0.0f,
                                                    real restitution = 0.0f);

        template <typename T, typename = std::enable_if_t<std::is_base_of<Collider2, T>::value>>
        void deleteCollider(T& collider) {
            for(auto it = _colliders.begin(); it != _colliders.end(); ++it) {
                if((*it).get() == &collider) {
                    _colliders.erase(it);
                    return;
                }
            }
        }

        void createContact(Rigidbody2 &bodyA, Rigidbody2 &bodyB, 
                                Vec2 const &point, Vec2 const &normal, real penetration,
                                real restitution = 0.0f, real friction = 0.0f) {
            _contacts.emplace_back(PrivateToPhysicsEngine2(), 
                                   bodyA, bodyB,
                                   point, normal, penetration, 
                                   restitution, friction);
        }

        void runPhysics(real dt);
        friend void createCollisionContacts(PhysicsEngine2& engine);
    };
}

#endif // INCLUDE_GUST_PHYSICS_ENGINE2

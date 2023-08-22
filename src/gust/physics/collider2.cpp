#include <gust/physics/collider2.h>
#include <algorithm>
#include <limits>

using namespace gust;

bool CircleCollider2::inBounds(Vec2 const &point) const {
    return (point - body.transform * offset.translation).magnitudeSquared() <= radius * radius;
}

Vec2 CircleCollider2::clamp(Vec2 const &point) const  {
    Vec2 globalCenter = body.transform * offset.translation;
    Vec2 delta = point - globalCenter;
    if(delta.magnitudeSquared() <= radius * radius) return point;
    return globalCenter + delta.normal() * radius;
}

bool RectangleCollider2::inBounds(Vec2 const &point) const {
    Vec2 localPoint = (body.transform*offset).inverse() * point;
    return std::abs(localPoint.x) <= _halfSize.x && std::abs(localPoint.y) <= _halfSize.y;
}

Vec2 RectangleCollider2::clamp(Vec2 const &point) const {
    Tform2 globalTform = body.transform * offset;
    Vec2 localPoint = globalTform.inverse() * point;

    localPoint.x = std::max(-_halfSize.x, std::min(_halfSize.x, localPoint.x));
    localPoint.y = std::max(-_halfSize.y, std::min(_halfSize.y, localPoint.y));

    return globalTform * localPoint;
}

void CircleCollider2::visitCircle(CircleCollider2 const &other, PhysicsEngine2 &engine) const {


    Vec2 globalCenter = body.transform * offset.translation;
    Vec2 otherGlobalCenter = other.body.transform * other.offset.translation;
    Vec2 midline = otherGlobalCenter - globalCenter;

    real radiusSum = radius + other.radius;
    real midlineLength = midline.magnitude();

    if(midlineLength >= radiusSum - gust_physics_MIN_PENETRATION) return;

    Vec2 normal = midline/midlineLength;

    real penetration = radiusSum - midlineLength;
    Vec2 point = otherGlobalCenter - normal * other.radius;

    real restitution = (this->restitution + other.restitution) * 0.5f;
    real friction = (this->friction + other.friction) * 0.5f;

    engine.createContact(body, other.body, point, normal, penetration, restitution, friction);
}

void CircleCollider2::visitRectangle(RectangleCollider2 const &other , PhysicsEngine2 &engine) const {
    if(&body == &(other.body)) return;

    Vec2 globalCenter = body.transform * offset.translation;
    Tform2 otherTransform = other.body.transform * other.offset;
    Vec2 relativeCenter = otherTransform.inverse() * globalCenter;
    Vec2 relativeClosestPointWithinOther = relativeCenter;
    relativeClosestPointWithinOther.x = std::max(-other._halfSize.x, 
                                                 std::min(other._halfSize.x,
                                                          relativeClosestPointWithinOther.x));

    relativeClosestPointWithinOther.y = std::max(-other._halfSize.y,
                                                 std::min(other._halfSize.y,
                                                          relativeClosestPointWithinOther.y));
    
    if(relativeClosestPointWithinOther == relativeCenter) {
        real restitution = (this->restitution + other.restitution) * 0.5f;
        real friction = (this->friction + other.friction) * 0.5f;        

        real edgeDistances[] = {std::abs(other._halfSize.x - relativeCenter.x),
                                std::abs(-other._halfSize.x - relativeCenter.x),
                                std::abs(other._halfSize.y - relativeCenter.y),
                                std::abs(-other._halfSize.y - relativeCenter.y)};
        int minIndex = std::distance(edgeDistances, std::minmax_element(edgeDistances, edgeDistances + 4).first);
        real penetration = radius + edgeDistances[minIndex];

        switch(minIndex) {
            case 0:
                engine.createContact(body, other.body,
                                            globalCenter+otherTransform.getDirection()*edgeDistances[0],
                                            -otherTransform.getDirection(),
                                            penetration,
                                            restitution,
                                            friction);
                return;
            case 1:
                engine.createContact(body, other.body,
                                            globalCenter-otherTransform.getDirection()*edgeDistances[1],
                                            otherTransform.getDirection(),
                                            penetration,
                                            restitution,
                                            friction);
                return;
            case 2:
                engine.createContact(body, other.body,
                                            globalCenter+otherTransform.getOrthogonalDirection()*edgeDistances[2],
                                            -otherTransform.getOrthogonalDirection(),
                                            penetration,
                                            restitution,
                                            friction);
                return;
            case 3:
                engine.createContact(body, other.body,
                                            globalCenter-otherTransform.getOrthogonalDirection()*edgeDistances[3],
                                            otherTransform.getOrthogonalDirection(),
                                            penetration,
                                            restitution,
                                            friction);
                return;
        }

    }

    Vec2 closestPointWithinOther = otherTransform * relativeClosestPointWithinOther;

    Vec2 midline = closestPointWithinOther - globalCenter;
    real midlineLength = midline.magnitude();
    
    if(midlineLength > radius - gust_physics_MIN_PENETRATION) return;

    Vec2 normal = midline/midlineLength;

    real penetration = radius - midlineLength;

    real restitution = (this->restitution + other.restitution) * 0.5f;
    real friction = (this->friction + other.friction) * 0.5f;

    engine.createContact(body, other.body, closestPointWithinOther, normal, penetration, restitution, friction);
}

void RectangleCollider2::visitCircle(CircleCollider2 const &other, PhysicsEngine2 &engine) const {
    other.visitRectangle(*this, engine);
}

void RectangleCollider2::visitRectangle(RectangleCollider2 const &other, PhysicsEngine2 &engine) const {
    PolygonCollider2::visitPolygon(static_cast<PolygonCollider2 const &>(other), engine);
}

void PolygonCollider2::visitPolygon(PolygonCollider2 const &other, PhysicsEngine2 &engine) const {
    // Q := other, M := this(me), N := vertex of this, P := vertex of other, for any A,B : A_over_B := B relative to A
    // for any A,B A := is short for global_over_A

    Tform2 Q = other.body.transform * other.offset; // Q is short for global_over_Q
    Tform2 M = body.transform * offset;
    Tform2 M_over_Q = M.inverse() * Q;
    Tform2 Q_over_M = M_over_Q.inverse();

    real leastIntersectingProjection = std::numeric_limits<real>::max();
    std::vector<Tform2>::const_iterator leastIntersectingVertexIt = _vertexTforms.end();
    std::vector<Tform2>::const_iterator leastIntersectedEdgeIt = other._vertexTforms.end();

    bool thisBodyHasLeastIntersectingVertex = false;

    for(std::vector<Tform2>::const_iterator it = _vertexTforms.begin(); it != _vertexTforms.end(); ++it) {
        Tform2 N_over_Q = it->inverse() * M_over_Q; // _vertexTform[i] is M_over_N
        real maxProjection = gust_physics_MIN_PENETRATION; // maximum projection of a vertex of other wrt the edge N belongs
        std::vector<Tform2>::const_iterator supportVertexIt = other._vertexTforms.end();

        for(std::vector<Tform2>::const_iterator jt = other._vertexTforms.begin(); jt != other._vertexTforms.end(); ++jt) {
            Tform2 N_over_P = N_over_Q * (*jt); // other._vertexTform[j] is Q_over_P
            // y coordinate of P relative to N (N_over_P.y) is
            // the negative of the outward projected distance of P wrt to the edge N belongs
            if(maxProjection <= N_over_P.translation.y) {
                maxProjection = N_over_P.translation.y;
                supportVertexIt = jt;
            }
        }

        if(maxProjection == gust_physics_MIN_PENETRATION) return; // all of the points of other are outside of the edges of this polygon

        if(leastIntersectingProjection > maxProjection) {
            leastIntersectingProjection = maxProjection;
            leastIntersectingVertexIt = supportVertexIt;
            leastIntersectedEdgeIt = it;
        }
    }

    // do this for other polygon edges too in case it has a bigger intersection or all vertices of this lie outside of one of the edges of other
    for(std::vector<Tform2>::const_iterator it = other._vertexTforms.begin(); it != other._vertexTforms.end(); ++it) {
        Tform2 P_over_M = it->inverse() * Q_over_M; // other._vertexTform[i] is Q_over_P
        real maxProjection = gust_physics_MIN_PENETRATION; // maximum projection of a vertex of other wrt the edge P belongs
        std::vector<Tform2>::const_iterator supportVertexIt = _vertexTforms.end();

        for(std::vector<Tform2>::const_iterator jt = _vertexTforms.begin(); jt != _vertexTforms.end(); ++jt) {
            Tform2 P_over_N = P_over_M * (*jt); // _vertexTform[j] is M_over_N
            if(maxProjection <= P_over_N.translation.y) {
                maxProjection = P_over_N.translation.y;
                supportVertexIt = jt;
            }
        }

        if(maxProjection == gust_physics_MIN_PENETRATION) return; // all of the points of other are outside of the edges of this polygon

        if(leastIntersectingProjection > maxProjection) {
            leastIntersectingProjection = maxProjection;
            leastIntersectingVertexIt = supportVertexIt;
            leastIntersectedEdgeIt = it;
            thisBodyHasLeastIntersectingVertex = true;
        }
    }

    real restitution = (this->restitution + other.restitution) * 0.5f;
    real friction = (this->friction + other.friction) * 0.5f;

    if(thisBodyHasLeastIntersectingVertex) {
        Tform2 N = M * (*leastIntersectingVertexIt); // leastIntersectingVertexIt points to M_over_N
        Tform2 P = Q * (*leastIntersectedEdgeIt); // leastIntersectedEdgeIt points to Q_over_P
        engine.createContact(other.body, body, N.translation, -P.getOrthogonalDirection(), leastIntersectingProjection, restitution, friction);
    }
    else {
        Tform2 P = Q * (*leastIntersectingVertexIt); // leastIntersectingVertexIt points to Q_over_P
        Tform2 N = M * (*leastIntersectedEdgeIt); // leastIntersectedEdgeIt points to M_over_N
        engine.createContact(body, other.body, P.translation, -N.getOrthogonalDirection(), leastIntersectingProjection, restitution, friction);
    }
}

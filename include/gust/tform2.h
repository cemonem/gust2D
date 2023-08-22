#ifndef GUST_TFORM2_H
#define GUST_TFORM2_H

#include <gust/core.h>
#include <gust/vec2.h>
#include <iostream>
#include <cmath>

namespace gust {
    class Tform2 {
    private:
        Vec2 _direction;
    public:
        Vec2 translation;
        Tform2() : translation({}), _direction({1.0f, 0.0f}) {}
        Tform2(const Vec2 &_translation, real orientation) : translation(_translation),
                                                             _direction({std::cos(orientation),
                                                                         std::sin(orientation)}) {}
        Tform2(const Vec2 &_translation, const Vec2 &direction, bool normalize = false) : translation(_translation),
                                                                                         _direction(direction) {
            if(normalize) _direction.normalize();
        }

        real getOrientation() const {
            return _direction.orientation();
        }

        Vec2 getDirection() const {
            return _direction;
        }

        void setOrientation(real orientation) {
            _direction = {std::cos(orientation), std::sin(orientation)};
        }

        void setDirection(const Vec2 &direction, bool normalize = false) {
            _direction = direction;
            if(normalize) _direction.normalize();
        }

        Vec2 getOrthogonalDirection() const {
            return {-_direction.y, _direction.x};
        }

        void setOrthogonalDirection(const Vec2 &direction, bool normalize = false) {
            _direction = {-direction.y, direction.x};
            if(normalize) _direction.normalize();
        }

        Vec2 operator*(const Vec2& point) const {
            return {_direction.x * point.x - _direction.y * point.y + translation.x,
                    _direction.y * point.x + _direction.x * point.y + translation.y};
        }

        Tform2 operator*(const Tform2 &other) const {
            return {(*this) * other.translation,
                    {_direction.x * other._direction.x -_direction.y * other._direction.y,
                     _direction.y * other._direction.x + _direction.x * other._direction.y}};
        }

        Tform2 inverse() const {
            return {{-_direction.dot(translation), -_direction.cross(translation)},
                    {_direction.x, -_direction.y}};
        }

        void invert() {
            translation = {-_direction.dot(translation), -_direction.cross(translation)};
            _direction.y = -_direction.y;
        }

        void rotateLocal(real angle) {
            _direction.rotate(angle);
        }

    };

    inline std::ostream& operator<<(std::ostream& os, const Tform2& tform) {
        os << "Tform2{{" << tform.translation.x << ", " << tform.translation.y << "}, {"
           << tform.getDirection().x << ", " << tform.getDirection().y << ", " << tform.getOrientation() / gust_PI * 180.0f << " degrees}}";
        return os;
    }

}

#endif //GUST_TFORM2_H

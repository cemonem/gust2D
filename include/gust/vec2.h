#ifndef GUST_VEC2_H
#define GUST_VEC2_H

#include <gust/core.h>
#include <iostream>
#include <cmath>

namespace gust {
    class Vec2 {
    public:
        real x;
        real y;

        Vec2() : x(0.0f), y(0.0f) {}
        Vec2(real _x, real _y) : x(_x), y(_y) {}

        Vec2(const Vec2 &other) = default;
        Vec2 &operator=(const Vec2 &other) {
            if (this != &other) {
                x = other.x;
                y = other.y;
            }
            return *this;
        }

        Vec2 operator+(const Vec2 &other) const {
            return {x + other.x, y + other.y};
        }
        
        Vec2& operator+=(const Vec2 &other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vec2 operator-(const Vec2 &other) const {
            return {x - other.x, y - other.y};
        }

        Vec2& operator-=(const Vec2 &other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        bool operator==(const Vec2 &other) {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Vec2 &other) {
            return x != other.x || y != other.y;
        }

        real dot(const Vec2 &other) const {
            return x * other.x + y * other.y;
        }

        real cross(const Vec2 &other) const {
            return x * other.y - y * other.x;
        }

        Vec2 hadamard(const Vec2 &other) const {
            return {x * other.x, y * other.y};
        }

        Vec2 operator*(real scalar) const {
            return {x * scalar, y * scalar};
        }

        Vec2& operator*=(real scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        Vec2 operator/(real scalar) const {
            return {x / scalar, y / scalar};
        }

        Vec2 operator/=(real scalar) {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        real magnitudeSquared() const {
            return x * x + y * y;
        }

        real magnitude() const {
            return std::sqrt(magnitudeSquared());
        }

        real orientation() const {
            return std::atan2(y, x);
        }

        Vec2 normal() const {
            real mag = magnitude();
            if (mag != 0.0f) {
                return {x / mag, y / mag};
            }
            return {};
        }

        void normalize() {
            real mag = magnitude();
            if (mag != 0.0f) {
                x /= mag;
                y /= mag;
            }
        }

        Vec2 rotated(real angle) const {
            real cosAngle = std::cos(angle);
            real sinAngle = std::sin(angle);
            return {x * cosAngle - y * sinAngle, x * sinAngle + y * cosAngle};
        }

        void rotate(real angle) {
            real cosAngle = std::cos(angle);
            real sinAngle = std::sin(angle);
            real newX = x * cosAngle - y * sinAngle;
            real newY = x * sinAngle + y * cosAngle;
            x = newX;
            y = newY;
        }

        Vec2 rotated90() const {
            return {-y, x};
        }

        void rotate90() {
            real newX = -y;
            y = x;
            x = newX;
        }

        bool nearZero(real epsilon = gust_EPSILON) const {
            return std::abs(x) < epsilon && std::abs(y) < epsilon;
        }
    };

    inline std::ostream& operator<<(std::ostream& out, const Vec2 &vector) {
        out << "Vec2{" << vector.x << ", " << vector.y << "}";
        return out;
    }

    inline Vec2 operator*(real scalar, const Vec2 &vector) {
        return {vector.x * scalar, vector.y * scalar};
    }
    
    inline Vec2 operator+(real scalar, const Vec2 &vector) {
        return {vector.x + scalar, vector.y + scalar};
    }

    inline Vec2 operator-(real scalar, const Vec2 &vector) {
        return {vector.x - scalar, vector.y - scalar};
    }

    inline Vec2 operator-(const Vec2 &vector) {
        return {-vector.x, -vector.y};
    }
}

#endif //GUST_VEC2_H

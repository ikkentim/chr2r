#pragma once

#include <math.h>
#include <assert.h>

struct Vector2 {
    double x;
    double y;

    Vector2() :x(0), y(0){ }
    Vector2(double a, double b) :x(a), y(b){ }

    inline void zero() {
        x = 0;
        y = 0;
    }

    inline bool is_zero() const {
        return x == 0 && y == 0;
    }

    inline double length() {
        return sqrt(length_sq());
    }

    inline double length_sq() {
        return x * x + y * y;
    }

    inline void normalize() {
        double len = length();
        x /= len;
        y /= len;
    }

    inline double dot(const Vector2 &v2) const {
        return x*v2.x + y*v2.y;
    }

    void truncate(double max) {
        assert(max > 0);

        double len = length();

        if (len < max) return;

        len /= max;

        x /= len;
        y /= len;
    }

	void truncate_x(double max)
	{
		assert(max > 0);

		if (abs(x) < max) return;

		x = x < 0 ? -max : max;
	}

    void truncate_y(double max)
    {
        assert(max > 0);

        if (abs(y) < max) return;

        y = y < 0 ? -max : max;
    }

    inline double distance(const Vector2 &v2) {
        return sqrt(distance_sq(v2));
    }

    inline double distance_sq(const Vector2 &v2) {
        return (x - v2.x) * (x - v2.x) + (y - v2.y) * (y - v2.y);
    }

    inline Vector2 reverse() const {
        return{ y, x };
    }

    inline Vector2 operator+(Vector2 rhs) {
        return{ rhs.x + x, rhs.y + y };
    }

    inline Vector2 operator+=(Vector2 rhs) {
        x += rhs.x;
        y += rhs.y;

        return *this;
    }

    inline Vector2 operator-=(Vector2 rhs) {
        x -= rhs.x;
        y -= rhs.y;

        return *this;
    }

    inline Vector2 operator-(Vector2 rhs) {
        return{ x - rhs.x, y - rhs.y };
    }

    inline Vector2 operator-() {
        return{ -x, -y };
    }

    inline Vector2 operator*(Vector2 rhs) {
        return{ x * rhs.x, y * rhs.y };
    }

    inline Vector2 operator*(double rhs) {
        return{ x * rhs, y * rhs };
    }

    inline Vector2 operator/(Vector2 rhs) {
        return{ x / rhs.x, y / rhs.y };
    }

    inline Vector2 operator/(double rhs) {
        return{ x / rhs, y / rhs };
    }

    inline bool operator==(Vector2 rhs) {
        return rhs.x == x && rhs.y == y;
    }

    inline bool operator!=(Vector2 rhs) {
        return rhs.x != x || rhs.y != y;
    }

    inline bool operator<(Vector2 rhs) {
        return length_sq() < rhs.length_sq();
    }
    inline bool operator<=(Vector2 rhs) {
        return length_sq() <= rhs.length_sq();
    }
    inline bool operator>(Vector2 rhs) {
        return length_sq() > rhs.length_sq();
    }
    inline bool operator>=(Vector2 rhs) {
        return length_sq() >= rhs.length_sq();
    }
};
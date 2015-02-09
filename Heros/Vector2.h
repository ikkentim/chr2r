#include <math.h>
#include <assert.h>

#pragma once

struct Vector2 {
    double x;
    double y;

    Vector2() :x(0), y(0){ }
    Vector2(double a, double b) :x(a), y(b){ }

    inline void Zero() {
        x = 0;
        y = 0;
    }

    inline bool IsZero() const {
        return x == 0 && y == 0;
    }

    inline double Length() {
        return sqrt(LengthSq());
    }

    inline double LengthSq() {
        return x * x + y * y;
    }

    inline void Normalize() {
        double length = Length();
        x /= length;
        y /= length;
    }

    inline double Dot(const Vector2 &v2) const {
        return x*v2.x + y*v2.y;
    }

    void Truncate(double max) {
        assert(max > 0);

        double length = Length();

        if (length < max) return;

        length /= max;

        x /= length;
        y /= length;
    }

	void TruncateX(double max)
	{
		assert(max > 0);

		if (abs(x) < max) return;

		x = max;
	}

    inline double Distance(const Vector2 &v2) {
        return sqrt(DistanceSq(v2));
    }

    inline double DistanceSq(const Vector2 &v2) {
        return (x - v2.x) * (x - v2.x) + (y - v2.y) * (y - v2.y);
    }

    inline Vector2 GetReverse() const {
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
        return LengthSq() < rhs.LengthSq();
    }
    inline bool operator<=(Vector2 rhs) {
        return LengthSq() <= rhs.LengthSq();
    }
    inline bool operator>(Vector2 rhs) {
        return LengthSq() > rhs.LengthSq();
    }
    inline bool operator>=(Vector2 rhs) {
        return LengthSq() >= rhs.LengthSq();
    }
};
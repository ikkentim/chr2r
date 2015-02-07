#include <math.h>
#include <assert.h>

#pragma once

struct Vector2 {
    float x;
    float y;

    Vector2() :x(0), y(0){ }
    Vector2(float a, float b) :x(a), y(b){ }

    inline void Zero() {
        x = 0;
        y = 0;
    }

    inline bool IsZero() const {
        return x == 0 && y == 0;
    }

    inline float Length() {
        return sqrt(LengthSq());
    }

    inline float LengthSq() {
        return x * x + y * y;
    }

    inline void Normalize() {
        float length = Length();
        x /= length;
        y /= length;
    }

    inline float Dot(const Vector2 &v2) const {
        return x*v2.x + y*v2.y;
    }

    void Truncate(float max) {
        assert(max > 0);

        float length = Length();

        if (length < max) return;

        length /= max;

        x /= length;
        y /= length;
    }

	void TruncateX(float max)
	{
		assert(max > 0);

		if (abs(x) < max) return;

		x = max;
	}

    inline float Distance(const Vector2 &v2) {
        return sqrt(DistanceSq(v2));
    }

    inline float DistanceSq(const Vector2 &v2) {
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

    inline Vector2 operator*(float rhs) {
        return{ x * rhs, y * rhs };
    }

    inline Vector2 operator/(Vector2 rhs) {
        return{ x / rhs.x, y / rhs.y };
    }

    inline Vector2 operator/(float rhs) {
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
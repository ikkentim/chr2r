/**
 * Vector2.h
 * Defines the Vector2 structure.
 */
#pragma once

#include <math.h>
#include <assert.h>

// Represents a 2D vector
struct Vector2 {
    // X-coordinate
    double x;

    // Y-coordinate
    double y;

    // Default constructor
    Vector2() :
        x(0), 
        y(0) { }

    // A constructor which sets the x and y values
    Vector2(double a, double b) :
        x(a), 
        y(b) { }

    // Resets the vector to zero
    inline void zero() {
        x = 0;
        y = 0;
    }

    // Gets a value indicating whether the vector is zero
    inline bool is_zero() const {
        return x == 0 && y == 0;
    }

    // Gets the length
    inline double length() {
        return sqrt(length_sq());
    }

    // Gets the squared length
    inline double length_sq() {
        return x * x + y * y;
    }

    // Normalizes the elements
    inline void normalize() {
        double len = length();
        x /= len;
        y /= len;
    }

    // Dots the vector with the specified vector
    inline double dot(const Vector2 &v2) const {
        return x*v2.x + y*v2.y;
    }

    // Truncates the vector at the specified limit
    void truncate(double max) {
        assert(max > 0);

        double len = length();

        if (len < max) return;

        len /= max;

        x /= len;
        y /= len;
    }

    // Truncates the x component of the vector at the specified limit
	void truncate_x(double max)
	{
		assert(max > 0);

		if (abs(x) < max) return;

		x = x < 0 ? -max : max;
	}

    // Truncates the y component of the vector at the specified limit
    void truncate_y(double max)
    {
        assert(max > 0);

        if (abs(y) < max) return;

        y = y < 0 ? -max : max;
    }

    // Gets the distance to the specified vector
    inline double distance(const Vector2 &v2) {
        return sqrt(distance_sq(v2));
    }

    // Gets the squared distance to the specified vector
    inline double distance_sq(const Vector2 &v2) {
        return (x - v2.x) * (x - v2.x) + (y - v2.y) * (y - v2.y);
    }

    // Gets the reversed vector
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
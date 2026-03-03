# pragma once
# include "utils/io_helpers.hpp"


struct Vector3
{
    double x, y, z = 0;

    Vector3(): x(0), y(0), z(0) { }
    Vector3(int x, int y, int z)
    : x(x), y(y), z(z) { }
    Vector3(double x, double y, double z)
    : x(x), y(y), z(z) { }

    Vector3 const operator*(const double s)
    {
        return Vector3(x * s, y * s, z * s);
    }
    Vector3 const operator*=(const double s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    std::string ToCSVString() const
    {
        return STR(x << "," << y << "," << z);
    }

    std::string ToString() const
    {
        return STR("(" << ToCSVString() << ")");
    }
};
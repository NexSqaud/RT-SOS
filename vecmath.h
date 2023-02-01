#include <math.h>
#include "types.h"

#define POSITIVE_INFFINITY (1.0 / 0.0)

Vector3 add(Vector3 u, Vector3 v)
{
    Vector3 res = { u.x + v.x, u.y + v.y, u.z + v.z };
    return res;
}

Vector3 minus(Vector3 u, Vector3 v)
{
    Vector3 res = { u.x - v.x, u.y - v.y, u.z - v.z };
    return res;
}

Vector3 multiply(Vector3 u, Vector3 v)
{
    Vector3 res = { u.x * v.x, u.y * v.y, u.z * v.z };
    return res;
}

Vector3 multiply2(Vector3 u, float t)
{
    Vector3 res = { u.x * t, u.y * t , u.z * t };
    return res;
}

Vector3 divide(Vector3 u, float t)
{
    Vector3 res = { u.x / t, u.y / t,u.z / t };
    return res;
}

float dot(Vector3 u, Vector3 v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

Vector3 cross(Vector3 u, Vector3 v)
{
    Vector3 res = {
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    };
    return res;
}

float length(Vector3 vec)
{
    return sqrt(dot(vec, vec));
}

Vector3 normalize(Vector3 vec)
{
    return divide(vec, length(vec));
}

Vector3 at(Ray ray, float t)
{
    return add(ray.origin, multiply2(ray.direction, t));
}
#include <stdbool.h>
#include "types.h"
#include "vecmath.h"

#ifndef __INTERSECTIONS_H__
#define __INTERSECTIONS_H__

bool sphereIntersect(void* object, Vector3 origin, Vector3 direction, float tMin, Vector3* normal, float* t)
{
    Object* sphere = (Object*)object;
    SphereData* data = (SphereData*)sphere->data;
    Vector3 originToCenter = minus(origin, sphere->position);

    float a = dot(direction, direction);
    float b = 2 * dot(originToCenter, direction);
    float c = dot(originToCenter, originToCenter) - (data->radius * data->radius);

    float discriminant = (b * b) - (4.f * (a * c));

    if (discriminant < 0)
    {
        return false;
    }

    float t1 = (-b + sqrt(discriminant)) / (2 * a);
    float t2 = (-b - sqrt(discriminant)) / (2 * a);

    if (t1 > tMin) *t = t1;
    if (t2 < t1 && t2 > tMin) *t = t2;

    *normal = normalize(minus(add(origin, multiply2(direction, *t)), sphere->position));
    return *t > tMin;
}

#endif
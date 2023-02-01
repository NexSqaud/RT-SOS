#include "intersections.h"
#include <stdlib.h>

Object* initSphere(Vector3 position, Color color, float radius)
{
    SphereData* data = (SphereData*)malloc(sizeof(SphereData));
    Object* object = (Object*)malloc(sizeof(Object));

    printf("object: %x, data: %x\n", (uint32_t)object, (uint32_t)data);

    data->radius = radius;
    object->position = position;
    object->color = color;
    object->data = data;
    object->intersection = sphereIntersect;
    return object;
}

//Object initSphere(Vector3 position, Color color, float radius)
//{
//    return (Object) {
//        .position = position,
//            .color = color,
//            .data
//    }
//}
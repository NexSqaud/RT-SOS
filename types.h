#ifndef __TYPES_H__
#define __TYPES_H__

typedef struct
{
    float x;
    float y;
    float z;
} Vector3;

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;

typedef struct
{
    Vector3 origin;
    Vector3 direction;
} Ray;


typedef struct
{
    Vector3 position;
    Color color;
    void* data;

    bool(*intersection)(void*, Vector3, Vector3, float, Vector3*, float*);
} Object;

typedef struct
{
    float radius;
} SphereData;


#endif
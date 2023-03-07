#include <stdbool.h>
#include <stdio.h>
#include <vesa.h>

#include "main.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define X_OFFSET 200
#define Y_OFFSET 200

#define SKY_COLOR { 0xFF, 0xBF, 0x00 }

//#define ARR_SIZE(x) (sizeof((x)) / sizeof((x)[0]))

Color traceRay(Vector3 origin, Vector3 direction);
bool minObjectIntersect(Vector3 origin, Vector3 direction, float tMin, Vector3* normal, float* t, Object** object);

typedef union
{
    Color color;
    uint32_t vesaColor;
} VESAColor;

static Object** objects = NULL;
static int objectsLength = 0;

static Vector3 lightPosition = (Vector3){ 5.f, 5.f, -1.f };
static float lightIntensity = 0.45f;
static float ambientIntensity = 0.15f;

void addObject(Object* object)
{
    static int length = 0;
    length++;
    Object* newArray = malloc(sizeof(Object) * length);
    if (!newArray)
    {
        printf("NOT ALLOCATED!\n");
		return;
    }

    if (objects != NULL)
    {
        for (int i = 0; i < length - 1; i++)
        {
            newArray[i] = objects[i];
        }
        free(objects);
    }
	
    newArray[length - 1] = object;

    objects = newArray;
    objectsLength = length;
}

Color colorMultiply(Color color, float t)
{
	if(t <= 0) return (Color){ 0, 0, 0 };
	if(t > 1.f) t = 1.f;
	return (Color){ color.r * t, color.g * t, color.b * t };
}

int main(void)
{
    addObject(initSphere((Vector3) { 0.f, 0.f, 5.f }, (Color) { 0xFF, 0xFF, 0xFF }, 1.f));
    addObject(initSphere((Vector3) { -0.5f, 2.f, 5.f }, (Color) { 0x00, 0xFF, 0x00 }, 1.f));
    addObject(initSphere((Vector3) { 4.f, 1.f, 10.f }, (Color) { 0x00, 0xFF, 0xFF }, 2.f));
    addObject(initSphere((Vector3) { 0.f, -6001.f, 10.f }, (Color) { 0x00, 0x00, 0xFF }, 6000.f));

    const float aspectRatio = SCREEN_WIDTH / SCREEN_HEIGHT;

    const float viewportHeight = 2.f;
    const float viewportWidth = viewportHeight * aspectRatio;
    const float focalLength = 1.f;

    Vector3 origin = { 0, 0, 0 };
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            Vector3 direction = { (x - SCREEN_WIDTH / 2) * viewportWidth / SCREEN_WIDTH, -(y - SCREEN_HEIGHT / 2) * viewportHeight / SCREEN_HEIGHT, focalLength };
            direction = normalize(direction);
            VESAColor vesaColor;
            vesaColor.color = traceRay(origin, direction);
            draw_pixel(x + X_OFFSET, y + Y_OFFSET, vesaColor.vesaColor);
        }
    }

    return 0;
}

Color traceRay(Vector3 origin, Vector3 direction)
{
    float t = 0.f;
    Object* object = NULL;
    Vector3 normal = { 0, 0, 0 };

    if (minObjectIntersect(origin, direction, 0.0001f, &normal, &t, &object))
    {
        Vector3 intersection = add(origin, multiply2(direction, t));
        Vector3 lightDirection = normalize(minus(lightPosition, intersection));
        return colorMultiply(object->color, 
			    (dot(normal, normalize(lightDirection)) / (length(normal) * length(normalize(lightDirection)))) * lightIntensity 
                            + ambientIntensity); // TODO: make lights array
    }
    Color sky = SKY_COLOR;
    return sky;
}

bool minObjectIntersect(Vector3 origin, Vector3 direction, float tMin, Vector3* normal, float* t, Object** intersectedObject)
{
    float tTemp = 0.f;
    *t = POSITIVE_INFFINITY;
    Vector3 normalTemp = { 0,0,0 };
    for (int i = 0; i < objectsLength; i++)
    {
        Object* object = *(objects + i);
        if (object->intersection(object, origin, direction, tMin, &normalTemp, &tTemp))
        {
            if (tTemp < *t && tTemp > tMin)
            {
                *t = tTemp;
                *normal = normalTemp;
                *intersectedObject = object;
            }
        }
    }

    return *t != POSITIVE_INFFINITY;
}

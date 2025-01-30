#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vector2.h"

class Camera
{
public:
    float x = 0;
    float y = 0;

public:
    Camera() = default;
    ~Camera() = default;

    void set_size(const Vector2& size)
    {
        this->size = size;
    }

    const Vector2& get_size() const
    {
        return size;
    }

    const Vector2& get_position() const
    {
        return position;
    }

    void look_at(const Vector2& target)
    {
        position = target - size / 2.0f;
    }

private:
    Vector2 position;
    Vector2 size;
};

#endif
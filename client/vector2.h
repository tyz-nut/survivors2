#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <cmath>
#include <string>

class Vector2
{
public:
    float x = 0;
    float y = 0;

public:
    Vector2() = default;
    ~Vector2() = default;

    Vector2(float x, float y)
        :x(x), y(y) {
    }

    Vector2 operator+(const Vector2& vec) const
    {
        return Vector2(x + vec.x, y + vec.y);
    }

    Vector2 operator-(const Vector2& vec) const
    {
        return Vector2(x - vec.x, y - vec.y);
    }

    Vector2 operator*(float val) const
    {
        return Vector2(x * val, y * val);
    }

    Vector2 operator/(float val) const
    {
        return Vector2(x / val, y / val);
    }

    void operator+=(const Vector2& vec)
    {
        x += vec.x, y += vec.y;
    }

    void operator-=(const Vector2& vec)
    {
        x -= vec.x, y -= vec.y;
    }

    float operator*(const Vector2& vec) const
    {
        return x * vec.x + y * vec.y;
    }

    void operator*=(float val)
    {
        x *= val, y *= val;
    }

    void operator/=(float val)
    {
        x /= val, y /= val;
    }

    float length()
    {
        return sqrt(x * x + y * y);
    }

    Vector2 normalize()
    {
        float len = length();

        if (len == 0)
            return Vector2(0, 0);

        return Vector2(x / len, y / len);
    }

    bool approx(const Vector2& target)
    {
        return(*this - target).length() <= 0.0001f;
    }

    const std::string Vtos() const
    {
        std::string str = std::to_string(this->x) + "," + std::to_string(this->y);
        return str;
    }

    static const Vector2 stoV(const std::string& s)
    {
        std::string s1, s2;
        Vector2 vec;
        std::string::size_type pos1, pos2;
        pos2 = s.find(',');
        pos1 = 0;
        if (std::string::npos != pos2)
        {
            s1 = s.substr(pos1, pos2 - pos1);
            s2 = s.substr(pos2 + 1);
            vec.x = std::stof(s1);
            vec.y = std::stof(s2);
            return vec;
        }
        return Vector2(0, 0);
    }
};

#endif

#include "Vector2.h"
#pragma once
class Collider {
public:
    virtual bool isColliding(const Collider& other) const = 0;
};

class CircleCollider : public Collider {
private:
    float radius;
    Vector2 point; // Position of the circle's center

public:
    CircleCollider(Vector2 _point, float _radius) : point(_point), radius(_radius) {}

    bool isColliding(const Collider& other) const override;
};

class RectangleCollider : public Collider {
private:
    Vector2 pointUL;
    Vector2 pointDR; // Position of the rectangle's top-left corner

public:
    RectangleCollider(Vector2 _pointUL, Vector2 _pointDR) : pointUL(_pointUL), pointDR(_pointDR) {}

    bool isColliding(const Collider& other) const override;
};
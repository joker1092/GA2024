#pragma once
#include "../stdafx.h"
#include "Vector2.h"
#include "Bounds.h"
#include "./Objects/Object.h"
class Collider {
private:
    

    friend struct Object;
    friend class CircleCollider;
    friend class RectangleCollider;
    friend class ColliderManager;
    virtual Vector2 GetPosition() const = 0;    // 중심과 오브젝트 위치를 더한 값.
public:
    virtual bool isColliding(const Collider& other) const = 0;
    virtual bool isPointColliding(const Vector2& point) const = 0;
    Object* parent;
    bool isActive = true;
    virtual ~Collider()
    {

    }
};

// 원 충돌체 (마우스 포인터나, 원모양 객체에 사용)
class CircleCollider : public Collider {
private:
    float radius = 0.f;
    Vector2 point = {0.f, 0.f};

    friend struct Object;
    friend class Collider;
    friend class CircleCollider;
    friend class RectangleCollider;

    Vector2 GetPosition() const override; 
public:
    CircleCollider(Vector2 _point, float _radius) : point(_point), radius(_radius) {}
    ~CircleCollider() override {}
    bool isColliding(const Collider& other) const override;
    bool isPointColliding(const Vector2& point) const override;
};

// 사각형 충돌체
class RectangleCollider : public Collider {
private:

    friend struct Object;
    friend class Collider;
    friend class CircleCollider;
    friend class RectangleCollider;

    Vector2 GetPosition() const override;
public:
    Bounds bounds = { {0.f,0.f}, {0.f, 0.f} };
    RectangleCollider(Vector2 _pointUL, Vector2 _pointDR) {
        bounds = { {0.0f,0.0f}, {(_pointDR.x - _pointUL.x) / 2.0f, (_pointDR.y - _pointUL.y) / 2.0f} };
    }
    RectangleCollider(Vector2 _center, float _width, float _height) {
        bounds.center = _center;
        bounds.extents = Vector2(_width / 2, _height / 2);
    }
    ~RectangleCollider() override {}
    bool isColliding(const Collider& other) const override;
    bool isPointColliding(const Vector2& point) const override;
};
#include "Collider.h"


Vector2 CircleCollider::GetPosition() const {
    if (parent == nullptr) {
        return point;
    }
    return parent->GetPosition() + point;
}

bool CircleCollider::isColliding(const Collider& other) const {
    if (isActive == false || other.isActive == false) return false; // 둘중 하나라도 비활성화라면 이 충돌검사는 무효.
    // 원과 원 충돌
    if (const CircleCollider* circle = dynamic_cast<const CircleCollider*>(&other)) {
        float distance = std::sqrt(std::pow(circle->GetPosition().x - GetPosition().x, 2) +
            std::pow(circle->GetPosition().y - GetPosition().y, 2));
        return distance < circle->radius + radius;
    }
    // 원과 사각형 충돌
    else if (const RectangleCollider* r = dynamic_cast<const RectangleCollider*>(&other)) {
        auto circleX = GetPosition().x;
        auto circleY = GetPosition().y;
        auto rectX = r->GetPosition().x;
        auto rectY = r->GetPosition().y;
        if (circleX >= rectX - r->bounds.extents.x &&
            circleX <= rectX + r->bounds.extents.x &&
            circleY >= rectY - r->bounds.extents.y &&
            circleY <= rectY + r->bounds.extents.y) {
            return true;
        }

        // 원의 중심이 사각형의 가장자리에 있는지 확인
        float dx = circleX - std::max(rectX - r->bounds.extents.x,
            std::min(circleX, rectX + r->bounds.extents.x));
        float dy = circleY - std::max(rectY - r->bounds.extents.y,
            std::min(circleY, rectY + r->bounds.extents.y));
        return (dx * dx + dy * dy) <= (radius * radius);
    }
    return false;
}

bool CircleCollider::isPointColliding(const Vector2& point) const {
    if (isActive == false) return false;
    float distance = std::sqrt(std::pow(GetPosition().x - point.x, 2) +
        std::pow(GetPosition().y - point.y, 2));
    return distance < radius;
}

Vector2 RectangleCollider::GetPosition() const {
    if (parent == nullptr) {
        return bounds.center;
    }
    return parent->GetPosition() + bounds.center;
}

bool RectangleCollider::isColliding(const Collider& other) const {
    if (isActive == false || other.isActive == false) return false; // 둘중 하나라도 비활성화라면 이 충돌검사는 무효.
    // 사각형과 원 충돌
    if (const CircleCollider* c = dynamic_cast<const CircleCollider*>(&other)) {
        auto circleX = c->GetPosition().x;
        auto circleY = c->GetPosition().y;
        auto rectX = GetPosition().x;
        auto rectY = GetPosition().y;
        if (circleX >= rectX - bounds.extents.x && 
            circleX <= rectX + bounds.extents.x &&
            circleY >= rectY - bounds.extents.y &&
            circleY <= rectY + bounds.extents.y) {
            return true;
        }

        // 원의 중심이 사각형의 가장자리에 있는지 확인
        float dx = circleX - std::max(rectX - bounds.extents.x,
            std::min(circleX, rectX + bounds.extents.x));
        float dy = circleY - std::max(rectY - bounds.extents.y,
            std::min(circleY, rectY + bounds.extents.y));
        return (dx * dx + dy * dy) <= (c->radius * c->radius);
    }
    // 사각형과 사각형 충돌
    else if (const RectangleCollider* r = dynamic_cast<const RectangleCollider*>(&other)) {
        auto compare1 = GetPosition();
        auto compare2 = r->GetPosition();
        Vector2 thisLcorner = Vector2(-bounds.extents.x, - bounds.extents.y);
        thisLcorner += compare1;
        Vector2 thisRcorner = bounds.extents;
        thisRcorner += compare1;
        Vector2 otherLcorner = Vector2(-r->bounds.extents.x, -r->bounds.extents.y);
        otherLcorner += compare2;
        Vector2 otherRcorner = r->bounds.extents;
        otherRcorner += compare2;

        if (otherRcorner.y < thisLcorner.y
            || otherLcorner.y > thisRcorner.y
            || otherRcorner.x < thisLcorner.x
            || otherLcorner.x > thisRcorner.x)
            return false;
        else
            return true;
    }
}

bool RectangleCollider::isPointColliding(const Vector2& point) const {
    if (isActive == false) return false;
    float rectX = GetPosition().x;
    float rectY = GetPosition().y;
    if (point.x >= rectX - bounds.extents.x &&
        point.x <= rectX + bounds.extents.x &&
        point.y >= rectY - bounds.extents.y &&
        point.y <= rectY + bounds.extents.y) {
        return true;
    }
    return false;
}
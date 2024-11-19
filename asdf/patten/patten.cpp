#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

class Shape;  // Forward declaration

// Step 1: Observer 인터페이스 정의
class Observer
{
public:
    virtual void onShapeChanged(Shape* shape) = 0;
};

// Step 2: Shape 클래스에 옵저버 패턴 적용
class Shape
{
public:
    virtual ~Shape() = default;

    void addObserver(Observer* observer)
    {
        observers.push_back(observer);
    }

    void notifyObservers()
    {
        for (auto observer : observers)
        {
            observer->onShapeChanged(this);
        }
    }

    virtual void accept(class Visitor* visitor) = 0;

protected:
    std::vector<Observer*> observers;
};

// Step 3: Circle과 Rectangle 정의 (속성 변화 시 옵저버 통지)
class Circle : public Shape
{
public:
    Circle(double radius) : radius(radius) {}

    double getRadius() const { return radius; }

    void setRadius(double newRadius)
    {
        radius = newRadius;
        notifyObservers();  // 속성이 변경되었을 때 옵저버에게 알림
    }

    void accept(Visitor* visitor) override;

private:
    double radius;
};

class Rectangle : public Shape
{
public:
    Rectangle(double width, double height) : width(width), height(height) {}

    double getWidth() const { return width; }
    double getHeight() const { return height; }

    void setDimensions(double newWidth, double newHeight)
    {
        width = newWidth;
        height = newHeight;
        notifyObservers();  // 속성이 변경되었을 때 옵저버에게 알림
    }

    void accept(Visitor* visitor) override;

private:
    double width, height;
};

// Step 4: Visitor 인터페이스 및 구현
class Visitor
{
public:
    virtual void visit(Circle* circle) = 0;
    virtual void visit(Rectangle* rectangle) = 0;
};

void Circle::accept(Visitor* visitor)
{
    visitor->visit(this);
}

void Rectangle::accept(Visitor* visitor)
{
    visitor->visit(this);
}

class AreaVisitor : public Visitor
{
public:
    void visit(Circle* circle) override
    {
        double area = 3.14159 * std::pow(circle->getRadius(), 2);
        std::cout << "Circle Area: " << area << std::endl;
    }

    void visit(Rectangle* rectangle) override
    {
        double area = rectangle->getWidth() * rectangle->getHeight();
        std::cout << "Rectangle Area: " << area << std::endl;
    }
};

// Step 5: ShapeObserver 구현 (옵저버 클래스)
class ShapeObserver : public Observer
{
public:
    void onShapeChanged(Shape* shape) override
    {
        std::cout << "Shape changed! Recalculating area." << std::endl;
        AreaVisitor areaVisitor;
        shape->accept(&areaVisitor);  // 변경된 도형의 면적을 다시 계산
    }
};

int main()
{
    // 도형 생성
    Circle circle(5.0);
    Rectangle rectangle(3.0, 4.0);

    // 옵저버 생성 및 등록
    ShapeObserver observer;
    circle.addObserver(&observer);
    rectangle.addObserver(&observer);

    // 처음 면적 계산
    AreaVisitor areaVisitor;
    circle.accept(&areaVisitor);
    rectangle.accept(&areaVisitor);

    std::cout << "\n--- Changing Circle Radius ---" << std::endl;
    circle.setRadius(10.0);  // 반지름 변경 -> 옵저버에게 알림

    std::cout << "\n--- Changing Rectangle Dimensions ---" << std::endl;
    rectangle.setDimensions(6.0, 8.0);  // 가로와 세로 변경 -> 옵저버에게 알림

    return 0;
}

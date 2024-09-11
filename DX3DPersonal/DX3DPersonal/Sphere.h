#pragma once
#include "framework.h"
#include "Vertex.h"

class Sphere {
public:
    Sphere(Vector3 center, float radius);
    Sphere(float centerX, float centerY, float centerZ, float radius);

    const std::vector<Vertex>& getVertices() const;
    const std::vector<unsigned int>& getIndices() const;

    /*void setLatitudeSegments(int segments) { latitudeSegments = segments; };
    void setLongitudeSegments(int segments) { longitudeSegments = segments; };*/
private:
    void generateVertices();
    void generateIndices();
    Vector3 center; // 중점 좌표
    float r; // 반지름
    int latitudeSegments; // 위도 분할 수
    int longitudeSegments; // 경도 분할 수
    std::vector<Vertex> vertices; // 정점 정보
    std::vector<unsigned int> indices; // 인덱스 버퍼
};


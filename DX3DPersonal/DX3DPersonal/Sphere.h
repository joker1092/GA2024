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
    Vector3 center; // ���� ��ǥ
    float r; // ������
    int latitudeSegments; // ���� ���� ��
    int longitudeSegments; // �浵 ���� ��
    std::vector<Vertex> vertices; // ���� ����
    std::vector<unsigned int> indices; // �ε��� ����
};


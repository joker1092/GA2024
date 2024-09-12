#pragma once
#include "framework.h"
#include "Vertex.h"

class Sphere {
public:
    Sphere(ID3D11Device* device,Vector3 center, float radius);
    Sphere(ID3D11Device* device, float centerX, float centerY, float centerZ, float radius);

    const std::vector<Vertex>& getVertices() const;
    const std::vector<unsigned int>& getIndices() const;

    void Draw(ID3D11DeviceContext* pContext);
    /*void setLatitudeSegments(int segments) { latitudeSegments = segments; };
    void setLongitudeSegments(int segments) { longitudeSegments = segments; };*/
private:
    void generateVertices();
    void generateIndices();

    ID3D11Device* m_pDevice = nullptr; //3d11 디바이스

    Vector3 center; // 중점 좌표
    float r; // 반지름
    int latitudeSegments; // 위도 분할 수
    int longitudeSegments; // 경도 분할 수


    std::vector<Vertex> vertices; // 정점 정보
    ID3D11Buffer* m_pVertexBuffer = nullptr; // 버텍스 버퍼
    std::vector<unsigned int> indices; // 인덱스 정보
    ID3D11Buffer* m_pIndexBuffer = nullptr; // 인덱스 버퍼
};


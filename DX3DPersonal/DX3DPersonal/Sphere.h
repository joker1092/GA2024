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

    ID3D11Device* m_pDevice = nullptr; //3d11 ����̽�

    Vector3 center; // ���� ��ǥ
    float r; // ������
    int latitudeSegments; // ���� ���� ��
    int longitudeSegments; // �浵 ���� ��


    std::vector<Vertex> vertices; // ���� ����
    ID3D11Buffer* m_pVertexBuffer = nullptr; // ���ؽ� ����
    std::vector<unsigned int> indices; // �ε��� ����
    ID3D11Buffer* m_pIndexBuffer = nullptr; // �ε��� ����
};


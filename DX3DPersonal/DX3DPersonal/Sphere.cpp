#include "Sphere.h"

Sphere::Sphere(ID3D11Device* device, Vector3 center, float radius)
	:m_pDevice(device),center(center), r(radius)
{
	generateVertices();
	generateIndices();
}


Sphere::Sphere(ID3D11Device* device, float centerX, float centerY, float centerZ, float radius)
	:m_pDevice(device),center(centerX, centerY, centerZ), r(radius)
{
	generateVertices();
	generateIndices();
}

const std::vector<Vertex>& Sphere::getVertices() const
{
	return vertices;
}

const std::vector<unsigned int>& Sphere::getIndices() const
{
	return indices;
}

void Sphere::Draw(ID3D11DeviceContext* pContext)
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pContext->DrawIndexed(indices.size(), 0, 0);
}

#include <random>

void Sphere::generateVertices()
{
    // 위도, 경도 분할 수
    latitudeSegments = static_cast<int>(20 * r);
    longitudeSegments = static_cast<int>(20 * r);

    // 렌덤 디바이스 생성
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);

    // 정점 생성
    for (int i = 0; i <= latitudeSegments; ++i) {
        double theta = i * DirectX::XM_PI / latitudeSegments; // 위도 각도
        for (int j = 0; j <= longitudeSegments; ++j) {
            double phi = j * 2 * DirectX::XM_PI / longitudeSegments; // 경도 각도

            float x = sin(theta) * cos(phi);
            float y = cos(theta);
            float z = sin(theta) * sin(phi);
            Vector3 position = Vector3(x, y, z);

            // 렌덤한 색상값 생성
            float r = dis(gen);
            float g = dis(gen);
            float b = dis(gen);
            Vector4 color(r, g, b, 1.0f);

            Vertex v(position, color);

            vertices.push_back(v);
        }
    }

    //버텍스 버퍼 생성
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof(Vertex) * vertices.size();
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA vertexBufferData = {};
    vertexBufferData.pSysMem = vertices.data();

    //버텍스 버퍼 생성
    HRESULT hr = m_pDevice->CreateBuffer(&bufferDesc, &vertexBufferData, &m_pVertexBuffer);
    if (FAILED(hr))
    {
        MessageBox(NULL, L"CreateBuffer Failed", L"Error", MB_OK);
    }
}

void Sphere::generateIndices()
{
	for (int i = 0; i < latitudeSegments; ++i) {
		for (int j = 0; j < longitudeSegments; ++j) {
			unsigned int first = (i * (longitudeSegments + 1)) + j;
			unsigned int second = first + latitudeSegments + 1;

			// 삼각형 1
			indices.push_back(first);
			indices.push_back(second);
			indices.push_back(first + 1);

			// 삼각형 2
			indices.push_back(second);
			indices.push_back(second + 1);
			indices.push_back(first + 1);
		}
	}

	//인덱스 버퍼 생성
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(unsigned int) * indices.size();
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA indexBufferData;
	ZeroMemory(&indexBufferData, sizeof(indexBufferData));
	indexBufferData.pSysMem = indices.data();

	//인덱스 버퍼 생성
	HRESULT hr = m_pDevice->CreateBuffer(&bufferDesc, &indexBufferData, &m_pIndexBuffer);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"CreateBuffer Failed", L"Error", MB_OK);
	}
}

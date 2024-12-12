#pragma once
class Mesh;
class Model
{
public:
	Model() = default;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	UINT stride = 0;
	UINT offset = 0;
	UINT numElements = 0;

	void createMeshBuffer(ID3D11Device* m_device, const Mesh* mesh) {
		stride = sizeof(Mesh::Vertex);
		numElements = static_cast<UINT>(mesh->faces().size() * 3);

		const size_t vertexSize = mesh->vertices().size() * sizeof(Mesh::Vertex);
		const size_t indexSize = mesh->faces().size() * sizeof(Mesh::Face);
		{
			D3D11_BUFFER_DESC desc = {};
			desc.ByteWidth = (UINT)vertexSize;
			desc.Usage = D3D11_USAGE_IMMUTABLE;
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

			D3D11_SUBRESOURCE_DATA data = {};
			data.pSysMem = &mesh->vertices()[0];
			if (FAILED(m_device->CreateBuffer(&desc, &data, &m_pVertexBuffer))) {
				throw std::runtime_error("Failed to create vertex buffer");
			}
		}
		{
			D3D11_BUFFER_DESC desc = {};
			desc.ByteWidth = (UINT)indexSize;
			desc.Usage = D3D11_USAGE_IMMUTABLE;
			desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

			D3D11_SUBRESOURCE_DATA data = {};
			data.pSysMem = &mesh->faces()[0];
			if (FAILED(m_device->CreateBuffer(&desc, &data, &m_pIndexBuffer))) {
				throw std::runtime_error("Failed to create vertex buffer");
			}
		}
	}
};


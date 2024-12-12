#include "framework.h"
#include <DirectXMath.h>
#include <directxtk/simplemath.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

Mesh* Mesh::fromFile(const std::string& filename)
{
	Mesh* mesh;
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filename, ImportFlags);
	if (scene && scene->HasMeshes()) {
		mesh = new Mesh{ scene->mMeshes[0] };
	}
	else {
		throw std::runtime_error("Failed to load mesh file: " + filename);
	}
	return mesh;
}

Mesh* Mesh::fromString(const std::string& data)
{
	Mesh* mesh;
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFileFromMemory(data.c_str(), data.length(), ImportFlags, "nff");
	if (scene && scene->HasMeshes()) {
		mesh = new Mesh{ scene->mMeshes[0] };
	}
	else {
		throw std::runtime_error("Failed to create mesh from string: " + data);
	}
	return mesh;
}

Mesh::Mesh(const aiMesh* mesh)
{
	assert(mesh->HasPositions());
	assert(mesh->HasNormals());

	m_vertices.reserve(mesh->mNumVertices);
	for (size_t i = 0; i < m_vertices.capacity(); ++i) {
		Vertex vertex;
		vertex.position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
		vertex.normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
		if (mesh->HasTangentsAndBitangents()) {
			vertex.tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };
			vertex.bitangent = { mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z };
		}
		if (mesh->HasTextureCoords(0)) {
			vertex.texcoord = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
		}
		m_vertices.push_back(vertex);
	}

	m_faces.reserve(mesh->mNumFaces);
	for (size_t i = 0; i < m_faces.capacity(); ++i) {
		assert(mesh->mFaces[i].mNumIndices == 3);
		m_faces.push_back({ mesh->mFaces[i].mIndices[0], mesh->mFaces[i].mIndices[1], mesh->mFaces[i].mIndices[2] });
	}
}

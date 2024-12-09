#pragma once
const unsigned int ImportFlags =
aiProcess_CalcTangentSpace |
aiProcess_Triangulate |
aiProcess_SortByPType |
aiProcess_PreTransformVertices |
aiProcess_GenNormals |
aiProcess_GenUVCoords |
aiProcess_OptimizeMeshes |
aiProcess_Debone |
aiProcess_ValidateDataStructure;

class Mesh
{
public:

	struct Vertex
	{
		Vector3 position;
		Vector3 normal;
		Vector3 tangent;
		Vector3 bitangent;
		Vector2 texcoord;
	};
	static_assert(sizeof(Vertex) == 14 * sizeof(float));
	static const int NumAttributes = 5;

	struct Face
	{
		uint32_t v1, v2, v3;
	};
	static_assert(sizeof(Face) == 3 * sizeof(uint32_t));

	//static std::shared_ptr<Mesh> fromFile(const std::string& filename);
	static Mesh* fromFile(const std::string& filename);
	//static std::shared_ptr<Mesh> fromString(const std::string& data);
	static Mesh* fromString(const std::string& data);

	const std::vector<Vertex>& vertices() const { return m_vertices; }
	const std::vector<Face>& faces() const { return m_faces; }
private:
	Mesh(const struct aiMesh* mesh);

	std::vector<Vertex> m_vertices;
	std::vector<Face> m_faces;
};


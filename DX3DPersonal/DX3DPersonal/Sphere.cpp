#include "Sphere.h"

Sphere::Sphere(Vector3 center, float radius)
	:center(center), r(radius)
{
	generateVertices();
	generateIndices();
}


Sphere::Sphere(float centerX, float centerY, float centerZ, float radius)
	: center(centerX, centerY, centerZ), r(radius)
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

void Sphere::generateVertices()
{
	latitudeSegments = static_cast<int>(5 * r);
	longitudeSegments = static_cast<int>(10 * r);

	
	for (int i = 0; i <= latitudeSegments; ++i) {
		double theta = i * DirectX::XM_PI / latitudeSegments; // 위도 각도
		for (int j = 0; j <= longitudeSegments; ++j) {
			double phi = j * 2 * DirectX::XM_PI / longitudeSegments; // 경도 각도

			float x = sin(theta) * cos(phi);
			float y = cos(theta);
			float z = sin(theta) * sin(phi);
			Vertex v(x, y, z);

			vertices.push_back(v);
		}
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
}

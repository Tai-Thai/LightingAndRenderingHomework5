#include "RasterizationScene.h"
#include "Rasterization.h"
#include "ImageUtils.h"
#include "Window.h"
#include "Camera.h"
#include "Time.h"
#include "Mesh.h"

std::vector<Vector3> VerticesFromIndices(std::vector<Vector3> unique_vertices, std::vector<uint16_t> indices);

void RasterizationScene::OnLoad()
{
}

void RasterizationScene::OnUnload()
{
}

void RasterizationScene::OnUpdate(float dt)
{
	float tt = TotalTime();
	Matrix world = RotateY(100.0f * tt * DEG2RAD) * Translate(0.0f, 0.0f, 8.0f);//5.0f + sinf(tt) * 3.0f);
	Matrix view = LookAt({ 0.0f, 0.0f, 10.0f }, V3_ZERO, V3_UP);
	Matrix proj = Perspective(90.0f * DEG2RAD, 1.0f, 0.1f, 100.0f);
	Matrix mvp = world * view * proj;
	printf("Helloe");

	Image* img = &gImageCPU;
	Mesh mesh = gMeshSphere;
	ClearColor(img, BLACK);
	ClearDepth(img, 1.0f); // 0.0f = nearest to camera, 1.0f = furthest to camera
	DrawMesh(img, gMeshSphere, world, mvp);
}

std::vector<Vector3> VerticesFromIndices(std::vector<Vector3> unique_vertices, std::vector<uint16_t> indices)
{
	std::vector<Vector3> positions;
	positions.resize(indices.size());

	for (int i = 0; i < positions.size(); i++)
		positions[i] = unique_vertices[indices[i]];

	return positions;
}

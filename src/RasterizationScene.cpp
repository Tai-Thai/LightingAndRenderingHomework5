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

static const int PLANET_COUNT = 9;

static float planetRadius[PLANET_COUNT] =
{
	2.0f, 0.3f, 0.5f, 0.55f, 0.4f, 1.0f, 0.9f, 0.6f, 0.6f
};

static Vector3 planetBasePos[PLANET_COUNT] =
{
	{0,0,0},
	{3,0,0},
	{5,0,0},
	{7,0,0},
	{9,0,0},
	{12,0,0},
	{15,0,0},
	{18,0,0},
	{21,0,0}
};

static float orbitSpeed[PLANET_COUNT] =
{
	0.0f, 1.2f, 0.8f, 1.0f, 1.4f, 0.5f, 0.4f, 0.3f, 0.2f
};

static float selfRotationSpeed[PLANET_COUNT] =
{
	0.5f, 1.0f, 2.0f, 1.5f, 1.2f, 0.8f, 1.1f, 1.3f, 1.4f
};

void RasterizationScene::OnUpdate(float dt)
{
    float tt = TotalTime();

    Image* img = &gImageCPU;

    ClearColor(img, BLACK);
    ClearDepth(img, 1.0f);

    Mesh sphere = gMeshSphere;

    Matrix view = LookAt({ 0, 10, 25 }, { 0,0,0 }, V3_UP);
    Matrix proj = Perspective(90 * DEG2RAD, 1.0f, 0.1f, 200.0f);

    for (int i = 0; i < PLANET_COUNT; i++)
    {
        Matrix scale = Scale(planetRadius[i], planetRadius[i], planetRadius[i]);


        Matrix selfRot = RotateY(tt * selfRotationSpeed[i]);

        Matrix orbitRot = RotateZ(tt * orbitSpeed[i]);

        Matrix translation = Translate(planetBasePos[i]);

        Matrix world = scale * selfRot * translation * orbitRot;

        Matrix mvp = world * view * proj;

        DrawMesh(img, sphere, world, mvp);
    }
}

std::vector<Vector3> VerticesFromIndices(std::vector<Vector3> unique_vertices, std::vector<uint16_t> indices)
{
	std::vector<Vector3> positions;
	positions.resize(indices.size());

	for (int i = 0; i < positions.size(); i++)
		positions[i] = unique_vertices[indices[i]];

	return positions;
}

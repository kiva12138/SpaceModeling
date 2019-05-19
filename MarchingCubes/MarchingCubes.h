#pragma once

#include "Mesh3D.h"

struct  PPoint {
	double x;
	double y;
	double z;
	double value;
};


class MarchingCubes
{

private:
	Mesh3D* m_pmesh;

public:
	MarchingCubes(Mesh3D* _mesh)
		:m_pmesh(_mesh)
	{
	}

	double MarchingCubes::function(double x, double y, double z);

	PPoint MarchingCubes::interpolate(double isoValue, PPoint P1, PPoint P2);

	Mesh3D* Do_Marching_Cubes();

};

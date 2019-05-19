#pragma once

#include "Mesh3D.h"

const float TWOPI = 6.283185307179586476925286766559f;

class MeshSubdivision
{

private:
	Mesh3D* m_pmesh;

public:
	MeshSubdivision(Mesh3D* _mesh)
		:m_pmesh(_mesh)
	{
	}
	
	Mesh3D* Doo_Sabin();

	Mesh3D* Catmull_Clark();
	
};

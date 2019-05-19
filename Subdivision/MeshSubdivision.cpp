#include "StdAfx.h"
#include ".\meshsubdivision.h"


//--------------------------------------------------------------
#define PI 3.1415926536
#include <vector>

Mesh3D* MeshSubdivision::Doo_Sabin()
{
	if (m_pmesh==NULL) {
		return NULL;
	}

	Mesh3D* New_mesh = new Mesh3D;


	////////////////////////////////////////////////

	//your implmentation
	//New_mesh:  subdivisioned mesh
	//m_pmesh:  original mesh

	// insert all vertex

	//==================
	// YOUR CODE 
	//=================

	PTR_FACE_LIST face_list = m_pmesh->get_faces_list();
	FACE_ITER fiter = face_list->begin();


	std::vector<int> vert_id_list;
	vert_id_list.assign(m_pmesh->get_num_of_edges_list(), 0);

	// for each face, compute new vertex, insert vertex
	// and insert F-faces 
	// save the id of these newly inserted vertex , so they can
	// be acquired using the face and vertex

	//=================
	// YOUR CODE
	//=================

	for (; fiter != face_list->end(); fiter++) {
		int n = (*fiter)->valence;
		HE_edge * anchor_edge = (*fiter)->edge;
		HE_edge * temp_edge;
		VERTEX_LIST v_list;
		float new_x = 0, new_y = 0, new_z = 0;
		do {
			temp_edge = anchor_edge;
			new_x = 0; new_y = 0; new_z = 0;
			for (int i = 0; i < n; i++) {
				if (i == 0) {
					new_x += ((n + 5) / (4)) * temp_edge->vert->x;
					new_y += ((n + 5) / (4)) * temp_edge->vert->y;
					new_z += ((n + 5) / (4)) * temp_edge->vert->z;
				}
				else {
					new_x += ((3 + 2 * cos((2 * PI * i) / n)) / (4 * n)) * temp_edge->vert->x;
					new_y += ((3 + 2 * cos((2 * PI * i) / n)) / (4 * n)) * temp_edge->vert->y;
					new_z += ((3 + 2 * cos((2 * PI * i) / n)) / (4 * n)) * temp_edge->vert->z;
				}
				temp_edge = temp_edge->next;
			}
			HE_vert *vv = New_mesh->insert_vertex(new_x, new_y, new_z);
			vert_id_list[anchor_edge->id] = vv->id;
			v_list.push_back(vv);
			anchor_edge = anchor_edge->next;
		} while (anchor_edge != (*fiter)->edge);

		New_mesh->insert_face(v_list);
	}

	//
	//search all vertex, construct V-faces 
	//

	//===============
	// YOUR CODE
	//===============

	PTR_VERTEX_LIST vert_list = m_pmesh->get_vertices_list();
	VERTEX_ITER viter = vert_list->begin();
	for (; viter != vert_list->end(); viter++)
	{ 
		VERTEX_LIST v_list;
		HE_edge * edge = (*viter)->edge;
		HE_edge * t_edge = NULL;
		HE_vert * vert = NULL;
		do{
			t_edge = edge;
			do { t_edge = t_edge->next; } while (t_edge->next != edge);
			vert = New_mesh->get_vertex(vert_id_list[t_edge->id]);
			v_list.push_back(vert);
			edge = t_edge->pair;
		} while (edge != (*viter)->edge);

		New_mesh->insert_face(v_list);
	}



	//
	// search all edges, to build E-faces
	//

	//======================
	//  YOUR CODE
	//======================

	PTR_EDGE_LIST edge_list = m_pmesh->get_edges_list();
	EDGE_ITER eiter = edge_list->begin();
	for (; eiter != edge_list->end(); eiter++) {
		if ((*eiter)->pair->tag)
			continue;
		else
			(*eiter)->tag = true;

		VERTEX_LIST v_list;
		HE_vert * vert;
		HE_edge * edge = (*eiter);
		vert = New_mesh->get_vertex(vert_id_list[edge->id]);
		v_list.push_back(vert);

		do {
			edge = edge->next;
		} while (edge->next != (*eiter));
		vert = New_mesh->get_vertex(vert_id_list[edge->id]);
		v_list.push_back(vert);

		edge = edge->next->pair;
		vert = New_mesh->get_vertex(vert_id_list[edge->id]);
		v_list.push_back(vert);

		do {
			edge = edge->next;
		} while (edge->next != (*eiter)->pair);
		vert = New_mesh->get_vertex(vert_id_list[edge->id]);
		v_list.push_back(vert);

		New_mesh->insert_face(v_list);
	}

	/////////////////////////////////////////////////

	New_mesh->update_mesh();

	delete m_pmesh;
	m_pmesh = NULL;
	return New_mesh;


} 

//--------------------------------------------------------------

Mesh3D* MeshSubdivision::Catmull_Clark()
{

	if (m_pmesh==NULL) {
		return NULL;
	}

	

}	

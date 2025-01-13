#ifndef _pgl_mesh
#define _pgl_mesh 

#include<iostream>
#include<string>
#include<map>
#include<Importer.hpp>
#include<scene.h>
#include<postprocess.h>
#include<vector>

#include "pgl_maths.h"
#include "pgl_texture.h"

class Mesh
{
public:

	Mesh();
	
	~Mesh();

	bool LoadMesh(const std::string& fileName);

	void Render();
private:

	bool InitFromScene(const aiScene* pScene, const std::string& fileName);
	void InitMesh(unsigned int Index, const aiMesh* pMesh);
	bool InitMaterials(const aiScene* pScene, const std::string& fileName);
	void Clear();

#define INVALID_MATERIAL 0xFFFFFFFF

	struct Vertex
	{
		Vector3f m_pos;
		Vector2f m_tex;
		Vector3f m_normal;
		Vector3f m_tangent;

		Vertex() {}

		Vertex(const Vector3f& pos, const Vector2f& tex, const Vector3f& normal, const Vector3f& Tangent)
		{
			m_pos    = pos;
			m_tex    = tex;
			m_normal = normal;
			m_tangent = Tangent;
		}
	};


	struct MeshEntry
	{
		MeshEntry();
		~MeshEntry();

		bool Init(const std::vector<Vertex>& Vertices, const std::vector<unsigned int>& Indices);

		GLuint VB;
		GLuint IB;
		unsigned int NumIndices;
		unsigned int MaterialIndex;
	};

	std::vector<MeshEntry> m_Entries;
	std::vector<Texture*> m_textures;
};

#endif
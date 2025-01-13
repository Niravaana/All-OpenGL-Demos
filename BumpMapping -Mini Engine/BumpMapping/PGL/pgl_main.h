#ifndef _PglMain
#define _PglMain 


#include <iostream>
#include <string>
#include <assert.h>
#include "pgl_maths.h"
#include "pgl_texture.h"
#include "pgl_camera.h"
#include "pgl_transformations.h"
#include "pgl_oglkeys.h"
#include "pgl_utility.h"
#include "pgl_techniques.h"
#include "pgl_lighting_technique.h"
#include "pgl_glut_callback.h"
#include "pgl_ogl.h"
#include "pgl_ogltypes.h"
#include "pgl_mesh.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;

#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1200

struct Vertex
{
    Vector3f m_pos;
    Vector2f m_tex;
	Vector3f m_normal;

    Vertex() {}

    Vertex(Vector3f pos, Vector2f tex)
    {
        m_pos = pos;
        m_tex = tex;
		m_normal = Vector3f(0.0f,0.0f,0.0f);
    }
};

#endif 

#ifndef _Pgl_Techniques
#define _Pgl_Techniques

#include "pgl_utility.h"
#include "pgl_transformations.h"
#include <list>
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;

class Techniques
{
	public:

    Techniques();

    virtual ~Techniques();

    virtual bool Init();
	virtual void render(Pipeline& p)=0;
    void Enable();

protected:

    bool AddShader(GLenum ShaderType, const char* pFilename);

    bool Finalize();

    GLint GetUniformLocation(const char* pUniformName);
    
    GLint GetProgramParam(GLint param);
    
    GLuint m_shaderProg;    
    
private:

    typedef std::list<GLuint> ShaderObjList;
    ShaderObjList m_shaderObjList;
};

#endif
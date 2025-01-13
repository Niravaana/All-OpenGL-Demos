#ifndef _Pgl_Glut_Ogl
#define	_Pgl_Glut_Ogl

#include "pgl_ogltypes.h"
#include "pgl_glut_callback.h"


void GLUTBackendInit(int argc, char** argv, bool WithDepth, bool WithStencil);


bool GLUTBackendCreateWindow(uint Width, uint Height, bool isFullScreen, const char* pTitle);

void GLUTBackendRun(ICallbacks* pCallbacks);

void GLUTBackendSwapBuffers();

void GLUTBackendLeaveMainLoop();

OGLDEV_KEY GLUTKeyToOGLDEVKey(uint Key);

#endif	/* GLUT_BACKEND_H */
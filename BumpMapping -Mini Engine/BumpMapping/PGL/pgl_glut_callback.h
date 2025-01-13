#ifndef _Pgl_Glut_Callback
#define _Pgl_Glut_Callback

#include "pgl_ogltypes.h"
#include "pgl_oglkeys.h"

class ICallbacks
{
public:

    virtual void KeyboardCB(OGLDEV_KEY OgldevKey) {};

    virtual void PassiveMouseCB(int x, int y) {};

    virtual void RenderSceneCB() {};

    virtual void MouseCB(OGLDEV_MOUSE Button, OGLDEV_KEY_STATE State, int x, int y) {};

	virtual void SpecialKeyboardCB(int Key, int x, int y){};

};

#endif
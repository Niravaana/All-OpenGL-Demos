#include <math.h>
#include "pgl_main.h"

class BlueRenderer : public ICallbacks
{
public:

    BlueRenderer()
    {
        m_pGameCamera = NULL;
        m_pEffect = NULL;
        m_scale = 0.0f;
		m_pMesh = NULL;
		m_pTexture = NULL;
		m_pNormalMap = NULL;
		m_pTrivialNromalMap = NULL;
        
        m_persProjInfo.FOV = 60.0f;
        m_persProjInfo.Height = WINDOW_HEIGHT;
        m_persProjInfo.Width = WINDOW_WIDTH;
        m_persProjInfo.zNear = 1.0f;
        m_persProjInfo.zFar = 15000.0f;

		m_bumpMapEnabled = true;
    }

    ~BlueRenderer()
    {
		SAFE_DELETE(m_pEffect);
		SAFE_DELETE(m_pGameCamera);
		SAFE_DELETE(m_pMesh);
		SAFE_DELETE(m_pTexture);
		SAFE_DELETE(m_pNormalMap);
		SAFE_DELETE(m_pTrivialNromalMap);
    }

    bool Init()
    {
          
		m_pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);

        m_pEffect = new LightingTechnique();

        if (!m_pEffect->Init())
        {
			printf("Error Initializing The Lighting!!!!\n");
            return false;
        }

       m_pEffect->Enable();
	   m_pEffect->SetColorTextureUnit(0);
	   m_pEffect->SetNormalMapTextureUnit(2);
       
	   m_pMesh = new Mesh();
	   if(!m_pMesh->LoadMesh("../Content/crytek_sponza/sponza.obj"))
	   {
		   printf("Error Initializing Mesh!!!!\n");
           return false;
	   }

	   m_pTexture = new Texture(GL_TEXTURE_2D,"../Content/bricks.jpg");
	   if(!m_pTexture->Load())
	   {
		   printf("Error Initializing Texture!!!!\n");
           return false;
	   }
	 
	   m_pNormalMap = new Texture(GL_TEXTURE_2D, "../Content/bricks_NRM.jpg");
	   if(!m_pNormalMap->Load())
	   {
		   printf("Error Initializing Normal Texture!!!!\n");
           return false;
	   }

	   m_pTrivialNromalMap = new Texture(GL_TEXTURE_2D, "../Content/normal_up.jpg");
        
        if (!m_pTrivialNromalMap->Load()) {
            return false;
        }

        return true;
    }

	virtual void SpecialKeyboardCB(int Key, int x, int y)
	{
		OGLDEV_KEY OgldevKey = GLUTKeyToOGLDEVKey(Key);
		m_pGameCamera->OnKeyboard(OgldevKey);
	}

    void Run()
    {
        GLUTBackendRun(this);
    }

    virtual void RenderSceneCB()
    {
       
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
        m_scale += 0.1f;

        Pipeline p;
		p.Rotate(0.0f, m_scale, 0.0f);
		p.Scale(3.0,3.0,3.0);
        p.WorldPos(1.0f, 5.0f, 1.0f);
        p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
        p.SetPerspectiveProj(m_persProjInfo);
       
		m_pTexture->Bind(COLOR_TEXTURE_UNIT);

		if(m_bumpMapEnabled)
		{
			m_pNormalMap->Bind(NORMAL_TEXTURE_UNIT);
		}
		else
		{
			m_pTrivialNromalMap->Bind(NORMAL_TEXTURE_UNIT);
		}

		m_pEffect->render(p);

		m_pMesh->Render();

        glutSwapBuffers();
    }

    virtual void KeyboardCB(OGLDEV_KEY OgldevKey)
    {
        switch (OgldevKey) {
            case OGLDEV_KEY_ESCAPE:
            case OGLDEV_KEY_q:
                    GLUTBackendLeaveMainLoop();
                    break;

            case OGLDEV_KEY_a:
				m_pEffect->UpdateDirectionalLight(0.05f,0.05f);
                break;

            case OGLDEV_KEY_s:
				m_pEffect->UpdateDirectionalLight(-0.05,-0.05);
                break;
        }
    }
	    

private:
	void CalculateNormals(const unsigned int* pIndices,unsigned int indexCount, Vertex *pVertex, unsigned int vertexCount)
	{
		for( unsigned int i = 0; i < indexCount; i +=3)
		{
			unsigned int Index0 = pIndices[i];
			unsigned int Index1 = pIndices[i+1];
			unsigned int Index2 = pIndices[i+2];

			Vector3f v1 = pVertex[Index1].m_pos - pVertex[Index0].m_pos;
			Vector3f v2 = pVertex[Index2].m_pos - pVertex[Index0].m_pos;

			Vector3f Normal = v1.Cross(v2);
			Normal.Normalize();

			pVertex[Index0].m_normal += Normal;
			pVertex[Index1].m_normal += Normal;
			pVertex[Index2].m_normal += Normal;
		}

		// Normalize all the vertex normals
		for (unsigned int i = 0 ; i < vertexCount ; i++) 
		{
			pVertex[i].m_normal.Normalize();
		}
	}


  
    LightingTechnique* m_pEffect;
    Camera* m_pGameCamera;
    float m_scale;
	Mesh* m_pMesh;
    PersProjInfo m_persProjInfo;
	bool m_bumpMapEnabled;
	Texture *m_pTexture;
	Texture *m_pNormalMap;
	Texture *m_pTrivialNromalMap;

};


int main(int argc, char** argv)
{
    GLUTBackendInit(argc, argv, true, false);

    if (!GLUTBackendCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false, "PGL 1.0")) {
        return 1;
    }

    BlueRenderer* pApp = new BlueRenderer();

    if (!pApp->Init()) {
        return 1;
    }

    pApp->Run();

    delete pApp;
 
    return 0;
}

#ifndef LIGHTING_TECHNIQUE_H
#define	LIGHTING_TECHNIQUE_H

#include "pgl_techniques.h"
#include "pgl_maths.h"


struct BaseLight
{
	 Vector3f Color;
	 float AmbientIntensity;
	 float DiffuseIntensity;

	 BaseLight()
	 {
		Color = Vector3f(0.0f, 0.0f, 0.0f);
        AmbientIntensity = 0.0f;
        DiffuseIntensity = 0.0f;
	 }
};

struct DirectionalLight : public BaseLight
{
    
	Vector3f Direction;
	DirectionalLight()
	{
		Direction = Vector3f(0.0f, 0.0f, 0.0f);
	}
	
};

struct PointLight : public BaseLight
{
	Vector3f Position;

    struct
    {
        float Constant;
        float Linear;
        float Exp;
    } Attenuation;

    PointLight()
    {
        Position = Vector3f(0.0f, 0.0f, 0.0f);
        Attenuation.Constant = 1.0f;
        Attenuation.Linear = 0.0f;
        Attenuation.Exp = 0.0f;
    }
};

class LightingTechnique : public Techniques
{
public:

    LightingTechnique();

    virtual bool Init();
	virtual void render(Pipeline& p);

    void SetWVP(const Matrix4f& WVP);
	void SetColorTextureUnit(unsigned int TextureUnit);
	void SetNormalMapTextureUnit(unsigned int TextureUnit);
    void SetDirectionalLight( DirectionalLight& Light);
	void UpdateDirectionalLight(float AmbientIntensity, float DiffuseIntensity);
	void SetWorldMatrixLocation(const Matrix4f& WV);
	void SetEyeWolrdPos(const Vector3f& EyeWorldPos);
	void SetMatSpecularPower(float power);
	void SetMatSpecularIntensity(float intensity );
	void SetPointLights(unsigned int NumLights, const PointLight* pLights);
	void InitializePointLights();

private:

	static const unsigned int MAX_POINT_LIGHTS = 2;

    GLuint m_WVPLocation;
    GLuint m_WorldMatrixLocation;
	GLuint m_eyeWorldPosLocation;
	GLuint m_numPointLightsLocation;
	GLuint m_colorMapLocation;
	GLuint m_normalMapLocation;

	DirectionalLight m_directionalLight;
	PointLight m_pointLights[MAX_POINT_LIGHTS];

	struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint Direction;
        GLuint DiffuseIntensity;
		GLuint SpecularIntesity;
		GLuint SpecularPower;
    } m_dirLightLocation;

	struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Position;
        struct
        {
            GLuint Constant;
            GLuint Linear;
            GLuint Exp;
        } Atten;
    } m_pointLightsLocation[MAX_POINT_LIGHTS];
};

#endif
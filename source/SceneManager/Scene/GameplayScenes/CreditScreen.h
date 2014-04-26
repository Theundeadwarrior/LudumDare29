#ifndef SCENEMANAGER_CREDITSCREEN_H
#define SCENEMANAGER_CREDITSCREEN_H

#include "SceneManager/Scene/Scene.h"
#include "SceneManager/Manager/TypedefID.h"

namespace Atum
{
namespace SceneManager
{
    
class CreditScreen : public Scene
{
public:
    CreditScreen();
    ~CreditScreen();

	virtual void Init();
	virtual void Uninit();

    void LoadShader();
    void LoadTexture();
	void LoadQuad();
	void LoadMaterial();

    void UnloadShader();
    void UnloadTexture();
	void UnloadQuad();
	void UnloadMaterial();

	void CreateTitleScreenObject();

	void RemoveTitleScreenObject();

private:
	ShaderListID m_alphaTexturedQuadShaderID;
	TextureId m_titleScreenTextureID;
	GeometryID m_titleScreenQuadID;
	MaterialID m_titleScreenMaterialID;

	Object* m_titleScreenObject;
	Camera* m_dummyCamera;
};

} // namespace SceneManager
} // namespace Atum


#endif

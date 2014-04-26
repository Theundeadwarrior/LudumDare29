#ifndef SCENEMANAGER_TITLESCREEN_H
#define SCENEMANAGER_TITLESCREEN_H

#include "SceneManager/Scene/Scene.h"
#include "SceneManager/Manager/TypedefID.h"

namespace Atum
{
namespace SceneManager
{
    
class TitleScreen : public Scene
{
public:
    TitleScreen();
    ~TitleScreen();

	virtual void Init();
	virtual void Uninit();

    static ShaderListID GetShader();
    static TextureId GetTexture();
	static GeometryID GetQuad();
	static MaterialID GetMaterial();

    void UnloadShader();
	void UnloadQuad();

	void CreateTitleScreenObject();

	void RemoveTitleScreenObject();

private:
	Object* m_titleScreenObject;
	Camera* m_dummyCamera;
};

} // namespace SceneManager
} // namespace Atum


#endif

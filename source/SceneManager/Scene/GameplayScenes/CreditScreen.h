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

	static TextureId GetTexture();
	static MaterialID GetMaterial();

	void CreateTitleScreenObject();

	void RemoveTitleScreenObject();

private:
	Object* m_titleScreenObject;
	Camera* m_dummyCamera;
};

} // namespace SceneManager
} // namespace Atum


#endif

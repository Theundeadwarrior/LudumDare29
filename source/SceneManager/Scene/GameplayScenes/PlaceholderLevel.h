#ifndef SCENEMANAGER_PLACEHOLDERLEVEL_H
#define SCENEMANAGER_PLACEHOLDERLEVEL_H

#include "SceneManager/Scene/Scene.h"
#include "SceneManager/Manager/TypedefID.h"

namespace Atum
{
namespace SceneManager
{
    
class PlaceholderLevel : public Scene
{
public:
    PlaceholderLevel();
    ~PlaceholderLevel();

	virtual void Init();
	virtual void Uninit();

	void CreateTitleScreenObject();

	void RemoveTitleScreenObject();

private:
	Object* m_titleScreenObject;
	Camera* m_dummyCamera;
};

} // namespace SceneManager
} // namespace Atum


#endif

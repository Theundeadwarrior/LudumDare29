#ifndef SCENEMANAGER_PLACEHOLDERLEVEL_H
#define SCENEMANAGER_PLACEHOLDERLEVEL_H

#include "SceneManager/Scene/Scene.h"
#include "SceneManager/Manager/TypedefID.h"
#include "SceneManager/Objects/GameplayObjects/MainCharacter.h"

namespace Atum
{
namespace SceneManager
{
 
class LevelLayout;

class PlaceholderLevel : public Scene
{
public:
    PlaceholderLevel();
	PlaceholderLevel(const LevelLayout& level);
	~PlaceholderLevel();

	virtual void Init();
	virtual void Uninit();

	void CreateTitleScreenObject();

	void RemoveTitleScreenObject();

private:
	glm::vec4 m_currentPosition; // used for scrolling

	MainCharacter* m_titleScreenObject;
	Camera* m_dummyCamera;

};

} // namespace SceneManager
} // namespace Atum


#endif

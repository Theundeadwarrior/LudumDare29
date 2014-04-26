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

class Level
{
public:
	Level();
	~Level();


private:
	glm::vec4 m_currentPosition; // used for scrolling
};

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
	MainCharacter* m_titleScreenObject;
	Camera* m_dummyCamera;
	Level m_currentLevel;
	Level m_nextLevel;
};

} // namespace SceneManager
} // namespace Atum


#endif

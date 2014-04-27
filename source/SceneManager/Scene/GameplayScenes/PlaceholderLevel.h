#ifndef SCENEMANAGER_PLACEHOLDERLEVEL_H
#define SCENEMANAGER_PLACEHOLDERLEVEL_H

#include "SceneManager/Scene/Scene.h"
#include "SceneManager/Manager/TypedefID.h"
#include "SceneManager/Objects/GameplayObjects/MainCharacter.h"

#include "SceneManager/Objects/GameplayObjects/Background.h"
#include "SceneManager/Objects/GameplayObjects/ForeGround.h"

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

	void Level::BuildObjectsFromLevelLayout();
	std::vector<Object*>::iterator GetObjectListBegin(){ return m_objectList.begin(); }
	std::vector<Object*>::iterator GetObjectListEnd(){ return m_objectList.end(); }


	glm::vec4& GetPosition() { return m_currentPosition;  }
	float GetLastPlatformYPosition();
	float GetFirstPlatformYPosition();
	void Translate(const glm::vec4& translation);

private:
	std::vector<Object*> m_objectList;

	glm::vec4 m_currentPosition; // used for scrolling.
};

class PlaceholderLevel : public Scene
{
public:
    PlaceholderLevel();
	PlaceholderLevel(const LevelLayout& level);
	~PlaceholderLevel();

	virtual void Init();

	void InitLevel(Level* level);

	virtual void Uninit();

	void CreateTitleScreenObject();

	void RemoveTitleScreenObject();

	virtual void Update();

private:
	MainCharacter* m_mainCharacter;
	Background* m_background;
	Foreground* m_foreground;
	Camera* m_dummyCamera;
	//std::list<Level*> m_levels; // levels that go from left to right
	Level* m_currentLevel;
	Level* m_nextLevel;

};

} // namespace SceneManager
} // namespace Atum


#endif

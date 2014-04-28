#ifndef SCENEMANAGER_PLACEHOLDERLEVEL_H
#define SCENEMANAGER_PLACEHOLDERLEVEL_H

#include "SceneManager/Scene/Scene.h"
#include "SceneManager/Manager/TypedefID.h"
#include "SceneManager/Objects/GameplayObjects/MainCharacter.h"

#include "SceneManager/Objects/GameplayObjects/Background.h"
#include "SceneManager/Objects/GameplayObjects/ForeGround.h"
#include "SceneManager/Objects/GameplayObjects/MovingBackground.h"

namespace Atum
{
namespace SceneManager
{
 
class LevelLayout;

class Level
{
public:
	Level(bool isUnderGround = false);
	~Level();

	void Level::BuildObjectsFromLevelLayout();
	std::vector<Object*>::iterator GetObjectListBegin(){ return m_objectList.begin(); }
	std::vector<Object*>::iterator GetObjectListEnd(){ return m_objectList.end(); }

	glm::vec4& GetPosition() { return m_currentPosition;  }
	float GetLastPlatformYPosition();
	float GetFirstPlatformYPosition();
	
	bool IsUnderGround() { return m_isUnderGround; }

	void Translate(const glm::vec4& translation);

private:
	std::vector<Object*> m_objectList;
	glm::vec4 m_currentPosition; // used for scrolling.
	bool m_isUnderGround;
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

	virtual void Update();


	void CreateTitleScreenObject();

private:
	void GoBeneathTheSurface();
	void ResetLevelsPosition();
	void InitParticleSystem();
private:
	MainCharacter* m_mainCharacter;
	Background* m_background;
	Foreground* m_foreground;
    MovingBackground* m_movingBackground;
	Camera* m_dummyCamera;
	Level* m_currentLevel;
	Level* m_nextLevel;
	bool m_switchMusic;

};

} // namespace SceneManager
} // namespace Atum


#endif

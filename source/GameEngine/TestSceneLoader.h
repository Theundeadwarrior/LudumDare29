#ifndef TEST_SCENE_LOADER_H
#define TEST_SCENE_LOADER_H

#include "Events/EventManager.h"
#include "SceneManager/SceneManager.h"

using namespace Atum;

class TestSceneLoader : public Events::InputKeyboardListener
{
public:
	TestSceneLoader(Atum::SceneManager::SceneManager & sceneManager);
	~TestSceneLoader();
	virtual void NotifyKeyPressed(const Events::KeyboardEvent& event);

private:
	SceneManager::SceneManager & m_sceneManager;
};

#endif
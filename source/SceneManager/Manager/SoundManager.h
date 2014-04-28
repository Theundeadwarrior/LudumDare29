#ifndef SCENEMANAGER_SOUND_MANAGER_H
#define SCENEMANAGER_SOUND_MANAGER_H

#include "irrKlang/include/irrKlang.h"

namespace Atum
{

namespace SceneManager
{

class SoundManager
{
public:
	enum MusicTransition
	{
		TitleToAbove,
		AboveToBelow,
		BelowToTitle
	};

	static SoundManager& GetInstance();
	~SoundManager();

	void StartMusic();
	bool IncrementSwitchMusic(MusicTransition transition, float transitionSpeed = 0.05f);
	void StopMusic();

private:
	SoundManager();
	SoundManager(SoundManager const&); //don't implement
	void operator=(SoundManager const&); //don't implement

	irrklang::ISoundEngine* m_engine;
	irrklang::ISound* m_currentMusicTitle;
    irrklang::ISound* m_currentMusicAbove;
	irrklang::ISound* m_currentMusicUnder;
};

}
}

#endif
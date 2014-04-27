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
	static SoundManager& GetInstance();
	~SoundManager();

	void StartMusic();
	bool IncrementSwitchMusic(bool underworld);
	void StopMusic();

private:
	SoundManager();
	SoundManager(SoundManager const&); //don't implement
	void operator=(SoundManager const&); //don't implement

	irrklang::ISoundEngine* m_engine;
    irrklang::ISound* m_currentMusic;
	irrklang::ISound* m_currentMusicUnder;
};

}
}

#endif
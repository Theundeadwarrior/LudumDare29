#include "SceneManager/Manager/SoundManager.h"
#include "windows.h"

#define THRESHOLD 0.99999f

namespace Atum
{
	namespace SceneManager
	{
		SoundManager::SoundManager()
			:m_currentMusicTitle(0x00000000)
			,m_currentMusicAbove(0x00000000)
			,m_currentMusicUnder(0x00000000)
		{
			m_engine = irrklang::createIrrKlangDevice();
		}
   
		SoundManager& SoundManager::GetInstance()
		{
			static SoundManager instance;
			return instance;
		}
		SoundManager::~SoundManager()
		{
			if(m_currentMusicTitle)
			{
				m_currentMusicTitle->stop();
				m_currentMusicTitle->drop();
			}
			if(m_currentMusicAbove)
			{
				m_currentMusicAbove->stop();
				m_currentMusicAbove->drop();
			}
			if(m_currentMusicUnder)
			{
				m_currentMusicUnder->stop();
				m_currentMusicUnder->drop();
			}
			m_engine->drop();
		} 

		void SoundManager::StartMusic()
		{	
			if(!m_currentMusicTitle)
			{
				m_currentMusicTitle = m_engine->play2D("../../data/sounds/TitleScreen.ogg", true, true, true, irrklang::ESM_AUTO_DETECT, true);
				m_currentMusicTitle->setPlayPosition(0.0f);
				m_currentMusicTitle->setVolume(1.0f);
				m_currentMusicTitle->setIsPaused(false);
			}
			if(!m_currentMusicAbove)
			{
				m_currentMusicAbove = m_engine->play2D("../../data/sounds/AboveTheSurface.ogg", true, true, true, irrklang::ESM_AUTO_DETECT, true);
				m_currentMusicAbove->setPlayPosition(0.0f);
				m_currentMusicAbove->setVolume(0.0f);
				m_currentMusicAbove->setIsPaused(false);
			}
			if(!m_currentMusicUnder)
			{
				m_currentMusicUnder = m_engine->play2D("../../data/sounds/BeneathTheSurface.ogg", true, true, true, irrklang::ESM_AUTO_DETECT, true);
				m_currentMusicUnder->setPlayPosition(0.0f);
				m_currentMusicUnder->setVolume(0.0f);
				m_currentMusicUnder->setIsPaused(false);
			}
		}

		bool SoundManager::IncrementSwitchMusic(MusicTransition transition, float transitionSpeed)
		{
			switch(transition)
			{
			case TitleToAbove:
				if(m_currentMusicAbove->getVolume() < THRESHOLD)
				{
					m_currentMusicTitle->setVolume(m_currentMusicTitle->getVolume()-transitionSpeed);
					m_currentMusicAbove->setVolume(m_currentMusicAbove->getVolume()+transitionSpeed);

					return true;
				}
				break;
			case AboveToBelow:
				if(m_currentMusicUnder->getVolume() < THRESHOLD)
				{
					m_currentMusicAbove->setVolume(m_currentMusicAbove->getVolume()-transitionSpeed);
					m_currentMusicUnder->setVolume(m_currentMusicUnder->getVolume()+transitionSpeed);

					return true;
				}
				break;
			case BelowToTitle:
				if(m_currentMusicTitle->getVolume() < THRESHOLD)
				{
					m_currentMusicUnder->setVolume(m_currentMusicUnder->getVolume()-transitionSpeed);
					m_currentMusicTitle->setVolume(m_currentMusicTitle->getVolume()+transitionSpeed);

					return true;
				}
				break;
			}

			return false;
		}

		void SoundManager::StopMusic()
		{	
			while(SoundManager::GetInstance().IncrementSwitchMusic(SoundManager::BelowToTitle,0.005f))
			{
				Sleep(1);
			}
		}

	}
}

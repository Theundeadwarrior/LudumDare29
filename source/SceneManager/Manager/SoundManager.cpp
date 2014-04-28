#include "SceneManager/Manager/SoundManager.h"
#include "windows.h"

namespace Atum
{
	namespace SceneManager
	{
		SoundManager::SoundManager()
			:m_currentMusic(0x00000000)
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
			if(m_currentMusic)
			{
				m_currentMusic->drop();
			}
			if(m_currentMusicUnder)
			{
				m_currentMusicUnder->drop();
			}
			m_engine->drop();
		} 

		void SoundManager::StartMusic()
		{	
			if(!m_currentMusic)
			{
				m_currentMusic = m_engine->play2D("../../data/sounds/AboveTheSurface.ogg", true, false, true, irrklang::ESM_AUTO_DETECT, true);
			}
			if(!m_currentMusicUnder)
			{
				m_currentMusicUnder = m_engine->play2D("../../data/sounds/BeneathTheSurface.ogg", true, false, true, irrklang::ESM_AUTO_DETECT, true);
			}
			m_currentMusicUnder->setPlayPosition(0.0f);
			m_currentMusicUnder->setVolume(0.0f);
			m_currentMusicUnder->setIsPaused(false);
			m_currentMusic->setPlayPosition(0.0f);
			m_currentMusic->setVolume(1.0f);
			m_currentMusic->setIsPaused(false);
		}

		bool SoundManager::IncrementSwitchMusic(bool underworld)
		{
			if(underworld && m_currentMusicUnder->getVolume() < 0.99f)
			{
				m_currentMusic->setVolume(m_currentMusic->getVolume()-0.025f);
				m_currentMusicUnder->setVolume(m_currentMusicUnder->getVolume()+0.025f);
				return true;
			}
			else if(!underworld && m_currentMusic->getVolume() < 0.99f)
			{
				m_currentMusic->setVolume(m_currentMusic->getVolume()+0.025f);
				m_currentMusicUnder->setVolume(m_currentMusicUnder->getVolume()-0.025f);
				return true;
			}
			return false;
		}

		void SoundManager::StopMusic()
		{	
			if(m_currentMusic)
			{
				m_currentMusic->setIsPaused(true);
			}
			if(m_currentMusicUnder)
			{
				m_currentMusicUnder->setIsPaused(true);
			}
		}

	}
}

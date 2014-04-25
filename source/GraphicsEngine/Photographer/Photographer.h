#ifndef GRAPHICSENGINE_PHOTOGRAPHER_H
#define GRAPHICSENGINE_PHOTOGRAPHER_H
  
namespace Atum { namespace SceneManager { class Scene; } }

namespace Atum
{
namespace GraphicsEngine
{
	class Photographer
	{
	public:
		Photographer():m_isScreenShotRequested(false), m_lastScreenShotTaken(0){}
		~Photographer(){if(m_lastScreenShotTaken){delete m_lastScreenShotTaken;}}
		void RequestScreenShot(){m_isScreenShotRequested = true;}
		bool IsScreenShotRequested(){return m_isScreenShotRequested;}
		void TakeScreenShot();
		unsigned char* GetLastScreenShot(){return m_lastScreenShotTaken;}
	private:
		bool m_isScreenShotRequested;
		unsigned char* m_lastScreenShotTaken;
	};

}
}

#endif

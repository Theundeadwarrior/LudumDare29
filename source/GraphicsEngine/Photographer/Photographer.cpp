#include "GraphicsEngine/Photographer/Photographer.h"
#include "LowLevelGraphics/LowLevelAPI/GPUAPI/LowLevelGPUAPI.h"
#include "GraphicsEngine/GraphicsEngine.h"

namespace Atum
{

namespace GraphicsEngine
{
	void Photographer::TakeScreenShot()
	{
		if(m_lastScreenShotTaken)
		{
			delete m_lastScreenShotTaken;
		}
		m_lastScreenShotTaken = new unsigned char[3*DEFAULT_WINDOW_WIDTH*DEFAULT_WINDOW_HEIGHT];
		LowLevelGraphics::LowLevelAPI::GetRenderedData(m_lastScreenShotTaken,0,0,DEFAULT_WINDOW_WIDTH,DEFAULT_WINDOW_HEIGHT,LowLevelGraphics::LowLevelAPI::ATUM_RGB);
		m_isScreenShotRequested = false;
	}

}
}

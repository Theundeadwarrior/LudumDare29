#ifndef LOWLEVELGRAPHICS_WINDOWMANAGER_CPP
#define LOWLEVELGRAPHICS_WINDOWMANAGER_CPP

#include "LowLevelGraphics/WindowManager/WindowManager.h"

#include "LowLevelGraphics/Context/Context.h"
#include "LowLevelGraphics/LowLevelAPI/WindowAPI/LowLevelWindowAPI.h"

namespace Atum
{
namespace LowLevelGraphics
{

//-----------------------------------------------------------------------------
WindowManager::WindowManager()
{
}

//-----------------------------------------------------------------------------
WindowManager& WindowManager::GetInstance()
{
	static WindowManager instance;
	return instance;
}

//-----------------------------------------------------------------------------
void WindowManager::AddWindow(WindowParameters params)
{
    //Todo : support more than one window
	
	LowLevelAPI::AddWindow(params);
	LowLevelAPI::CreateNewContext();

    //m_contexts.push_back(Context(LowLevelAPI::CreateNewContext(),LowLevelAPI::AddWindow(params)));
}
//-----------------------------------------------------------------------------
void SetWindow(int contextId)
{
    LowLevelAPI::SetCurrentWindow(contextId);
}
//-----------------------------------------------------------------------------
int WindowManager::GetCurrentWindowId()
{
    return LowLevelAPI::GetCurrentWindowId();
}
//-----------------------------------------------------------------------------
Context& WindowManager::GetCurrentContext()
{
    //todiscuss and remove
    return m_contexts[0]; 
    //////////////////////
}

//-----------------------------------------------------------------------------
void WindowManager::ResizeWindow( int width, int height )
{
	LowLevelAPI::ResizeWindow(width, height);
}

//-----------------------------------------------------------------------------
void WindowManager::RepositionWindow( int x, int y )
{
	LowLevelAPI::RepositionWindow(x,y);
}

glm::uvec2 WindowManager::GetCurrentWindowSize()
{
	unsigned int wSizeX, wSizeY;
	LowLevelAPI::GetCurrentWindowSize(wSizeX, wSizeY);
	return glm::uvec2(wSizeX, wSizeY);
}

}
}

#endif

#ifndef LOWLEVELGRAPHICS_LOWLEVELAPI_WINDOWAPI_LOWLEVELWINDOWAPI_H
#define LOWLEVELGRAPHICS_LOWLEVELAPI_WINDOWAPI_LOWLEVELWINDOWAPI_H

namespace Atum
{
namespace LowLevelGraphics
{
struct WindowParameters;

namespace LowLevelAPI
{

int AddWindow(WindowParameters params);
void SetCurrentWindow(int contextId);
int GetCurrentWindowId();
void GetCurrentWindowSize( unsigned int& x, unsigned int& y );
void ResizeWindow(int width, int height);
void RepositionWindow(int x, int y);

}
}
}
#endif
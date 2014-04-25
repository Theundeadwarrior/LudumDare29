#ifndef LOWLEVELGRAPHICS_WINDOWMANAGER_H
#define LOWLEVELGRAPHICS_WINDOWMANAGER_H

#include <vector>
#include "GLM/include/glm/glm.hpp"

// If we want to have multiple windows, we could keep the same functions
// and add something like : setCurrentWindow.
// The windows ids could be stored in a vector (we get those Id's from
// the glutCreateWindow.
namespace Atum
{
namespace LowLevelGraphics
{
class Context;

struct WindowParameters
{
    WindowParameters(char* t, int w, int h, int ox, int oy)
        :title(t),
        width(w),
        height(h),
        x(ox),
        y(oy)
    {}

    char* title;
    int width;
    int height;
    int x;
    int y;
};

class WindowManager
{
public:
	static WindowManager& GetInstance();

	void AddWindow(WindowParameters params);
    void SetWindow(int contextId);
	void RepositionWindow(int x, int y);
	void ResizeWindow(int width, int height);
    int  GetCurrentWindowId();
    Context& GetCurrentContext();
	glm::uvec2 GetCurrentWindowSize();

private:
	WindowManager();
	WindowManager(WindowManager const&);
	void operator=(WindowManager const&);

private:
    std::vector<Context> m_contexts; //todo: delete contexts on delete window, manage rendering per window
};

}
}

#endif

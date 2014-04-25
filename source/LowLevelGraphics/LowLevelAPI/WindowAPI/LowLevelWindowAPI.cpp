#include "LowLevelGraphics/LowLevelAPI/WindowAPI/LowLevelWindowAPI.h"

#include "freeglut/include/GL/freeglut.h"
#include "LowLevelGraphics/WindowManager/WindowManager.h"
#include "Utilities/Debug/Debug.h"

namespace Atum
{
namespace LowLevelGraphics
{
namespace LowLevelAPI
{

//-----------------------------------------------------------------------------
void ResizeWindow(int width, int height)
{
    ATUM_ASSERT_MESSAGE(width > 0, "Width must be strictly positive");
    ATUM_ASSERT_MESSAGE(height > 0, "Height must be strictly positive");
    glutReshapeWindow(width, height);
}

//-----------------------------------------------------------------------------
void RepositionWindow(int x, int y)
{
    glutPositionWindow(x, y);
}

//-----------------------------------------------------------------------------
int GetCurrentWindowId()
{
    return glutGetWindow();
}

//-----------------------------------------------------------------------------
int AddWindow(WindowParameters params)
{
    ATUM_ASSERT_MESSAGE(params.width > 0, "Width must be strictly positive");
    ATUM_ASSERT_MESSAGE(params.height > 0, "Height must be strictly positive");

    //todo : support more options
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (params.width, params.height);
	glutInitWindowPosition (params.x, params.y);

    int windowID = glutCreateWindow(params.title);
    ATUM_ASSERT_MESSAGE(!glGetError(), "Failed to create a window");

    return windowID;
}
//-----------------------------------------------------------------------------
void SetCurrentWindow(int contextId)
{
    ATUM_ASSERT_MESSAGE(contextId, "Context ID must not be null");
    glutSetWindow(contextId);
    ATUM_ASSERT_MESSAGE(!glGetError(), "Context ID is refering to a nonexistent window");
}

void GetCurrentWindowSize( unsigned int& o_x, unsigned int& o_y )
{
	GLint m_viewport[4];
	glGetIntegerv( GL_VIEWPORT, m_viewport );
	o_x = m_viewport[2];
	o_y = m_viewport[3];
}

}
}
}
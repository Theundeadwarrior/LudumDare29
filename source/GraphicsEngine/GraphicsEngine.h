#ifndef GRAPHICSENGINE_GRAPHICSENGINE_H
#define GRAPHICSENGINE_GRAPHICSENGINE_H
  
#include "GraphicsEngine/Photographer/Photographer.h"

#define DEFAULT_WINDOW_WIDTH 1024
#define DEFAULT_WINDOW_HEIGHT 768

namespace Atum { namespace SceneManager { class Scene; } }

namespace Atum
{
namespace GraphicsEngine
{

//-----------------------------------------------------------------------------
class GraphicsEngine
{
public:
	GraphicsEngine(int argc, char *argv[]);
	~GraphicsEngine();

    void StartRendering(SceneManager::Scene* scene);//lock properties modification and start rendering
    void StopRendering();//unlock properties modification and output the rendering result

	Photographer& GetPhotographer(){return m_photographer;}

private:
	void DrawPointLightSphere(SceneManager::Scene* scene);
    void DrawOpaqueObjects(SceneManager::Scene* scene);
	void DrawAlphaObjects(SceneManager::Scene* scene);
	void DrawParticles(SceneManager::Scene* scene);
    void Preprocess();
    void Render(SceneManager::Scene* scene);

private:
	Photographer m_photographer;
};

}
}

#endif

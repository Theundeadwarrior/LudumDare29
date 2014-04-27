#ifndef SCENEMANAGER_SCENE_H
#define SCENEMANAGER_SCENE_H

#include <vector>
#include "SceneManager/Objects/Object.h"
#include "SceneManager/Camera/Camera.h"
#include "SceneManager/Lights/PointLight.h"
#include "SceneManager/SkyBox/SkyBox.h"
#include "Events/InputMouseListener.h"
#include "LowLevelGraphics/Material/Texture/TextureSkyBox.h"
#include "ParticleSystem/ParticleSystem.h"
#include <list>

namespace Atum { namespace Events { class MouseEvent; }}

namespace Atum
{
namespace SceneManager
{
    
class Scene : public Events::InputMouseListener
{
public:
	enum CameraMode
	{
		CAMERA_NONE = 0,
		CAMERA_ROTATION,
		CAMERA_ZOOM,
		CAMERA_TRANSLATION
	};

    Scene();
    ~Scene();

	virtual void Init()=0{}
	virtual void Uninit()=0{}

	// Mutator
    void AddObject(Object* const object){m_objectList.push_back(object);}
	void AddPointCloud(Object* const object){m_pointCloudList.push_back(object);}
	void AddCamera(Camera* const camera);
	void AddPointLight(PointLight* pointLight);
	void AddParticleSystem(ParticleSystem::ParticleSystem* const particleSystem){m_particleSystemList.push_back(particleSystem);}
	void DeletePointLight(std::vector<PointLight*>::iterator it){m_pointLightList.erase(it);}
	void AddSkyBox(SkyBox * skyBox);
	void SetCurrentCamera(unsigned int id){m_currentCamera = m_cameraList[id];}

	// iterator
    std::list<Object*>::iterator GetBeginObjectList(){return m_objectList.begin();}
	std::list<Object*>::iterator GetEndObjectList(){ return m_objectList.end(); }

	std::vector<Object*>::iterator GetBeginPointCloudList(){return m_pointCloudList.begin();}
	std::vector<Object*>::iterator GetEndPointCloudList(){return m_pointCloudList.end();}

	std::vector<PointLight*>::iterator GetBeginPointLightList(){return m_pointLightList.begin();}
	std::vector<PointLight*>::iterator GetEndPointLightList(){return m_pointLightList.end();}

	std::vector<ParticleSystem::ParticleSystem*>::iterator GetBeginParticleSystemList(){return m_particleSystemList.begin();}
	std::vector<ParticleSystem::ParticleSystem*>::iterator GetEndParticleSystemList(){return m_particleSystemList.end();}
    
	// Mouse Listener
	virtual void NotifyMouseClicked( const Events::MouseEvent& event );
	virtual void NotifyMouseMoved( const Events::MouseEvent& event );

	//Getters
	Camera* const GetCurrentCamera() const;
	SkyBox * const GetSkyBox() const;

	//Lights update
	//void UpdateIndexes(std::vector<Light*>* lights);

	virtual void Update();

	void UpdateAllPointLights();
	void UpdateAllObjects();

protected:
    std::list<Object*> m_objectList;
	
private:
	std::vector<Object*> m_pointCloudList;
	std::vector<Camera*> m_cameraList;
	std::vector<PointLight*> m_pointLightList;
	std::vector<ParticleSystem::ParticleSystem*> m_particleSystemList;

	SkyBox * m_skyBox;
	Camera* m_currentCamera;

	int m_mouseClickPositionX, m_mouseClickPositionY;
	CameraMode m_cameraMode;
};

} // namespace SceneManager
} // namespace Atum


#endif

#ifndef PHYSICSENGINE_PHYSICSENGINE_H
#define PHYSICSENGINE_PHYSICSENGINE_H

#include <PhysX/include/PxPhysicsAPI.h>
#include <PhysicsEngine/PhysicsScene.h>
#include <PhysicsEngine/Objects/PhysicsDynamicObject.h>
#include <Utilities/Debug/Debug.h>
#include <SceneManager/Scene/Scene.h>
#include "Events/EventManager.h"

namespace Atum
{
	namespace PhysicsEngine
	{
		class PhysicsEngine : public Events::InputKeyboardListener
		{
		public:
			~PhysicsEngine();
			static PhysicsEngine & GetInstance();

			bool Advance(physx::PxReal dt);
			inline PhysicsScene * const GetScene() const { return m_physicScene; };
			void SetScene(SceneManager::Scene * const scene);
			void UpdateGraphicScene();
			virtual void NotifyKeyPressed(const Events::KeyboardEvent& event);

		private:
			PhysicsEngine();
			void Initialize();

		private:
			physx::PxFoundation * m_foundation;
			physx::PxProfileZoneManager * m_profileZoneManager;
			physx::PxPhysics * m_physics;
			physx::PxCooking * m_cooking;

			physx::PxDefaultErrorCallback m_defaultErrorCallback;
			physx::PxDefaultAllocator m_defaultAllocatorCallback;

			PhysicsScene * m_physicScene;
			SceneManager::Scene * m_graphicScene;
		};
	}
}

#endif
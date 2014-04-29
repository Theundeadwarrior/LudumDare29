#include <PhysicsEngine/PhysicsEngine.h>

namespace Atum
{
	namespace PhysicsEngine
	{
		PhysicsEngine::PhysicsEngine()
		{
			Events::EventManager::GetInstance().RegisterKeyboardListener(this);
			Initialize();
		}

		PhysicsEngine::~PhysicsEngine()
		{
			delete m_physicScene;

			m_cooking->release();
			m_physics->release();
			m_profileZoneManager->release();
			m_foundation->release();
		}

		PhysicsEngine & PhysicsEngine::GetInstance()
		{
			static PhysicsEngine physicsEngine;
			return physicsEngine;
		}

		void PhysicsEngine::Initialize()
		{
			Utilities::OutputTrace("Physics engine initialization...");
			m_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_defaultAllocatorCallback, m_defaultErrorCallback);

			ATUM_ASSERT_MESSAGE(m_foundation, "PxCreateFoundation failed!");

			m_profileZoneManager = &physx::PxProfileZoneManager::createProfileZoneManager(m_foundation);

			ATUM_ASSERT_MESSAGE(m_profileZoneManager, "PxProfileZoneManager::createProfileZoneManager failed!");

			bool recordMemoryAllocations = true;
			m_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_foundation, physx::PxTolerancesScale(), recordMemoryAllocations, m_profileZoneManager);
			
			ATUM_ASSERT_MESSAGE(m_physics, "PxCreatePhysics failed!");

			m_cooking = PxCreateCooking(PX_PHYSICS_VERSION, *m_foundation, physx::PxCookingParams());

			ATUM_ASSERT_MESSAGE(m_cooking, "PxCreateCooking failed!");

			m_physicScene = new PhysicsScene(4, 1/32.0f, m_foundation, m_profileZoneManager, m_physics, m_cooking);
		}

		bool PhysicsEngine::Advance(physx::PxReal dt)
		{
			return m_physicScene->Advance(dt);
		}

		void PhysicsEngine::UpdateGraphicScene()
		{
			std::vector<PhysicsObject*>::iterator it = m_physicScene->GetBeginPhysicsObjectList();
			std::vector<PhysicsObject*>::iterator itEnd = m_physicScene->GetEndPhysicsObjectList();

			std::list<SceneManager::Object*>::iterator itObject = m_graphicScene->GetBeginObjectList();
			std::list<SceneManager::Object*>::iterator itObjectEnd = m_graphicScene->GetEndObjectList();
			for(; it != itEnd; it++, itObject++)
			{
				physx::PxTransform transformPhysic = (*it)->GetActor()->getGlobalPose();
				glm::mat4 rotationObject(1.0f);
				glm::vec3 positionObject;
				positionObject.x = transformPhysic.p[0];
				positionObject.y = transformPhysic.p[1];
				positionObject.z = transformPhysic.p[2];
				physx::PxMat33 rotation = physx::PxMat33(transformPhysic.q);
				rotationObject[0][0] = rotation[0][0];
				rotationObject[0][1] = rotation[0][1];
				rotationObject[0][2] = rotation[0][2];

				rotationObject[1][0] = rotation[1][0];
				rotationObject[1][1] = rotation[1][1];
				rotationObject[1][2] = rotation[1][2];

				rotationObject[2][0] = rotation[2][0];
				rotationObject[2][1] = rotation[2][1];
				rotationObject[2][2] = rotation[2][2];

				(*itObject)->GetTransform()->SetRotation(rotationObject);
				(*itObject)->GetTransform()->SetTranslate(positionObject);
			}
		}

		void PhysicsEngine::SetScene(SceneManager::Scene * const scene)
		{
			 m_graphicScene = scene;
			 std::list<SceneManager::Object*>::iterator it = m_graphicScene->GetBeginObjectList();
			 std::list<SceneManager::Object*>::iterator itEnd = m_graphicScene->GetEndObjectList();

			 physx::PxVec3 position;
			 for(; it != itEnd; it++)
			 {
				 position.x = (*it)->GetTransform()->GetPosition().x;
				 position.y = (*it)->GetTransform()->GetPosition().y;
				 position.z = (*it)->GetTransform()->GetPosition().z;
				 m_physicScene->AddDynamicObject(&(*it)->GetGeometry()->m_vertex[0], 
													(*it)->GetGeometry()->GetVertexBufferSize(), 
													position,
													0.1f, 0.1f, 0.1f);

			 }

			 m_physicScene->CreatePlane();
		}

		void PhysicsEngine::NotifyKeyPressed(const Events::KeyboardEvent& event)
		{
			if(event.GetEventType() == Events::KeyboardEventType::KEY_PRESSED)
			{
				if (event.GetKey() == 'p')
				{
					std::vector<PhysicsObject*>::iterator it = m_physicScene->GetBeginPhysicsObjectList();
					std::vector<PhysicsObject*>::iterator itEnd = m_physicScene->GetEndPhysicsObjectList();

					for(; it != itEnd; it++)
					{
						PhysicsDynamicObject * physicDynamicObject = dynamic_cast<PhysicsDynamicObject *> (*it);
						physicDynamicObject->ApplyForce(physx::PxVec3(0.0f, 10000.0f, 0.0f));
					}
				}
				if (event.GetKey() == 'o')
				{
					std::vector<PhysicsObject*>::iterator it = m_physicScene->GetBeginPhysicsObjectList();
					std::vector<PhysicsObject*>::iterator itEnd = m_physicScene->GetEndPhysicsObjectList();

					for(; it != itEnd; it++)
					{
						PhysicsDynamicObject * physicDynamicObject = dynamic_cast<PhysicsDynamicObject *> (*it);
						physicDynamicObject->ApplyTorque(physx::PxVec3(10000000000.0f, 10000000000.0f, 10000000000.0f));
					}
				}
			}
		}

	}
}

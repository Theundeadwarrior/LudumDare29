#ifndef PHYSICSENGINE_PHYSICSCENE_H
#define PHYSICSENGINE_PHYSICSCENE_H

#include <PhysX/include/PxPhysicsAPI.h>
#include <PhysicsEngine/Objects/PhysicsDynamicObject.h>
#include <PhysicsEngine/Objects/PhysicsStaticObject.h>
#include <PhysicsEngine/Objects/PhysicsObject.h>
#include <vector>
#include <GLM/include/glm/glm.hpp>
#include <Utilities/Debug/Debug.h>

namespace Atum
{
	namespace PhysicsEngine
	{
		class PhysicsScene
		{
		public:
			PhysicsScene(const int & nbThreads, const physx::PxReal & stepSize, physx::PxFoundation * foundation, physx::PxProfileZoneManager * profileZoneManager, physx::PxPhysics * physics, physx::PxCooking * cooking);
			~PhysicsScene();

			bool PhysicsScene::Advance(physx::PxReal dt);

			void AddActor(physx::PxActor & actor);
			std::vector<PhysicsObject*>::iterator GetBeginPhysicsObjectList(){return m_physicObjects.begin();}
			std::vector<PhysicsObject*>::iterator GetEndPhysicsObjectList(){return m_physicObjects.end();}

			PhysicsObject * AddDynamicObject(const glm::vec3 * const convexVertices, unsigned int verticesCount, const physx::PxVec3 & position, const physx::PxReal & staticFriction, const physx::PxReal & dynamicFriction, const physx::PxReal & restitution);
			PhysicsObject * AddStaticObject(const glm::vec3 * const convexVertices, unsigned int verticesCount, const physx::PxVec3 & position, const physx::PxReal & staticFriction, const physx::PxReal & dynamicFriction, const physx::PxReal & restitution);

			PhysicsObject * CreatePlane(); // a plane on the x/z axes

		private:
			physx::PxScene* m_scene;
			physx::PxDefaultCpuDispatcher * m_cpuDispatcher;
			int m_nbThreads;

			physx::PxReal m_accumulator;
			physx::PxReal m_stepSize; // sec./frame

			// reference for the variables in the physics engine
			physx::PxFoundation * m_foundation;
			physx::PxProfileZoneManager * m_profileZoneManager;
			physx::PxPhysics * m_physics;
			physx::PxCooking * m_cooking;

			std::vector<PhysicsObject *> m_physicObjects;
		};
	}
}

#endif
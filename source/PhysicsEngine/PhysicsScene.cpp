#include <PhysicsEngine/PhysicsScene.h>

namespace Atum
{
	namespace PhysicsEngine
	{
		PhysicsScene::PhysicsScene(const int & nbThreads, const physx::PxReal & stepSize, physx::PxFoundation * foundation, physx::PxProfileZoneManager * profileZoneManager, physx::PxPhysics * physics, physx::PxCooking * cooking)
		{
			m_nbThreads = nbThreads;
			m_accumulator = 0.0f;
			m_stepSize = stepSize;

			m_foundation = foundation;
			m_profileZoneManager = profileZoneManager;
			m_physics = physics;
			m_cooking = cooking;

			physx::PxSceneDesc sceneDesc(m_physics->getTolerancesScale());
			sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
			//customizeSceneDesc(sceneDesc);

			if(!sceneDesc.cpuDispatcher)
			{
				m_cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(m_nbThreads);

				ATUM_ASSERT_MESSAGE(m_cpuDispatcher, "PxDefaultCpuDispatcherCreate failed!");

				sceneDesc.cpuDispatcher = m_cpuDispatcher;
			}

			if(!sceneDesc.filterShader)
			{
				sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
			}

			m_scene = m_physics->createScene(sceneDesc);

			ATUM_ASSERT_MESSAGE(m_scene, "createScene failed!");
		}

		PhysicsScene::~PhysicsScene()
		{
			for(unsigned int i = 0; i < m_physicObjects.size(); ++i)
			{
				delete m_physicObjects[i];
			}

			m_scene->release();
			m_cpuDispatcher->release();
		}

		bool PhysicsScene::Advance(physx::PxReal dt)
		{
			m_accumulator  += dt;
			if(m_accumulator < m_stepSize)
				return false;

			m_accumulator -= m_stepSize;

			m_scene->simulate(m_stepSize);
			m_scene->fetchResults(true);

			return true;
		}

		void PhysicsScene::AddActor(physx::PxActor & actor)
		{
			m_scene->addActor(actor);
		}

		PhysicsObject * PhysicsScene::AddDynamicObject(const glm::vec3 * const convexVertices, unsigned int verticesCount, const physx::PxVec3 & position, const physx::PxReal & staticFriction, const physx::PxReal & dynamicFriction, const physx::PxReal & restitution)
		{
			physx::PxConvexMeshDesc convexDesc;
			convexDesc.points.count = verticesCount;
			convexDesc.points.stride = sizeof(glm::vec3);
			convexDesc.points.data = convexVertices;
			convexDesc.flags = physx::PxConvexFlag::eCOMPUTE_CONVEX;

			physx::PxDefaultMemoryOutputStream buffer;
			if(!m_cooking->cookConvexMesh(convexDesc, buffer))
			{
				return NULL;
			}

			physx::PxDefaultMemoryInputData input(buffer.getData(), buffer.getSize());
			physx::PxConvexMesh* convexMesh = m_physics->createConvexMesh(input);

			PhysicsObject * physicsObject = new PhysicsDynamicObject(m_physics, convexMesh, 30.0f, position, staticFriction, dynamicFriction, restitution);
			m_physicObjects.push_back(physicsObject);

			m_scene->addActor(*(physicsObject->GetActor()));

			return physicsObject;
		}

		PhysicsObject * PhysicsScene::AddStaticObject(const glm::vec3 * const convexVertices, unsigned int verticesCount, const physx::PxVec3 & position, const physx::PxReal & staticFriction, const physx::PxReal & dynamicFriction, const physx::PxReal & restitution)
		{
			physx::PxConvexMeshDesc convexDesc;
			convexDesc.points.count = verticesCount;
			convexDesc.points.stride = sizeof(glm::vec3);
			convexDesc.points.data = convexVertices;
			convexDesc.flags = physx::PxConvexFlag::eCOMPUTE_CONVEX;

			physx::PxDefaultMemoryOutputStream buffer;
			if(!m_cooking->cookConvexMesh(convexDesc, buffer))
			{
				return NULL;
			}

			physx::PxDefaultMemoryInputData input(buffer.getData(), buffer.getSize());
			physx::PxConvexMesh* convexMesh = m_physics->createConvexMesh(input);

			PhysicsObject * physicsObject = new PhysicsStaticObject(m_physics, convexMesh, position, staticFriction, dynamicFriction, restitution);
			m_physicObjects.push_back(physicsObject);

			m_scene->addActor(*(physicsObject->GetActor()));

			return physicsObject;
		}

		PhysicsObject * PhysicsScene::CreatePlane()
		{
			physx::PxMaterial * material = m_physics->createMaterial(0.5f, 0.5f, 0.1f);
			physx::PxRigidStatic * rigidActor = PxCreatePlane(*m_physics, physx::PxPlane(physx::PxVec3(0.0f, 1.0f, 0.0f), 0.0f), *material);
			physx::PxShape * shape = rigidActor->createShape(physx::PxPlaneGeometry(), *material);
			m_scene->addActor(*rigidActor);

			return new PhysicsStaticObject(m_physics, rigidActor, shape, material);
		}
	}
}

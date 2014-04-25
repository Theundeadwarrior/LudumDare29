#include <PhysicsEngine/Objects/PhysicsStaticObject.h>

namespace Atum
{
	namespace PhysicsEngine
	{
		PhysicsStaticObject::PhysicsStaticObject(physx::PxPhysics * physics, physx::PxConvexMesh* convexMesh, const physx::PxVec3 & position, const physx::PxReal & staticFriction, const physx::PxReal & dynamicFriction, const physx::PxReal & restitution)
			: PhysicsObject(physics, staticFriction, dynamicFriction, restitution)
		{
			m_actor = m_physics->createRigidStatic(physx::PxTransform(position));
			m_shape = m_actor->createShape(physx::PxConvexMeshGeometry(convexMesh), *m_material);
		}

		PhysicsStaticObject::PhysicsStaticObject(physx::PxPhysics * physics, physx::PxRigidStatic * actor, physx::PxShape * shape, physx::PxMaterial * material)
			: PhysicsObject(physics, material)
		{
			m_actor = actor;
			m_shape = shape;
		}

		PhysicsStaticObject::~PhysicsStaticObject()
		{
			m_material->release();
			// Apparently, we cannot destroy the shape of a static object before the actor ??
			//m_shape->release();
			m_actor->release();
		}

		void PhysicsStaticObject::SetPosition(const physx::PxVec3 & position)
		{
			m_actor->setGlobalPose(physx::PxTransform(position));
		}
	}
}

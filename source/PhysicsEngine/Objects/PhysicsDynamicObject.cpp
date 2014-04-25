#include <PhysicsEngine/Objects/PhysicsDynamicObject.h>

namespace Atum
{
	namespace PhysicsEngine
	{
		PhysicsDynamicObject::PhysicsDynamicObject(physx::PxPhysics * physics, physx::PxConvexMesh* convexMesh, const physx::PxReal & mass, const physx::PxVec3 & position, const physx::PxReal & staticFriction, const physx::PxReal & dynamicFriction, const physx::PxReal & restitution)
			: PhysicsObject(physics, staticFriction, dynamicFriction, restitution)
		{
			m_mass = mass;
			m_actor = m_physics->createRigidDynamic(physx::PxTransform(position));
			m_shape = m_actor->createShape(physx::PxConvexMeshGeometry(convexMesh), *m_material);
			m_actor->setMass(m_mass);
			physx::PxRigidBodyExt::updateMassAndInertia(*m_actor, m_mass);
		}

		PhysicsDynamicObject::~PhysicsDynamicObject()
		{
			m_material->release();
			m_shape->release();
			m_actor->release();
		}

		void PhysicsDynamicObject::ApplyForce(const physx::PxVec3 & force)
		{
			m_actor->addForce(force);
		}

		void PhysicsDynamicObject::ApplyTorque(const physx::PxVec3 & torque)
		{
			m_actor->addTorque(torque);
		}

		void PhysicsDynamicObject::SetPosition(const physx::PxVec3 & position)
		{
			m_actor->setGlobalPose(physx::PxTransform(position));
		}
	}
}

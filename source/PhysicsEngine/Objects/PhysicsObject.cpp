#include <PhysicsEngine/Objects/PhysicsObject.h>

namespace Atum
{
	namespace PhysicsEngine
	{
		PhysicsObject::PhysicsObject(physx::PxPhysics * physics, const physx::PxReal & staticFriction, const physx::PxReal & dynamicFriction, const physx::PxReal & restitution)
		{
			m_physics = physics;
			m_staticFriction = staticFriction;
			m_dynamicFriction = dynamicFriction;
			m_restitution = restitution;
			m_material = m_physics->createMaterial(m_staticFriction, m_dynamicFriction, m_restitution);

			ATUM_ASSERT_MESSAGE(m_material, "createMaterial failed!");
		}

		PhysicsObject::PhysicsObject(physx::PxPhysics * physics, physx::PxMaterial * material)
		{
			m_physics = physics;
			m_material = material;
			m_staticFriction = material->getStaticFriction();
			m_dynamicFriction = material->getDynamicFriction();
			m_restitution = material->getRestitution();
		}

		PhysicsObject::~PhysicsObject()
		{
		}
	}
}
